%{
#include "functions.h"

/*declarations*/
/*Names representing tokens must be declared; this is most simply done by writing

        %token   name1  name2 . . .

in the declarations section. (See Sections 3 , 5, and 6 for much more discussion). Every name not defined in the declarations section is assumed to represent a nonterminal symbol. Every nonterminal symbol must appear on the left side of at least one rule. */

int yylex(void);
int yyerror (char* yaccProvidedMessage);

int scope = 0;
/*metavliti gia na tsekaroume an to id einai mesa se return poy an einai den ftiaxnoume var*/
int retFLAG = 0; 	
/* metavliti gia ton elegxo an mesolavei sunartisi */
int check_if_open_func = 0;
int loop_signal = 0;
int block_func_signal = 0;
int assign_op = 0;
int is_func = 0;
int loopcounter = 0;
int checkglob = 0;

struct intList * breaklist_head;
struct intList * contlist_head;
struct stmt_t* tempstmt;

struct expr* func;
struct expr* t;
struct expr* val;
struct expr* temps;
struct expr* indexes;
struct SymbolTableEntry *new_temp;

int la;

//struct stack* scopeoffsetStack ;


/*int libfunc gia na vlepomy ena i sunartisi i opoia kalei ta ids einai libfunc giati an einai kanoume mono lookup*/
int libfunc=0;
SymTable *Symtbl; 

extern char* yytext; 				
extern int yylineno;  				
extern FILE* yyin; 					

%}


%union
{
    int intVal;
    float floatVal;
    char *stringVal;    
    struct SymbolTableEntry *exprNode;

    struct call* callVal;
    struct expr* exprVal;
    struct stmt_t* stmtVal;
	//struct whilestmt* stmtVal;
    unsigned unsignedVal;
};

/* akolouthei to arxiko sumvolo tis grammatikis to opoio einai upoxrewtiko*/

	

/* 	prepei na einai tis morfis 

	%token <intVal> TOKEN -> orizei to termatiko sumvolo TOKEN me tupo auton poy antistoixei sto intVAL pedio toy union */

%start program

%token <intVal>	CONST_INT

%token <stringVal> IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND NOT OR LOCAL TRUE FALSE NIL ASSIGN
%token <stringVal> PLUS MINUS MULTIPLY DEVIDE PERCENTAGE EQUAL NOTEQUAL DOUBLE_PLUS DOUBLE_MINUS GREATER_THAN LESS_THAN GR_EQ 
%token <stringVal> LE_EQ ID STRING DOT DOUBLE_DOT UNDERSCORE COLON DOUBLE_COL LEFT_BR RIGHT_BR LEFT_SQ_BR RIGHT_SQ_BR LEFT_PAR
%token <stringVal> RIGHT_PAR SEMICOLON COMMA 

%token <floatVal> CONST_REAL
 

/* i proteraiotita eiani auksanomeni apo panw pros ta katw */

%right ASSIGN
%left OR
%left AND
%nonassoc EQUAL NOTEQUAL 
%nonassoc GREATER_THAN GR_EQ LESS_THAN LE_EQ
%left PLUS MINUS
%left MULTIPLY DEVIDE PERCENTAGE
%right NOT DOUBLE_PLUS DOUBLE_MINUS UMINUS
%left DOT DOUBLE_DOT
%left LEFT_SQ_BR RIGHT_SQ_BR
%left LEFT_PAR RIGHT_PAR

%type <exprVal> lvalue
%type <exprVal> expr
%type <exprVal>  assignexpr
%type <stringVal> idlist
//%type <stringVal> idlists
%type <exprVal>  call
%type <stringVal> funcname
%type <unsignedVal> funcbody
%type <exprNode> funcprefix
%type <exprNode> funcdef
%type <unsignedVal> funcblockend
%type <unsignedVal> N
%type <unsignedVal> M
%type <stmtVal> stmt
%type <stmtVal> whilestmt
%type <exprVal> tableitem
%type <exprVal> primary
%type <exprVal> term
%type <exprVal> const
%type <exprVal> tablemake
%type <callVal> callsuffix
%type <callVal> normcall
%type <callVal> methodcall
%type <exprVal> elist
//%type <exprVal> elists
%type <exprVal> indexed
%type <exprVal> indexedelem
%type <unsignedVal> ifprefix
%type <unsignedVal> elseprefix
%type <unsignedVal> whilestart
%type <unsignedVal> whilecond
%type <unsignedVal> funcargs
%type <stmtVal> loopstmt
%type <stmtVal> continue
%type <stmtVal> break
%type <stmtVal> stmts
%type <stmtVal> returnstmt
%type <stmtVal> forprefix
%type <stmtVal> forstmt
%type <stmtVal> block

/*tou lew na perimenei ena sfalma shift/reduce poy einai to ifstmt*/
%expect 1


%%
/*rules*/
/*ta deksia meri ginontai reduced sta aristera meri otan vrethoun kata ti diarkeia tis suntaktikis analusis*/

program 		:	stmts	

/*ta statements einai 0 h perissotera kai gia na to petuxoyme auto prepei na ftiaksoume allo ena kanona*/
stmts			: 	stmt stmts 				{	
											
												//$$->breakList = mergelist($1->breakList,$2->breakList);
												//$$->contList = mergelist($1->contList,$2->contList);
											}
				|	{$$ = NULL;}
				;	

/*stmts 			: 	stmts stmt  			{
												//$$->breakList = mergelist($1->breakList,$2->breakList);
												//$$->contList = mergelist($1->contList,$2->contList);
											}
				|	stmt 		{$$=$1;}
				;	*/			

stmt			:	expr SEMICOLON			{printf("stmt <- expr;\n\n");}
				|	ifstmt					{printf("stmt <- ifstmt\n\n");}
				|	whilestmt				{printf("stmt <- whilestmt\n\n");}
				|	forstmt					{printf("stmt <- forstmt\n\n");}
				|	returnstmt				{printf("stmt <- returnstmt\n\n");}
				|	break 					{}
				|	continue 				{}
				|	block					{	
												$$=$1;
												printf("stmt <- block\n\n");
											}
				|	funcdef					{printf("stmt <- funcdef\n\n");}
				| 	SEMICOLON				{printf("stmt <- ;\n\n");}
				;

expr			:	assignexpr						{$$=$1;	printf("expr <- assignexpr\n");}
				|	expr PLUS expr				{ 
													if(check_corr_type($1)==0){
														$$ = newexpr(arithexpr_e);
														$$->sym = newtemp(Symtbl,scope,yylineno);
														emit(add,$1,$3,$$,0,yylineno);
														if($1->type == constnum_e && $3->type == constnum_e){
															$$->type = constnum_e;
															$$->x = $1->x + $3->x;
														}else if($1->type == constnum_ereal && $3->type == constnum_ereal){
															$$->type = constnum_ereal;
															$$->y = $1->y + $3->y;
														}else if($1->type == constnum_ereal){
															$$->type = constnum_ereal;
															$$->y = $1->y + $1->x;
														}else if($3->type == constnum_ereal){
															$$->type = constnum_ereal;
															$$->y = $1->x + $1->y;
														}
														printf("expr <- expr op expr\n");
														
															
													}else{
														printf("\033[1;31m");
					                                    printf("Error in line %d - This type of expr could not be used with PLUS expr\n",yylineno);
					                                    printf("\033[0m");
													}
												}
												
				|	expr MINUS expr				{	
													if(check_corr_type($1)==0 ){

														$$ = newexpr(arithexpr_e);
														$$->sym = newtemp(Symtbl,scope,yylineno);
														emit(sub,$1,$3,$$,0,yylineno);
														if($1->type == constnum_e && $3->type == constnum_e){
															$$->type = constnum_e;
															$$->x = $1->x - $3->x;
														}else if($1->type == constnum_ereal && $3->type == constnum_ereal){
															$$->type = constnum_ereal;
															$$->y = $1->y - $3->y;
														}else if($1->type == constnum_ereal){
															$$->type = constnum_ereal;
															$$->y = $1->y - $1->x;
														}else if($3->type == constnum_ereal){
															$$->type = constnum_ereal;
															$$->y = $1->x - $1->y;
														}
														printf("expr <- expr op expr\n");
													}else{
															printf("\033[1;31m");
				                                        	printf("Error in line %d - This type of expr could not be used with MINUS expr\n",yylineno);
				                                        	printf("\033[0m");
													}
												}
				|	expr MULTIPLY expr				{	
													if(check_corr_type($1)==0 ){

														$$ = newexpr(arithexpr_e);
														$$->sym = newtemp(Symtbl,scope,yylineno);
														emit(mul,$1,$3,$$,0,yylineno);
														if($1->type == constnum_e && $3->type == constnum_e){
															$$->type = constnum_e;
															$$->x = $1->x * $3->x;
														}else if($1->type == constnum_ereal && $3->type == constnum_ereal){
															$$->type = constnum_ereal;
															$$->y = $1->y * $3->y;
														}else if($1->type == constnum_ereal){
															$$->type = constnum_ereal;
															$$->y = $1->y * $1->x;
														}else if($3->type == constnum_ereal){
															$$->type = constnum_ereal;
															$$->y = $1->x * $1->y;
														}
														printf("expr <- expr op expr\n");
													}else{
															printf("\033[1;31m");
				                                        	printf("Error in line %d - This type of expr could not be used with MULTIPLY expr\n",yylineno);
				                                        	printf("\033[0m");
													}
												}

				|	expr DEVIDE	expr				{	
													if(check_corr_type($1)==0 ){

														$$ = newexpr(arithexpr_e);
														$$->sym = newtemp(Symtbl,scope,yylineno);
														emit(divi,$1,$3,$$,0,yylineno);
														if($1->type == constnum_e && $3->type == constnum_e){
															$$->type = constnum_e;
															if($3->x !=0){
																$$->x = $1->x / $3->x;
															}else{
																printf("\033[1;31m");
					                                        	printf("Error in line %d - Devide with ZERO is not allowed \n",yylineno);
					                                        	printf("\033[0m");
															}
														}
														printf("expr <- expr op expr\n");
													}else{
															printf("\033[1;31m");
				                                        	printf("Error in line %d - This type of expr could not be used with DEVIDE expr\n",yylineno);
				                                        	printf("\033[0m");
													}
												}

				|	expr PERCENTAGE expr			{	
														if(check_corr_type($1)==0){

															$$ = newexpr(arithexpr_e);
															$$->sym = newtemp(Symtbl,scope,yylineno);
															emit(mod,$1,$3,$$,0,yylineno);
															if($1->type == constnum_e && $3->type == constnum_e){
																$$->type = constnum_e;
																if($3->x!=0){
																	$$->x = $1->x % $3->x;
																}else{
																	$$->x = $1->x;
																}
															}
															printf("expr <- expr op expr\n");
														}else{
																printf("\033[1;31m");
					                                        	printf("Error in line %d - This type of expr could not be used with PERCENTAGE expr\n",yylineno);
					                                        	printf("\033[0m");
														}
													}

				|	expr GREATER_THAN expr				{
															if(check_corr_type($1)==0){
																$$ = newexpr(boolexpr_e);
																$$ ->sym = newtemp(Symtbl,scope,yylineno);

																emit(if_greater,$1,$3,NULL,nextquad()+3,yylineno);
																emit(jump,NULL,NULL,NULL,nextquad()+4,yylineno);		//tskir: egw to prosthesa giati den to ekane print
																
																temps = newexpr(constbool_e);
																temps->val.boolConst = 0;
																temps->sym->offset=$$->sym->offset;	//added by gerorge
																printf("einai %d\n",$$->sym->offset);
																emit(assign,temps,NULL,$$,0,yylineno);					//tskir : allagi me to apo panw giati mallon to newexpr_constbool
																//emit(assign,newexpr_constbool(0),NULL,$$,0,yylineno);		//tskir ->den leitourgei
																//printf("print %d",temps->val.boolConst);
																emit(jump,NULL,NULL,NULL,nextquad()+3,yylineno);		//tskir: to allaksa apo 2 se 3

																t = newexpr(constbool_e);
																t->val.boolConst = 1;
																t->sym->offset=$$->sym->offset;	//added by gerorge
																printf("einai %d\n",$$->sym->offset);
																//emit(assign,newexpr_constbool(1),NULL,$$,0,yylineno); 		//tskir: to allaksa me to apo katw
																emit(assign,t,NULL,$$,0,yylineno); 
																printf("expr <- expr op expr\n");

																if($1>$3){												//tskir: added last 1/5
																	$$->val.boolConst = 0;
																}else{
																	$$->val.boolConst= 1;
																}
															}else{
																printf("\033[1;31m");
					                                        	printf("Error in line %d - This type of expr could not be used with GREATER THAN expr\n",yylineno);
					                                        	printf("\033[0m");
															}
														}

				|	expr GR_EQ expr				{		

														if(check_corr_type($1)==0){
															$$ = newexpr(boolexpr_e);
															$$ ->sym = newtemp(Symtbl,scope,yylineno);

															temps = newexpr(constbool_e);
															temps->val.boolConst = 0;
															temps->sym->offset=$$->sym->offset;	//added by gerorge
															printf("einai %d\n",$$->sym->offset);
															emit(if_greatereq,$1,$3,NULL,nextquad()+3,yylineno);
															emit(jump,NULL,NULL,NULL,nextquad()+4,yylineno);		//tskir: egw to prosthesa giati den to ekane print
															
															emit(assign,temps,NULL,$$,0,yylineno); 	//tskir allagi apo katw m auto
															//emit(assign,newexpr_constbool(0),NULL,$$,0,yylineno);

															emit(jump,NULL,NULL,NULL,nextquad()+3,yylineno);

															t = newexpr(constbool_e);
															t->val.boolConst = 1;
															t->sym->offset=$$->sym->offset;	//added by gerorge
															printf(" einai %d\n",$$->sym->offset);
															//emit(assign,newexpr_constbool(1),NULL,$$,0,yylineno); 		//tskir: to allaksa me to apo katw

															emit(assign,t,NULL,$$,0,yylineno);
															printf("expr <- expr op expr\n");

															if($1>=$3){												//tskir: added last 1/5
																$$->val.boolConst = 0;
															}else{
																$$->val.boolConst= 1;
															}
														}else{
																printf("\033[1;31m");
					                                        	printf("Error in line %d - This type of expr could not be used with GREATER EQUAL expr\n",yylineno);
					                                        	printf("\033[0m");
														}
												}

				|	expr LESS_THAN expr				{
														if(check_corr_type($1)==0){
															$$ = newexpr(boolexpr_e);
															$$ ->sym = newtemp(Symtbl,scope,yylineno);

															temps = newexpr(constbool_e);
															temps->val.boolConst = 0;
															temps->sym->offset=$$->sym->offset;	//added by gerorge
															printf(" einai %d\n",$$->sym->offset);
															emit(if_less,$1,$3,NULL,nextquad()+3,yylineno);
															emit(jump,NULL,NULL,NULL,nextquad()+4,yylineno);		//tskir: egw to prosthesa giati den to ekane print

															emit(assign,temps,NULL,$$,0,yylineno);
															emit(jump,NULL,NULL,NULL,nextquad()+3,yylineno);

															t = newexpr(constbool_e);
															t->val.boolConst = 1;
															t->sym->offset=$$->sym->offset;	//added by gerorge
															printf( "einai %d\n",$$->sym->offset);
															emit(assign,t,NULL,$$,0,yylineno);						//tskir: allagi 
															printf("expr <- expr op expr\n");

															if($1<$3){												//tskir: added last 1/5
																$$->val.boolConst = 0;
															}else{
																$$->val.boolConst= 1;
															}
														}else{
																printf("\033[1;31m");
					                                        	printf("Error in line %d - This type of expr could not be used with LESS THAN expr\n",yylineno);
					                                        	printf("\033[0m");
														}
													}

				|	expr LE_EQ expr				{
														if(check_corr_type($1)==0){
															$$ = newexpr(boolexpr_e);
															$$ ->sym = newtemp(Symtbl,scope,yylineno);

															emit(if_lesseq,$1,$3,NULL,nextquad()+3,yylineno);
															emit(jump,NULL,NULL,NULL,nextquad()+4,yylineno);		//tskir: egw to prosthesa giati den to ekane print

															temps = newexpr(constbool_e);
															temps->val.boolConst = 0;
															temps->sym->offset=$$->sym->offset;	//added by gerorge
															printf(" einai %d\n",$$->sym->offset);
															emit(assign,temps,NULL,$$,0,yylineno);
															emit(jump,NULL,NULL,NULL,nextquad()+3,yylineno);

															t = newexpr(constbool_e);
															t->val.boolConst = 1;
															t->sym->offset=$$->sym->offset;	//added by gerorge
															printf(" einai %d\n",$$->sym->offset);
															emit(assign,t,NULL,$$,0,yylineno);
															printf("expr <- expr op expr\n");

															if($1<=$3){												//tskir: added last 1/5
																$$->val.boolConst = 0;
															}else{
																$$->val.boolConst= 1;
															}
														}else{
																printf("\033[1;31m");
					                                        	printf("Error in line %d - This type of expr could not be used with LESS EQUAL expr\n",yylineno);
					                                        	printf("\033[0m");
														}
													}

				|	expr EQUAL expr				{
														if(check_corr_type($1)==0){
															$$ = newexpr(boolexpr_e);
															$$ ->sym = newtemp(Symtbl,scope,yylineno);

															temps = newexpr(constbool_e);
															temps->val.boolConst = 0;
															temps->sym->offset=$$->sym->offset;	//added by gerorge
															printf(" einai %d\n",$$->sym->offset);
															emit(if_eq,$1,$3,NULL,nextquad()+3,yylineno);
															emit(jump,NULL,NULL,NULL,nextquad()+4,yylineno);		//tskir: egw to prosthesa giati den to ekane print

															emit(assign,temps,NULL,$$,0,yylineno);
															emit(jump,NULL,NULL,NULL,nextquad()+3,yylineno);
															
															t = newexpr(constbool_e);
															t->val.boolConst = 1;
															t->sym->offset=$$->sym->offset;	//added by gerorge
															printf(" einai %d\n",$$->sym->offset);
															emit(assign,t,NULL,$$,0,yylineno);
															printf("expr <- expr op expr\n");

															if($1==$3){												//tskir: added last 1/5
																$$->val.boolConst = 0;
															}else{
																$$->val.boolConst= 1;
															}
														}else{
																printf("\033[1;31m");
					                                        	printf("Error in line %d - This type of expr could not be used with EQUAL expr\n",yylineno);
					                                        	printf("\033[0m");
														}	
												}

				|	expr NOTEQUAL expr				{
														if(check_corr_type($1)==0){
															$$ = newexpr(boolexpr_e);
															$$ ->sym = newtemp(Symtbl,scope,yylineno);

															temps = newexpr(constbool_e);
															temps->val.boolConst = 0;
															temps->sym->offset=$$->sym->offset;	//added by gerorge
															printf("%d\n",$$->sym->offset);
															emit(if_noteq,$1,$3,NULL,nextquad()+3,yylineno);
															emit(jump,NULL,NULL,NULL,nextquad()+4,yylineno);		//tskir: egw to prosthesa giati den to ekane print
															
															emit(assign,temps,NULL,$$,0,yylineno);
															emit(jump,NULL,NULL,NULL,nextquad()+3,yylineno);
															t = newexpr(constbool_e);
															t->val.boolConst = 1;
															t->sym->offset=$$->sym->offset;	//added by gerorge
															printf(" einai %d\n",$$->sym->offset);
															emit(assign,t,NULL,$$,0,yylineno);
															printf("expr <- expr op expr\n");

															if($1!=$3){												//tskir: added last 1/5
																$$->val.boolConst = 0;
															}else{
																$$->val.boolConst= 1;
															}
														}else{
																printf("\033[1;31m");
					                                        	printf("Error in line %d - This type of expr could not be used with NOT EQUAL expr\n",yylineno);
					                                        	printf("\033[0m");
														}	
													}

				|	expr AND expr				{
													//if(check_corr_type($1)==0){
														$$ = newexpr(boolexpr_e);
														$$->sym = newtemp(Symtbl,scope,yylineno);
														emit(and,$1,$3,$$,0,yylineno);
														printf("expr <- expr op expr\n");
														//printf("expr <- expr op expr\n");

													/*}else{
																printf("\033[1;31m");
					                                        	printf("Error in line %d - This type of expr could not be used with AND expr\n",yylineno);
					                                        	printf("\033[0m");
													}	*/
												}

				|	expr OR expr				{
													//if(check_corr_type($1)==0){
														$$ = newexpr(boolexpr_e);
														$$->sym = newtemp(Symtbl,scope,yylineno);
														//printf("mpainei edw sto or \n");
														emit(or,$1,$3,$$,0,yylineno);
														printf("expr <- expr op expr\n");
													/*}else{
																printf("\033[1;31m");
					                                        	printf("Error in line %d - This type of expr could not be used with OR expr\n",yylineno);
					                                        	printf("\033[0m");
													}*/
												}

				|	term 							{	
														$$=$1;
														printf("expr <- term\n");
													}
				;



term			: 	LEFT_PAR expr RIGHT_PAR			{	
														$$ = $2;
														printf("term <- ( expr )\n");
													}
				|	MINUS expr %prec UMINUS			{	
														if(check_arith($2)==0){
															$$ = newexpr(arithexpr_e);
															$$->sym = newtemp(Symtbl,scope,yylineno);
															emit(uminus,$2,NULL,$$,0,yylineno);
														}
														printf("term <- -expr \n");
													}
				|	NOT expr						{	
														$$ = newexpr(boolexpr_e);
														$$->sym = newtemp(Symtbl,scope,yylineno);
														
														temps = newexpr(constbool_e);
														temps->val.boolConst = 0;
														temps->sym->offset=$$->sym->offset;	//added by gerorge
														printf(" einai %d\n",$$->sym->offset);
														t = newexpr(constbool_e);								//tskir added
														t->val.boolConst = 1;
														t->sym->offset=$$->sym->offset;	//added by gerorge
														printf(" einai %d\n",$$->sym->offset);
														emit(if_eq,$2,temps,NULL,nextquad()+5,yylineno);		//tskir added 
														emit(jump,NULL,NULL,NULL,nextquad()+2,yylineno);		//tskir: egw to prosthesa giati den to ekane print

														emit(assign,temps,NULL,$$,0,yylineno);	//tskir added
														emit(jump,NULL,NULL,NULL,nextquad()+3,yylineno);		//tskir added
														

														emit(assign,t,NULL,$$,0,yylineno);

														//emit(not,$2,NULL,$$,0,yylineno);

														printf("term <- not expr \n");
													}

				|	DOUBLE_PLUS lvalue				{
														if(check_type_for_print($2->sym->type)==1){
															printf("\033[1;31m");
															printf("Error in line %d - DOUBLE_PLUS lvalue action could not be used with Functions\n",yylineno);
															printf("\033[0m");
															printf("term <- ++lvalue \n");
														}
															if(check_arith($2)==0){
																if($2->type == tableitem_e){
																	temps = emit_iftableitem(Symtbl,scope,$2,yylineno);
																	emit(add,temps,newexpr_constnum(1),temps,0,yylineno);
																	emit(tablesetelem,$2,$2->index,temps,0,yylineno);
																}else{
																	
																	temps = newexpr(constnum_e);
																	temps->sym = newtemp(Symtbl,scope,yylineno);
																	temps->x = 1;
																	temps->sym->offset=$$->sym->offset;	//added by gerorge
																	printf(" einai %d\n",$$->sym->offset);
																	emit(add,$2,newexpr_constnum(1),temps,0,yylineno);
																	emit(assign,$2,NULL,temps,0,yylineno);
																}
															}else{
																printf("\033[1;31m");
																printf("Error in line %d - lvalue isnt a number\n",yylineno);
																printf("\033[0m");
															}	
														$$ = temps;
													}
															

				|	lvalue DOUBLE_PLUS				{
														if(check_type_for_print($1->sym->type)==1){
															printf("\033[1;31m");
															printf("Error in line %d - lvalue DOUBLE_PLUS action could not be used with Functions\n",yylineno);
															printf("\033[0m");
														}

														if(check_arith($1)==0){
															temps = newexpr(var_e);
															temps->sym = newtemp(Symtbl,scope,yylineno);
															temps->sym->offset=$$->sym->offset;	//added by gerorge
															printf(" einai %d\n",$$->sym->offset);
															if($1->type == tableitem_e){
																val = emit_iftableitem(Symtbl,scope,$1,yylineno);
																emit(assign,val,NULL,temps,0,yylineno);
																emit(add,val,newexpr_constnum(1),val,0,yylineno);
																emit(tablesetelem,$1,$1->index,val,0,yylineno);
															}else{
																emit(assign,$1,NULL,temps,0,yylineno);
																t = newexpr(constnum_e);
																t->x = 1;
																emit(add,$1,t,$1,0,yylineno);
															}
														}else{
															printf("\033[1;31m");
															printf("Error in line %d - lvalue isnt a number\n",yylineno);
															printf("\033[0m");
														}
														$$ = temps;
														printf("term <- lvalue++ \n");}

				|	DOUBLE_MINUS lvalue				{
														if(check_type_for_print($2->sym->type)==1){
															printf("\033[1;31m");
															printf("Error in line %d - DOUBLE_MINUS lvalue action could not be used with Functions\n",yylineno);
															printf("\033[0m");
															printf("term <- --lvalue \n");
														}
														if(check_arith($2)==0){
																if($2->type == tableitem_e){
																	temps = emit_iftableitem(Symtbl,scope,$2,yylineno);
																	emit(sub,temps,newexpr_constnum(1),temps,0,yylineno);
																	emit(tablesetelem,$2,$2->index,temps,0,yylineno);
																}else{
																	
																	temps = newexpr(constnum_e);
																	temps->sym = newtemp(Symtbl,scope,yylineno);
																	temps->x = 1;
																	temps->sym->offset=$$->sym->offset;	//added by gerorge
																	printf(" einai %d\n",$$->sym->offset);
																	emit(sub,$2,newexpr_constnum(1),temps,0,yylineno);
																	emit(assign,$2,NULL,temps,0,yylineno);
																}
														}else{
															printf("\033[1;31m");
															printf("Error in line %d - lvalue isnt a number\n",yylineno);
															printf("\033[0m");
														}
														$$ = temps;												
													}

				|	lvalue DOUBLE_MINUS				{
														if(check_type_for_print($1->sym->type)==1){
															printf("\033[1;31m");
															printf("Error in line %d - lvalue DOUBLE_MINUS action could not be used with Functions\n",yylineno);
															printf("\033[0m");
															printf("term <- lvalue-- \n");
														}
														if(check_arith($1)==0){
															temps = newexpr(var_e);
															temps->sym = newtemp(Symtbl,scope,yylineno);
															temps->sym->offset=$$->sym->offset;	//added by gerorge
															printf(" einai %d\n",$$->sym->offset);
															if($1->type == tableitem_e){
																val = emit_iftableitem(Symtbl,scope,$1,yylineno);
																emit(assign,val,NULL,temps,0,yylineno);
																emit(sub,val,newexpr_constnum(1),val,0,yylineno);
																emit(tablesetelem,$1,$1->index,val,0,yylineno);
															}else{
																emit(assign,$1,NULL,temps,0,yylineno);	
																t = newexpr(constnum_e);
																t->x = 1;
																emit(sub,$1,t,$1,0,yylineno);
															}
														}else{
															printf("\033[1;31m");
															printf("Error in line %d - lvalue isnt a number\n",yylineno);
															printf("\033[0m");
														}
														$$ = temps;
													}

				|	primary							{	
														$$=$1;
														printf("term <- primary \n");
													}
				;

assignexpr		:	lvalue 	ASSIGN expr				 
															{	if(checkglob==0){
																	if($1->sym!=NULL){
																		//printf("mpika mesa k to sym name eiani %s \n",$1->sym->value.varVal->name);
																		if($1->type==programfunc_e || $1->type==libraryfunc_e){
																					printf("\033[1;31m");
																					printf("Error in line %d - ASSIGN action could not be used with Functions\n",yylineno);
																					printf("\033[0m");
																}}}

																if($1->type == tableitem_e ){
																//printf("mpaieni edwdwwd\n");
																	//emit(tablesetelem,$1,$1->index,$3,0,yylineno);		//lvalue[index] =expr allaksa autp  gia toys pinakes
																	emit(tablesetelem,$1->index,$3,$1,0,yylineno);
																	temps = emit_iftableitem(Symtbl,scope,$1,yylineno);
																	temps->type = assignexpr_e;
																	temps->sym->offset=$$->sym->offset;	//added by gerorge
																	printf(" einai %d\n",$$->sym->offset);
																}else{
																//printf("mpaineiedcvw\n");
																	emit(assign,$3,NULL,$1,0,yylineno);
																	temps = newexpr(assignexpr_e);
																	temps->sym =newtemp(Symtbl,scope,yylineno);
																	temps->sym->offset=$$->sym->offset;	//added by gerorge
																	printf(" einai %d\n",$$->sym->offset);
																	emit(assign,$1,NULL,temps,0,yylineno);
																}
																$$=temps;
																//printf("to expr eiani $$: %s",$$->sym->value.varVal->name);
																//printf("to expr eiani lvalue: %s",$1->sym->value.varVal->name);
																//printf("to expr eiani epxr: %s",$3->sym->value.varVal->name);
																printf("assignexpr <- lvalue = expr \n");
															}

				;

primary			:	lvalue						{
													$$ = emit_iftableitem(Symtbl,scope,$1,yylineno);
													printf("primary <- lvalue \n");
												}

				|	call 						{	
													$$ = $1;
													printf("primary <- call \n");
												}
				|	tablemake 					{
													$$ = $1;
													printf("primary <- tablemake \n");
												}
				|	LEFT_PAR funcdef RIGHT_PAR 			{
															$$ = newexpr(programfunc_e);
															$$->sym = $2;
															printf("primary <- ( funcdef ) \n");
														}

				|	const 						{	
													$$=$1;
													//printf("to conststring einai %s\n",$$->val.strConst);
													//printf("to const eiani %d\n",$$->x);
													//printf("to const eiani %f\n",$$->y);
													printf("primary <- const \n");
												}
				;


lvalue			:	ID 							{	
                                                    if(look_up_inscope($1,scope)==NULL){
                                                        if(retFLAG==0){
                                                        	
                                                            if(check_if_open_func==0){
                                                                if(look_up($1,scope-1)==NULL){
                                                                	//printf("mpainei edw 2\n");
														            if(check_if_lib($1,yylineno)==0 && libfunc==0){
															            insert_variable(Symtbl,$1,scope,yylineno,check_Var_type_local(scope));
															            new_temp=look_up_inscope($1,scope);
																		new_temp->space=scope;
																		new_temp->offset=currscopeoffset();
																		inccurrscopeoffset();

															            //printf("%s variable Scope %d\n",$1, scope);
															        }
														            
														        
														        }else if(look_up($1,scope-1)!=NULL){
														            if(look_up($1,scope-1)->type==GLOBAL){
														           		 $$ = lvalue_expr(look_up_inscope_noprint($1,scope-1));
														                //printf("Ok %s is a global var\n",$1);
														                //printSymtable();
														            }else if(look_up($1,scope-1)->type==LOCALE){
														            	$$ = lvalue_expr(look_up_inscope_noprint($1,scope-1));
														                //printf("Ok %s refers to the previous variable and is visible\n",$1);
														            }
														          // printf("mpainei edw 3\n");
														        }
														        
                                                            }else if(check_if_open_func!=0){
                                                           
                                                                if(look_up($1,scope-1)==NULL){
                                                                    if(check_if_lib($1,yylineno)==0 && libfunc==0){
															            insert_variable(Symtbl,$1,scope,yylineno,check_Var_type_local(scope));

															            new_temp=look_up_inscope($1,scope);
																		new_temp->space=scope;
																		new_temp->offset=currscopeoffset();
																		inccurrscopeoffset();
																		//printf("mpainei edw 4\n");
															            //printf("%s variable Scope %d\n",$1, scope);
															        }
														            
														            
														        }else if(look_up($1,scope-1)!=NULL){
														        //printf("mpainei edw 5\n");
														            if(block_func_signal<=1){

														            }else if(block_func_signal>1){
														                if((look_up($1,scope-1)->type!=GLOBAL || look_up($1,scope-1)->type==LOCALE || look_up($1,scope-1)->type==FORMAL) && look_up($1,scope-1)->type!=USERFUNC){
														                    printf("\033[1;31m");
														                    printf("Error in line %d - cannot access %s in this function\n",yylineno,$1);
														                    printf("\033[0m");
														                }
														                
														            }
														            
														        }
                                                            }
                                                         
													    }else if(retFLAG!=0){
													   // printf("mpainei edw 6\n");
													        if(check_if_open_func==0 && scope==0){
													        	printf("\033[1;31m");
													            printf("Error in line %d - Use of 'return' while not in a function\n",yylineno);
													            printf("\033[0m");
													            //printSymtable();
													        }else if(check_if_open_func!=0){
													            if(look_up($1,scope-1)==NULL){
													                if(check_if_lib($1,yylineno)==0 && libfunc==0){
															            insert_variable(Symtbl,$1,scope,yylineno,check_Var_type_local(scope));

															            new_temp=look_up_inscope($1,scope);
																		new_temp->space=scope;
																		new_temp->offset=currscopeoffset();
																		inccurrscopeoffset();
															            //printf("%s variable Scope %d\n",$1, scope);
															  
															        }
															        //printSymtable();
															        
													            }else if(look_up($1,scope-1)!=NULL){
													                if(check_if_function_before(scope)==0){
													                    if(look_up($1,scope-1)->type==GLOBAL || look_up($1,scope-1)->type==USERFUNC || look_up($1,scope-1)->type==LOCALE){
													                        printf("\033[1;31m");
													                        printf("Error in line %d -  %s cannot access in this function\n",yylineno,$1);
													                        printf("\033[0m");
														                   //printSymtable();
														                   
													                    }
													                    
													                }else{
													                    if(look_up($1,scope-1)->type==GLOBAL || look_up($1,scope-1)->type!=LOCALE
													                    || look_up($1,scope-1)->type==USERFUNC
													                    || look_up($1,scope-1)->type==LIBFUNC){
													                        //printf("Ok: %s can access in this function\n",$1);
													                    }else{
													                        printf("\033[1;31m");
													                        printf("Error in line %d - %s cannot access in this function\n",yylineno,$1);
													                    	printf("\033[0m");
													                    }
													                    
													                }
													                
													            }
													            
														    }
													    }
													  
                                                    }	
                                                   
                                                    if(look_up_inscope($1,scope)!=NULL && retFLAG!=0 && scope==0){
                                                    		printf("\033[1;31m");
													            printf("Error in line %d - Use of 'return' while not in a function\n",yylineno);
													            printf("\033[0m");
                                                    }
													
													//toy dinw tin timi poy exei to lvalue gia na tin xrisimopoiisw meta stoys kanones lvalue ++ klp
														if(look_up_inscope_noprint($1,scope)!=NULL){
															//printf("mpainei sto telos\n");
															$$ = lvalue_expr(look_up_inscope_noprint($1,scope));
														}
														if(check_if_lib_noprint($1)==1 || check_type(look_up($1,scope)) ==1){						//added because when it was libfunc den ekane tipota && otan itan func genika den tin evlepe
															//printf("mpainei sto telos stin kainourgia\n");
															$$ = lvalue_expr(look_up($1,scope));
														}
														printf("lvalue <- ID \n");
														//printf("name = %s \n",$1);
												    }

				|	LOCAL ID 					{if(look_up_inscope_noprint($2,scope)==NULL && retFLAG==0){ 
															if(check_if_lib($2,yylineno)==0){
															//printf("mpainei edw\n");
																insert_variable(Symtbl,$2,scope,yylineno,check_Var_type_local(scope));

																new_temp=look_up_inscope($1,scope);
																new_temp->space=scope;
																new_temp->offset=currscopeoffset();
																inccurrscopeoffset();
															}
													}else if(look_up_inscope_noprint($2,scope)!=NULL ){
														//printf("OK found locally.\n");
													}

													//toy dinw tin timi poy exei to lvalue gia na tin xrisimopoiisw meta stoys kanones lvalue ++ klp
													$$ = lvalue_expr(look_up_inscope_noprint($2,scope));
													printf("lvalue <-  LOCAL ID\n");}

				|	DOUBLE_COL ID 				{if(look_up_inscope_noprint($2,0)==NULL){
														printf("\033[1;31m");
														printf("\nError in line %d - This var isn't declared in GLOBAL scope \n",yylineno);
														printf("\033[0m");
														//$$->sym = NULL;
														checkglob=1;
												}
												if(look_up_inscope_noprint($2,scope)!=NULL){
															$$ = lvalue_expr(look_up_inscope_noprint($2,scope));
												}
												printf("lvalue <-  ::ID\n");}
				|	tableitem 						{
														$$ = $1;
														printf("lvalue <-  tableitem\n");
														//printf("petaei seg;\n");
													}	
				;

tableitem		:	lvalue DOT ID 								{
																	$$ = member_item(Symtbl,scope,$1,$3,yylineno);
																	printf("tableitem <- lvalue.ID \n");
																}

				|	lvalue LEFT_SQ_BR expr RIGHT_SQ_BR 			{
																	$1 = emit_iftableitem(Symtbl,scope,$1,yylineno);
																	$$ = newexpr(tableitem_e);
																	$$->sym = $1->sym;						//diaf 10 sel 22
																	$$->index = $3;							//the index is the expression
																	printf("tableitem <- lvalue [ expr ] \n");
																}


				|	call DOT ID 								{	

																	$$ = member_item(Symtbl,scope,$1,$3,yylineno);
																	printf("tableitem <- call.ID \n");
																}

				|	call LEFT_SQ_BR expr RIGHT_SQ_BR 			{
																	$1 = emit_iftableitem(Symtbl,scope,$1,yylineno);
																	$$ = newexpr(tableitem_e);
																	$$->sym = $1->sym;						//diaf 10 sel 22
																	$$->index = $3;							//the index is the expression

																	printf("tableitem <- call [ expr ] \n");
																}
				;
										
call			:	call LEFT_PAR elist RIGHT_PAR 				{
																	$$ = make_call(Symtbl,scope,$1,$3,yylineno);

																	printf("call <- call ( elist ) \n");
																}				

				|	lvalue callsuffix
																	{	//allaksa to lvalue call suffix k ton elegxo apo katw ton efera edw
																		//$1->sym = look_up($1->sym->value.funcVal->name,scope);
																		if(check_type($1->sym)==1){

																				if(check_if_lib_noprint($1->sym->value.funcVal->name)==1){				//phase 3 to bala se sxolia
																					//	printf("to name einai*********************** %s\n",$1->sym->value.funcVal->name);
										   												libfunc=1;
										    											is_func=1;
																				}
																		}
																		//sel 28 diaf 10
																		
																		$1 = emit_iftableitem(Symtbl,scope,$1,yylineno);
																		if($2->method){
																			t = $1;
																			$1 = emit_iftableitem(Symtbl,scope,member_item(Symtbl,scope,t,$2->name,yylineno),yylineno);
																			$2->elist->next = t;  					//insert as frst argument (rerversed , so last)
																			//$2->elist = $2->elist->next;
																		}

																		$$ = make_call(Symtbl,scope,$1,$2->elist,yylineno);
																	
																		printf("call <- lvalue callsuffix \n");
																	}


				|	LEFT_PAR funcdef RIGHT_PAR LEFT_PAR elist RIGHT_PAR						{
																								func = newexpr(programfunc_e);
																								func->sym = $2;
																								$$ = make_call(Symtbl,scope,func,$5,yylineno);
																								printf("call <- ( funcdef )( elist )\n");
																							}
				;

callsuffix		:	normcall								{
																$$ = $1;
																printf("callsuffix <- normcall\n");
															}

				|	methodcall								{
																$$ = $1;
																printf("callsuffix <- methodcall\n");
															}
				;	

normcall		:	LEFT_PAR elist RIGHT_PAR				{
																//printf("seg edw\n");
																if($2==NULL){					//added this line because of the seg with for and call
																	$$ = (struct call*)malloc(sizeof(struct call));
																}
																$$->elist = $2;
																$$->method = 0;
																$$->name = NULL;
																printf("normcall <- ( elist )\n");
															}
				;


methodcall		:	DOUBLE_DOT ID LEFT_PAR elist RIGHT_PAR       	{
																		if($4==NULL){					//added this line because of the seg with for and call
																			$$ = (struct call*)malloc(sizeof(struct call));
																		}			
																		$$->elist = $4;
																		$$->method = 1;
																		$$->name = $2;
																		printf("methodcall <- ..ID ( elist )\n");
																	}
				;

elist			:	expr														{	
																					$$=$1;
																					printf("elist <- expr\n");
																				}
				|	expr COMMA elist														{
																								$$ = $1;
																								$$->next = $3;
																								printf("elist <- ,expr\n");
																							}
				|						{$$=NULL;}							//tskir : added because we must check when we create the table if its null to not make a tablesetelem
				;

/*elists			:	expr 													{	
																					$$ = $1;
																					printf("elist <- expr\n");
																				}
				|	expr COMMA elists											{
																								$$ = $1;
																								$$->next = $3;
																								printf("h timi p exei twra to $$ eiani %s\n",$$->val.varVal);
																								printf("elist <- ,expr\n");
																							}
				
				;*/


tablemake		: 	LEFT_SQ_BR elist RIGHT_SQ_BR			{
																t = newexpr(newtable_e);
																t->sym = newtemp(Symtbl,scope,yylineno);
																emit(tablecreate,t,NULL,NULL,0,yylineno);
																if($2!=NULL){
																	for(la=0 ; $2 ; $2=$2->next){
																		//printf("mpainei edw elist\n");
																		//emit(tablesetelem,t,newexpr_constnum(la++),$2,0,yylineno);
																		temps = newexpr(constnum_e);					//ftiaxnw to arg1 na einai auksanomeno apo 0...+ gia toys pinakes
																		temps->x = la++;								//gia na kanw ti leitourgia [1,2,3]
																		emit(tablesetelem,temps,$2,t,0,yylineno); //allaksa to apo panw analoga me to print p thelw na vgalw
																	}
																}
																$$ = t;
																printf("tablemake <- [ elist ]\n");
															}

				| 	LEFT_SQ_BR indexed RIGHT_SQ_BR			{	//sel 30 diaf 10
																t = newexpr(newtable_e);
																t->sym = newtemp(Symtbl,scope,yylineno);
																emit(tablecreate,t,NULL,NULL,0,yylineno);
																indexes = $2;
																while(indexes!=NULL){
																	//emit(tablesetelem,t,indexes,indexes->index,0,yylineno);
																	emit(tablesetelem,indexes,indexes->index,t,0,yylineno);				//tskir to allaksa giati eftiaxa to indexeddelem
																	indexes = indexes->next;
																}
																$$=t;	

																printf("tablemake <- [ indexed ]\n");
															}
				;

indexed			:	indexedelem									{
																	$$=$1;
																	printf("indexed <- indexedelem\n");
																}

				|	indexedelem COMMA indexed 					{
																	$$ = $1;
																	$$->next = $3;
																	printf("indexed <- ,indexedelem \n");
																}	
				;


indexedelem 	:	LEFT_BR expr COLON expr RIGHT_BR 	{	$$ = $2;
															$$->index = $4;							//to allaksa apo to apo katw giati den ekane print ara den epairne tin timi to index
															//$$->next = $4;
															printf("indexedelem <- {expr : expr}\n");}
				;

block			:	LEFT_BR RIGHT_BR 													{$$=NULL;}
				|	LEFT_BR{++scope;}stmt stmts RIGHT_BR{;hide(scope--);} 				{	
																							if($3==NULL){
																								$$ = $4;
																								//printf("mpike sto $3=NULL\n");
																							}else if($4 == NULL){
																								$$=$3;
																							//	printf("mpike sto $4=NULL\n");
																								//printf("to $$ einai = %s\n");
																							}
																							
																							//$$->next = $4;
																							printf("block <- { stmt }\n");
																						}	
				;


funcname		: ID 						{$$ = $1;}
				|							{$$ = randomfunc();}
				;

funcblockstart 	: 				{

									push(loopcounterstack,loopcounter);
									loopcounter=0;
								}
				;

funcblockend  	:				{
									
									loopcounter = pop(loopcounterstack);
									$$ = nextquad();
								}
				;



funcprefix 		:	FUNCTION funcname
											{

												{           
							                        ++check_if_open_func;
							                        ++block_func_signal;
							                            if(look_up_inscope($2,scope)==NULL){
															if(check_if_lib($2,yylineno)==0){
																insert_function(Symtbl,$2,scope,yylineno,USERFUNC);	
															}
														}else{
														    if(check_if_lib($2,yylineno)==1){
														     	//printf("\033[1;31m");
															   // printf("Error in line %d - Collision with library function %s\n",yylineno,$2);
															   // printf("\033[0m");
														   // }else{
															//    printf("\033[1;31m");
															//    printf("Error in  line %d - This var is already defined before\n",yylineno);	
															 //   printf("\033[0m");
														    }
														}
												}
												//diaf 10 sel 5
												$$ = look_up_inscope_noprint($2,scope);
												$$->value.funcVal->iaddress = nextquad();
												emit(jump,NULL,NULL,NULL,0,yylineno);						//tskir : added gia na kanei print to jump prin to funcstart
												emit(funcstart,NULL,NULL,lvalue_expr($$),0,yylineno);
												push(scopeoffsetStack,currscopeoffset());
												enterscopespace();
												resetformalargsoffset();
											}
				;




funcargs		:	LEFT_PAR {++scope;} idlist {--scope;}RIGHT_PAR funcblockstart
											{
												$$ = currscopeoffset();
												enterscopespace();						//entering function locals space
												resetfunctionlocaloffset();				//start counting locals from zero
											}
				;


funcbody		: 	block funcblockend
											{	--check_if_open_func;--block_func_signal;
												$$ = currscopeoffset();				//extract totalLocals 
												exitscopespace();	
											}
				;



funcdef			: 	funcprefix funcargs funcbody
											{
												//patchlabel($1,$3+2);
												//patchlabel($3,nextquad()+2);
												patchlabel($2,nextquad()+2);
												exitscopespace();										//exiting function definition space
												$$->value.funcVal->totalLocals = $funcbody;				//store locals in symbol entry
												int offset = pop(scopeoffsetStack);
												restorecurrscopeoffset(offset);
												$$ = $funcprefix;										//the function def returns the symbol
												emit(funcend,NULL,NULL,lvalue_expr($1),0,yylineno);	//lvalue expr to convert the symtable * to expr*

											}
				;

const			:	CONST_INT			{	
											temps = newexpr(constnum_e);
											temps->x = $1;
											//temps = newexpr_constnum($1);
											//$$ = newexpr_constnum($1);
											$$ = temps;
											//printf("to consti int einai %d\n",$$->x);
											printf("const <- CONST_INT \n");}
				|	CONST_REAL 			{	
											//$$ = newexpr_constnum($1);
											temps = newexpr(constnum_ereal);
											temps->y = $1;
											$$ = temps;
											//printf("to const double einai %f\n",temps->y);
											printf("const <- CONST_REAL \n");
										}

				|	STRING 				{	
											temps = newexpr(conststring_e);
											temps -> val.strConst = $1;
											$$ = temps;
											//printf("to conststring einai %s\n",$$->val.strConst);
											printf("const <- STRING \n");
										}
				|	NIL  				{
											$$ = newexpr(nil_e);
											printf("const <- NIL \n");
										}
				|	TRUE 				{
											//$$ = newexpr_constbool(1);
											temps = newexpr(constbool_e);
											temps->val.boolConst = 0;
											$$ = temps;
											//printf("tempstrue == %d\n",$$->x);

											
											printf("const <- TRUE \n");
										}
				|	FALSE 				{
											//$$ = newexpr_constbool(0);
											t = newexpr(constbool_e);
											t->val.boolConst = 1;
											$$ = t;
											//printf("tempsfalse == %d\n",$$->x);
											printf("const <- FALSE \n");
										}
				;



idlist			:	ID 										{if(look_up_inscope_noprint($1,scope)==NULL){
																	if(check_if_lib_noprint($1)==0){
																		insert_variable(Symtbl,$1,scope,yylineno,FORMAL);
																	}else{
																		printf("\033[1;31m");
																		printf("Error in line %d - Formal argument shadows a LIBFUNC\n",yylineno);
																		printf("\033[0m");
																	}
															}else{
																	if(check_if_lib_noprint($1)==1){
																		printf("\033[1;31m");
																		printf("Error in line %d - Formal shadows LIBFUNC\n",yylineno);
																		printf("\033[0m");
																	}else if(look_up_inscope_noprint($1,scope)->isActive==0){			
																	/*an exei ginei declared san formal sto idio scope alla se alli synartisi to ksana vazw*/
																		insert_variable(Symtbl,$1,scope,yylineno,FORMAL);
																	}else{
																		printf("\033[1;31m");
																		printf("Error in line %d - Variable already defined in this scope\n",yylineno);
																		printf("\033[0m");
																	}
															}
															
															}

															{printf("idlist <- ID \n");}

				|	ID COMMA idlists 						{if(look_up_inscope_noprint($1,scope)==NULL){
																	if(check_if_lib_noprint($1)==0){
																		insert_variable(Symtbl,$1,scope,yylineno,FORMAL);
																	}else{
																		printf("\033[1;31m");
																		printf("Error in line %d - Formal argument shadows a LIBFUNC\n",yylineno);
																		printf("\033[0m");
																	}
															}else{
																	if(check_if_lib_noprint($1)==1){
																		printf("\033[1;31m");
																		printf("Error in line %d - Formal shadows LIBFUNC\n",yylineno);
																		printf("\033[0m");
																	}else if(look_up_inscope_noprint($1,scope)->isActive==0){			
																	/*an exei ginei declared san formal sto idio scope alla se alli synartisi to ksana vazw*/
																		insert_variable(Symtbl,$1,scope,yylineno,FORMAL);
																	}else{printf("\033[1;31m");
																		printf("Error in line %d - Variable already defined in this scope\n",yylineno);
																		printf("\033[0m");
																	}
															}
															
															}		
															{printf("idlist <- ,ID \n");}
				|					{$$ = NULL;}
				;

idlists			:	ID 										{if(look_up_inscope_noprint($1,scope)==NULL){
																	if(check_if_lib_noprint($1)==0){
																		insert_variable(Symtbl,$1,scope,yylineno,FORMAL);
																	}else{
																		printf("\033[1;31m");
																		printf("Error in line %d - Formal argument shadows a LIBFUNC\n",yylineno);
																		printf("\033[0m");
																	}
															}else{
																	if(check_if_lib_noprint($1)==1){
																		printf("\033[1;31m");
																		printf("Error in line %d - Formal shadows LIBFUNC\n",yylineno);
																		printf("\033[0m");
																	}else if(look_up_inscope_noprint($1,scope)->isActive==0){			
																	/*an exei ginei declared san formal sto idio scope alla se alli synartisi to ksana vazw*/
																		insert_variable(Symtbl,$1,scope,yylineno,FORMAL);
																	}else{
																		printf("\033[1;31m");
																		printf("Error in line %d - Variable already defined in this scope\n",yylineno);
																		printf("\033[0m");
																	}
															}
															
															}		
															{printf("idlist <- ID \n");}
															
				| 	ID COMMA idlists						{if(look_up_inscope_noprint($1,scope)==NULL){
																	if(check_if_lib_noprint($1)==0){
																		insert_variable(Symtbl,$1,scope,yylineno,FORMAL);
																	}else{
																		printf("\033[1;31m");
																		printf("Error in line %d - Formal argument shadows a LIBFUNC\n",yylineno);
																		printf("\033[0m");
																	}
															}else{
																	if(check_if_lib_noprint($1)==1){
																		printf("\033[1;31m");
																		printf("Error in line %d - Formal shadows LIBFUNC\n",yylineno);
																		printf("\033[0m");
																	}else if(look_up_inscope_noprint($1,scope)->isActive==0){			
																	/*an exei ginei declared san formal sto idio scope alla se alli synartisi to ksana vazw*/
																		insert_variable(Symtbl,$1,scope,yylineno,FORMAL);
																	}else{
																		printf("\033[1;31m");
																		printf("Error in line %d - Variable already defined in this scope\n",yylineno);
																		printf("\033[0m");
																	}

															}
															
															}	
															{printf("idlist <- ,ID \n");}
				;


ifprefix		:	IF LEFT_PAR expr RIGHT_PAR			{	
															temps = newexpr(constbool_e);
															temps->x = 1;
															emit(if_eq,$3,temps,NULL,nextquad()+3,yylineno);
															$$ = nextquad();
															emit(jump,NULL,NULL,0,0,yylineno);
														}
				;

elseprefix		:	ELSE 								{
															$$ = nextquad();
															emit(jump,NULL,NULL,0,0,yylineno);
														}
				;

ifstmt 			:	ifprefix stmt 						{
															patchlabel($1,nextquad()+1);							//tskir : t allaksa gia na tupwnei 5 sto jump
														}

				|	ifprefix stmt elseprefix stmt 		{	//diaf 11 sel 12
															patchlabel($1,$3+2);
															patchlabel($3,nextquad()+1);
														}
				;

loopstart		:	{++loopcounter;}
				

loopend 		:	{--loopcounter;}
				

loopstmt 		:	loopstart stmt loopend {$$ = $2;}

break 			: 	BREAK SEMICOLON				{
													$$ = (struct stmt_t*)malloc(sizeof(struct stmt_t));
				                                  	make_stmt($$);
				                                    if(loop_signal==0 && scope==0){
				                                    	printf("\033[1;31m");
				                                        printf("Error in line %d - Use of 'break' while not in a loop\n",yylineno);
				                                        printf("\033[0m");
				                                    }else{                                 
												  		insertlist(breaklist_head,nextquad());
				                                    	emit(jump,NULL,NULL,NULL,0,yylineno);
				                                    	printf("stmt <- break;\n\n");
				                                    }
				                                }

continue 		: 	CONTINUE SEMICOLON			{
													$$ = (struct stmt_t*)malloc(sizeof(struct stmt_t));
				                                  	make_stmt($$);
				                                    if(loop_signal==0 && scope==0){
				                                   		printf("\033[1;31m");
				                                        printf("Error in line %d - Use of 'continue' while not in a loop\n",yylineno);
				                                        printf("\033[0m");
				                                    }else{
					                                    insertlist(contlist_head,nextquad());
					                                    emit(jump,NULL,NULL,NULL,0,yylineno);
					                                    printf("stmt <- continue;\n\n");
													}
				                                }


whilestart		: WHILE 								{
															$$ = nextquad();
														}
				;

whilecond 		:  	LEFT_PAR expr RIGHT_PAR				{
															emit(if_eq,$2,newexpr_constbool(0),NULL,nextquad()+3,yylineno);
															$$ = nextquad();
															emit(jump,NULL,NULL,0,0,yylineno);
														}
				;

whilestmt 		:	whilestart whilecond {loop_signal++;} loopstmt {loop_signal--;}					{ 			//sto $3 evgaze oti den exei ginei declare o typos
																											emit(jump,NULL,NULL,NULL,$1+1,yylineno);
																											patchlabel($2,nextquad()+1);
																											whilestmt_check_lists( breaklist_head,contlist_head,$1);				
																									}
				;				

				
N 				: 	{$$ = nextquad(); emit(jump,NULL,NULL,0,0,yylineno);}	//paragei ena unfinished jump
				;

M 				:	{$$ = nextquad();}
				;


forprefix		: 		FOR LEFT_PAR elist SEMICOLON M expr SEMICOLON 					{
																							tempstmt = malloc(sizeof(struct stmt_t));
																							tempstmt->test = $5;
																							tempstmt->enter = nextquad();
																							$$ = tempstmt;
																							temps = newexpr(constbool_e);
																							temps->val.boolConst = 0;
																							emit(if_eq,$6,temps,0,0,yylineno);
																						}
				;

forstmt 			: 		forprefix N elist RIGHT_PAR N loopstmt N 					{
																							patchlabel($1->enter,$5+2);		//true jump
																							patchlabel($2,nextquad()+1);	//false jump
																							patchlabel($5,$1->test+1);		//loop jump
																							patchlabel($7,$2+2);			//closure jump
																							forstmt_check_lists(breaklist_head,contlist_head,$2);   
																						}
					;

returnstmt		:	RETURN SEMICOLON 			{							if(check_if_open_func==0){
																				printf("\033[1;31m");
										                                        printf("Error in line %d - Use of 'return' without a function \n",yylineno);
										                                        printf("\033[0m");

																			}else{
																				emit(ret,NULL,NULL,NULL,0,yylineno);
																				emit(jump,NULL,NULL,NULL,nextquad()+2,yylineno);
																				printf("returnstmt <- return; \n");
																			}
												}

				| 	RETURN {retFLAG=1;}expr SEMICOLON{retFLAG=0;}		{	
																			if(check_if_open_func==0){
																				printf("\033[1;31m");
										                                        printf("Error in line %d - Use of 'return' without a function \n",yylineno);
										                                        printf("\033[0m");

																			}else{
																				emit(ret,NULL,NULL,$3,0,yylineno);
																				//patchlabel($$,nextquad()+1);
																				emit(jump,NULL,NULL,NULL,nextquad()+3,yylineno);
																				printf("returnstmt <- return expr; \n");
																			}
																		}
				;



%%
/*programs   -   epilogos   */

int yyerror(char* yaccProvidedMessage){
	fprintf(stderr, "%s: at line %, before token: %s\n",yaccProvidedMessage,yylineno,yytext);
	printf("INPUT NOT VALID\n");
}


int main(int argc, char **argv) {
	int x;
	contlist_head = malloc(sizeof(struct intList));
	breaklist_head = malloc(sizeof(struct intList));
	Symtbl = new_Symtable();
	makestack();

	yyin = stdin;
	if(argc>1){
        if(!(yyin=fopen(argv[1],"r"))){
            fprintf(stderr, "Cannot read file: %s\n",argv[1]);
            return 1;
        }
    }
			yyparse();
			printf("\n");
			printSymtable();
			printquads();
			generate_all();
			print_tables();
			print_instructions();
			//printtables();
			avmbinaryfile();
		return 0;
}
