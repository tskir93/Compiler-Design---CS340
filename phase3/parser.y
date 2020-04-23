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

struct expr* func;
struct expr* t;
struct expr* val;
struct expr* temps;
struct expr* indexes;

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
//%type <unsignedVal> N
//%type <unsignedval> M
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
%type <exprVal> indexed
%type <unsignedVal> ifprefix
%type <unsignedVal> elseprefix
%type <unsignedVal> whilestart
%type <unsignedVal> whilecond
%type <stmtVal> loopstmt
%type <stmtVal> continue
%type <stmtVal> break
%type <stmtVal> stmts
%type <stmtVal> returnstmt

/*tou lew na perimenei ena sfalma shift/reduce poy einai to ifstmt*/
%expect 1


%%
/*rules*/
/*ta deksia meri ginontai reduced sta aristera meri otan vrethoun kata ti diarkeia tis suntaktikis analusis*/

program 		:	stmts	

/*ta statements einai 0 h perissotera kai gia na to petuxoyme auto prepei na ftiaksoume allo ena kanona*/
/*stmts			: 	stmt stmts
				|
				;	*/

stmts 			: 	stmts stmt  			{
												//$$->breakList = mergelist($1->breakList,$2->breakList);
												//$$->contList = mergelist($1->contList,$2->contList);
											}
				|	stmt 		{$$=$1;}
				;				

stmt			:	expr SEMICOLON			{printf("stmt <- expr;\n\n");}
				|	ifstmt					{printf("stmt <- ifstmt\n\n");}
				|	whilestmt				{printf("stmt <- whilestmt\n\n");}
				|	forstmt					{printf("stmt <- forstmt\n\n");}
				|	returnstmt				{printf("stmt <- returnstmt\n\n");}
				|	break 					{}
				|	continue 				{}
				|	block					{printf("stmt <- block\n\n");}
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
															}
															printf("expr <- expr op expr\n");
														}else{
																printf("\033[1;31m");
					                                        	printf("Error in line %d - This type of expr could not be used with PERCENTAGE expr\n",yylineno);
					                                        	printf("\033[0m");
														}
													}

				|	expr GREATER_THAN expr				{
															if(check_corr_type($1)==0 && check_corr_type($3)==0){
																$$ = newexpr(boolexpr_e);
																$$ ->sym = newtemp(Symtbl,scope,yylineno);

																emit(if_greater,$1,$3,NULL,nextquad()+3,yylineno);
																emit(assign,newexpr_constbool(0),NULL,$$,0,yylineno);
																emit(jump,NULL,NULL,NULL,nextquad()+2,yylineno);
																emit(assign,newexpr_constbool(1),NULL,$$,0,yylineno);
																printf("expr <- expr op expr\n");
															}else{
																printf("\033[1;31m");
					                                        	printf("Error in line %d - This type of expr could not be used with GREATER THAN expr\n",yylineno);
					                                        	printf("\033[0m");
															}
														}

				|	expr GR_EQ expr				{		

														if(check_corr_type($1)==0 && check_corr_type($3)==0){
															$$ = newexpr(boolexpr_e);
															$$ ->sym = newtemp(Symtbl,scope,yylineno);

															emit(if_greatereq,$1,$3,NULL,nextquad()+3,yylineno);
															emit(assign,newexpr_constbool(0),NULL,$$,0,yylineno);
															emit(jump,NULL,NULL,NULL,nextquad()+2,yylineno);
															emit(assign,newexpr_constbool(1),NULL,$$,0,yylineno);
															printf("expr <- expr op expr\n");
														}else{
																printf("\033[1;31m");
					                                        	printf("Error in line %d - This type of expr could not be used with GREATER EQUAL expr\n",yylineno);
					                                        	printf("\033[0m");
														}
												}

				|	expr LESS_THAN expr				{
														if(check_corr_type($1)==0 && check_corr_type($3)==0){
															$$ = newexpr(boolexpr_e);
															$$ ->sym = newtemp(Symtbl,scope,yylineno);

															emit(if_less,$1,$3,NULL,nextquad()+3,yylineno);
															emit(assign,newexpr_constbool(0),NULL,$$,0,yylineno);
															emit(jump,NULL,NULL,NULL,nextquad()+2,yylineno);
															emit(assign,newexpr_constbool(1),NULL,$$,0,yylineno);
															printf("expr <- expr op expr\n");
														}else{
																printf("\033[1;31m");
					                                        	printf("Error in line %d - This type of expr could not be used with LESS THAN expr\n",yylineno);
					                                        	printf("\033[0m");
														}
													}

				|	expr LE_EQ expr				{
														if(check_corr_type($1)==0 && check_corr_type($3)==0){
															$$ = newexpr(boolexpr_e);
															$$ ->sym = newtemp(Symtbl,scope,yylineno);

															emit(if_lesseq,$1,$3,NULL,nextquad()+3,yylineno);
															emit(assign,newexpr_constbool(0),NULL,$$,0,yylineno);
															emit(jump,NULL,NULL,NULL,nextquad()+2,yylineno);
															emit(assign,newexpr_constbool(1),NULL,$$,0,yylineno);
															printf("expr <- expr op expr\n");
														}else{
																printf("\033[1;31m");
					                                        	printf("Error in line %d - This type of expr could not be used with LESS EQUAL expr\n",yylineno);
					                                        	printf("\033[0m");
														}
													}

				|	expr EQUAL expr				{
														if(check_corr_type($1)==0 && check_corr_type($3)==0){
															$$ = newexpr(boolexpr_e);
															$$ ->sym = newtemp(Symtbl,scope,yylineno);

															emit(if_eq,$1,$3,NULL,nextquad()+3,yylineno);
															emit(assign,newexpr_constbool(0),NULL,$$,0,yylineno);
															emit(jump,NULL,NULL,NULL,nextquad()+2,yylineno);
															emit(assign,newexpr_constbool(1),NULL,$$,0,yylineno);
															printf("expr <- expr op expr\n");
														}else{
																printf("\033[1;31m");
					                                        	printf("Error in line %d - This type of expr could not be used with EQUAL expr\n",yylineno);
					                                        	printf("\033[0m");
														}	
												}

				|	expr NOTEQUAL expr				{
														if(check_corr_type($1)==0 && check_corr_type($3)==0){
															$$ = newexpr(boolexpr_e);
															$$ ->sym = newtemp(Symtbl,scope,yylineno);

															emit(if_noteq,$1,$3,NULL,nextquad()+3,yylineno);
															emit(assign,newexpr_constbool(0),NULL,$$,0,yylineno);
															emit(jump,NULL,NULL,NULL,nextquad()+2,yylineno);
															emit(assign,newexpr_constbool(1),NULL,$$,0,yylineno);
															printf("expr <- expr op expr\n");
														}else{
																printf("\033[1;31m");
					                                        	printf("Error in line %d - This type of expr could not be used with NOT EQUAL expr\n",yylineno);
					                                        	printf("\033[0m");
														}	
													}

				|	expr AND expr				{
													if(check_corr_type($1)==0 && check_corr_type($3)==0){
														$$ = newexpr(boolexpr_e);
														$$->sym = newtemp(Symtbl,scope,yylineno);
														emit(and,$1,$3,$$,0,yylineno);
														printf("expr <- expr op expr\n");
														printf("expr <- expr op expr\n");
													}else{
																printf("\033[1;31m");
					                                        	printf("Error in line %d - This type of expr could not be used with AND expr\n",yylineno);
					                                        	printf("\033[0m");
													}	
												}

				|	expr OR expr				{
													if(check_corr_type($1)==0 && check_corr_type($3)==0){
														$$ = newexpr(boolexpr_e);
														$$->sym = newtemp(Symtbl,scope,yylineno);
														emit(or,$1,$3,$$,0,yylineno);
														printf("expr <- expr op expr\n");
													}else{
																printf("\033[1;31m");
					                                        	printf("Error in line %d - This type of expr could not be used with OR expr\n",yylineno);
					                                        	printf("\033[0m");
													}
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
														emit(not,$2,NULL,$$,0,yylineno);
														printf("term <- not expr \n");
													}

				|	DOUBLE_PLUS lvalue				{
														if(check_type_for_print($2->sym->type)==1){
															printf("\033[1;31m");
															printf("Error in line %d - DOUBLE_PLUS lvalue action could not be used with Functions\n",yylineno);}
															printf("\033[0m");
															printf("term <- ++lvalue \n");

															if(check_arith($2)==0){
																if($2->type == tableitem_e){
																	temps = emit_iftableitem(Symtbl,scope,$2,yylineno);
																	emit(add,temps,newexpr_constnum(1),temps,0,yylineno);
																	emit(tablesetelem,$2,$2->index,temps,0,yylineno);
																}else{
																	emit(add,$2,newexpr_constnum(1),temps,0,yylineno);
																	temps = newexpr(arithexpr_e);
																	temps->sym = newtemp(Symtbl,scope,yylineno);
																	emit(assign,$2,NULL,temps,0,yylineno);
																}
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
															if($1->type == tableitem_e){
																val = emit_iftableitem(Symtbl,scope,$1,yylineno);
																emit(assign,val,NULL,temps,0,yylineno);
																emit(add,val,newexpr_constnum(1),val,0,yylineno);
																emit(tablesetelem,$1,$1->index,val,0,yylineno);
															}else{
																emit(assign,$1,NULL,temps,0,yylineno);
																emit(add,$1,newexpr_constnum(1),$1,0,yylineno);
															}
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
																	emit(sub,$2,newexpr_constnum(1),temps,0,yylineno);
																	temps = newexpr(arithexpr_e);
																	temps->sym = newtemp(Symtbl,scope,yylineno);
																	emit(assign,$2,NULL,temps,0,yylineno);
																}
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
															if($1->type == tableitem_e){
																val = emit_iftableitem(Symtbl,scope,$1,yylineno);
																emit(assign,val,NULL,temps,0,yylineno);
																emit(sub,val,newexpr_constnum(1),val,0,yylineno);
																emit(tablesetelem,$1,$1->index,val,0,yylineno);
															}else{
																emit(assign,$1,NULL,temps,0,yylineno);	
																emit(sub,$1,newexpr_constnum(1),$1,0,yylineno);
															}
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
																printf("mpaieni edwdwwd\n");
																	//emit(tablesetelem,$1,$1->index,$3,0,yylineno);		//lvalue[index] =expr allaksa autp edwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww***** gia toys pinakes
																	emit(tablesetelem,$1->index,$3,$1,0,yylineno);
																	temps = emit_iftableitem(Symtbl,scope,$1,yylineno);
																	temps->type = assignexpr_e;
																}else{
																printf("mpaineiedcvw\n");
																	emit(assign,$3,NULL,$1,0,yylineno);
																	temps = newexpr(assignexpr_e);
																	temps->sym =newtemp(Symtbl,scope,yylineno);
																	emit(assign,$1,NULL,temps,0,yylineno);
																}
																$$=temps;
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
													$$=$1;
													printf("primary <- tablemake \n");
												}
				|	LEFT_PAR funcdef RIGHT_PAR 			{
															$$ = newexpr(programfunc_e);
															$$->sym = $2;
															printf("primary <- ( funcdef ) \n");
														}

				|	const 						{	
													$$=$1;
													printf("to const eiani %d\n",$$->x);
													printf("primary <- const \n");
												}
				;


lvalue			:	ID 							{	
                                                    if(look_up_inscope($1,scope)==NULL){
                                                        if(retFLAG==0){
                                                        	
                                                            if(check_if_open_func==0){
                                                                if(look_up($1,scope-1)==NULL){
                                                                	printf("mpainei edw 2\n");
														            if(check_if_lib($1,yylineno)==0 && libfunc==0){
															            insert_variable(Symtbl,$1,scope,yylineno,check_Var_type_local(scope));
															            //printf("%s variable Scope %d\n",$1, scope);
															        }
														            
														        
														        }else if(look_up($1,scope-1)!=NULL){
														            if(look_up($1,scope-1)->type==GLOBAL){
														                //printf("Ok %s is a global var\n",$1);
														                //printSymtable();
														            }else if(look_up($1,scope-1)->type==LOCALE){
														                //printf("Ok %s refers to the previous variable and is visible\n",$1);
														            }
														            
														        }
														        
                                                            }else if(check_if_open_func!=0){
                                                           
                                                                if(look_up($1,scope-1)==NULL){
                                                                    if(check_if_lib($1,yylineno)==0 && libfunc==0){
															            insert_variable(Symtbl,$1,scope,yylineno,check_Var_type_local(scope));
															            //printf("%s variable Scope %d\n",$1, scope);
															        }
														            
														            
														        }else if(look_up($1,scope-1)!=NULL){
														        printf("mpainei edw 5\n");
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
													    printf("mpainei edw 6\n");
													        if(check_if_open_func==0 && scope==0){
													        	printf("\033[1;31m");
													            printf("Error in line %d - Use of 'return' while not in a function\n",yylineno);
													            printf("\033[0m");
													            //printSymtable();
													        }else if(check_if_open_func!=0){
													            if(look_up($1,scope-1)==NULL){
													                if(check_if_lib($1,yylineno)==0 && libfunc==0){
															            insert_variable(Symtbl,$1,scope,yylineno,check_Var_type_local(scope));
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
                                                    // $$ = look_up_inscope_noprint($1,scope); 
                                                    if(look_up_inscope($1,scope)!=NULL && retFLAG!=0 && scope==0){
                                                    		printf("\033[1;31m");
													            printf("Error in line %d - Use of 'return' while not in a function\n",yylineno);
													            printf("\033[0m");
                                                    }
													//printSymtable();
													//toy dinw tin timi poy exei to lvalue gia na tin xrisimopoiisw meta stoys kanones lvalue ++ klp
														if(look_up_inscope_noprint($1,scope)!=NULL){
															$$ = lvalue_expr(look_up_inscope_noprint($1,scope));
														}
														printf("lvalue <- ID \n");
												    }

				|	LOCAL ID 					{if(look_up_inscope_noprint($2,scope)==NULL && retFLAG==0){ 
															if(check_if_lib($2,yylineno)==0){
															printf("mpainei edw\n");
																insert_variable(Symtbl,$2,scope,yylineno,check_Var_type_local(scope));
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
																	printf("tableitem <- lvalue { expr } \n");
																}

				|	call DOT ID 								{printf("tableitem <- call.ID \n");}
				|	call LEFT_SQ_BR expr RIGHT_SQ_BR 			{printf("tableitem <- call { expr } \n");}
				;
										/*tsekarw px tin print(x) kai an einai libfunc opws i print theloyme apla na kanei lookup sto x kai oxi insert*/
call			:	call LEFT_PAR elist RIGHT_PAR 				{
																	$$ = make_call(Symtbl,scope,$1,$3,yylineno);
																	printf("call <- call ( elist ) \n");
																}				

				|	lvalue callsuffix
																	{	//allaksa to lvalue call suffix k ton elegxo apo katw ton efera edw
																		if(check_type($1->sym)==1){
																				if(check_if_lib_noprint($1->sym->value.funcVal->name)==1){				//phase 3 to bala se sxolia
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
																$$->elist = $2;
																$$->method = 0;
																$$->name = NULL;
																printf("normcall <- ( elist )\n");
															}
				;


methodcall		:	DOUBLE_DOT ID LEFT_PAR elist RIGHT_PAR       	{
																		$$->elist = $4;
																		$$->method = 1;
																		$$->name = $2;
																		printf("methodcall <- ..ID ( elist )\n");
																	}
				;

elist			:	expr														{printf("elist <- expr\n");}
				|	expr COMMA elist														{printf("elist <- ,expr\n");}
				|
				;

elists			:	expr
				|	expr COMMA elists
				|
				;


tablemake		: 	LEFT_SQ_BR elist RIGHT_SQ_BR			{
																t = newexpr(newtable_e);
																t->sym = newtemp(Symtbl,scope,yylineno);
																emit(tablecreate,t,NULL,NULL,0,yylineno);
																for(la=0 ; $2 ; $2=$2->next){
																	emit(tablesetelem,t,newexpr_constnum(la++),$2,0,yylineno);
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
																	emit(tablesetelem,t,indexes,indexes->index,0,yylineno);
																	indexes = indexes->next;
																}
																$$=t;	

																printf("tablemake <- [ indexed ]\n");
															}
				;

indexed			:	indexedelem									{printf("indexed <- indexedelem\n");}
				|	indexedelem COMMA indexed 					{printf("indexed <- ,indexedelem \n");}	
				;


indexedelem 	:	LEFT_BR expr COLON expr RIGHT_BR 	{printf("indexedelem <- {expr : expr}\n");}
				;

block			:	LEFT_BR RIGHT_BR
				|	LEFT_BR{++scope;} stmt stmts RIGHT_BR{;hide(scope--);} 				{printf("block <- { stmt }\n");}	
				;


funcname		: ID 						{$$ = $1;}
				|							{$$ = randomfunc();}
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
														    }else{
															    printf("\033[1;31m");
															    printf("Error in  line %d - This var is already defined before\n",yylineno);	
															    printf("\033[0m");
														    }
														} //printSymtable();
												}
												//diaf 10 sel 5
												$$ = look_up_inscope_noprint($2,scope);
												$$->value.funcVal->iaddress = nextquad();
												emit(funcstart,$<exprVal>$,NULL,NULL,0,yylineno);
												push(scopeoffsetStack,currscopeoffset());
												enterscopespace();
												resetformalargsoffset();
											}
				;

funcblockstart 	: 				{
									push(loopcounterstack,loopcounter);
									loopcounter=0;
								}
				;

funcblockend  	:				{
									loopcounter = pop(loopcounterstack);
								}
				;



funcargs		:	LEFT_PAR {++scope;} idlist {--scope;}RIGHT_PAR funcblockstart
											{
												enterscopespace();						//entering function locals space
												resetfunctionlocaloffset();				//start counting locals from zero
											}
				;


funcbody		: 	block funcblockend
											{--check_if_open_func;--block_func_signal;
												$$ = currscopeoffset();				//extract totalLocals 
												exitscopespace();
											}
				;



funcdef			: 	funcprefix funcargs funcbody
											{
												exitscopespace();										//exiting function definition space
												$$->value.funcVal->totalLocals = $funcbody;				//store locals in symbol entry
												int offset = pop(scopeoffsetStack);
												restorecurrscopeoffset(offset);
												$$ = $funcprefix;										//the function def returns the symbol
												emit(funcend, $<exprVal>1 ,NULL,NULL,0,yylineno);

											}
				;

const			:	CONST_INT			{	
											temps = newexpr(constnum_e);
											temps->x = $1;
											//temps = newexpr_constnum($1);
											//$$ = newexpr_constnum($1);
											$$ = temps;
											printf("to consti int einai %d\n",$$->x);
											printf("const <- CONST_INT \n");}
				|	CONST_REAL 			{	
											$$ = newexpr_constnum($1);
											//printf("to consti int einai %d\n",$$->x);
											printf("const <- CONST_REAL \n");
										}

				|	STRING 				{	
											newexpr_conststring($1);
											printf("const <- STRING \n");
										}
				|	NIL  				{
											newexpr(nil_e);
											printf("const <- NIL \n");
										}
				|	TRUE 				{
											newexpr_constbool(1);
											printf("const <- TRUE \n");
										}
				|	FALSE 				{
											newexpr_constbool(0);
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
																	}else{printf("\033[1;31m");
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
				|
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
																	}else{printf("\033[1;31m");
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
																	}else{printf("\033[1;31m");
																		printf("Error in line %d - Variable already defined in this scope\n",yylineno);
																		printf("\033[0m");
																	}

															}
															
															}	
															{printf("idlist <- ,ID \n");}
				;

/*ifstmt			: 	IF LEFT_PAR expr RIGHT_PAR stmt  {printf("ifstmt <- if ( expr ) stmt \n");}
				|   IF LEFT_PAR expr RIGHT_PAR stmt ELSE stmt {printf("ifstmt <- if ( expr ) stmt \n");}
				;*/

ifprefix		:	IF LEFT_PAR expr RIGHT_PAR			{
															emit(if_eq,$3,newexpr_constbool(1),NULL,nextquad()+2,yylineno);
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
															patchlabel($1,nextquad());
														}

				|	ifprefix stmt elseprefix stmt 		{	//diaf 11 sel 12
															patchlabel($1,$3+1);
															patchlabel($3,nextquad());
														}
				;

/*whilestmt		:	WHILE LEFT_PAR expr RIGHT_PAR {loop_signal++;} stmt {loop_signal--;} 		{printf("whilestmt <- while ( expr ) stmt \n");}
				;*/

loopstart		:	{++loopcounter;}
				

loopend 		:	{--loopcounter;}
				

loopstmt 		:	loopstart stmt loopend {$$ = $2;}

break 			: 	BREAK SEMICOLON				{
				                                    if(loop_signal==0 && scope==0){
				                                    	printf("\033[1;31m");
				                                        printf("Error in line %d - Use of 'break' while not in a loop\n",yylineno);
				                                        printf("\033[0m");
				                                    }
				                                    make_stmt($$);
				                                    $$->breakList = newlist(nextquad());
				                                    emit(jump,NULL,NULL,NULL,0,yylineno);
				                                    printf("stmt <- break;\n\n");
				                                }

continue 		: 	CONTINUE SEMICOLON			{
				                                    if(loop_signal==0 && scope==0){
				                                   		printf("\033[1;31m");
				                                        printf("Error in line %d - Use of 'break' while not in a loop\n",yylineno);
				                                        printf("\033[0m");
				                                    }
				                                    make_stmt($$);
				                                    $$->contList = newlist(nextquad());
				                                    emit(jump,NULL,NULL,NULL,0,yylineno);
				                                    printf("stmt <- continue;\n\n");
				                                }


whilestart		: WHILE 								{
															$$ = nextquad();
														}
				;

whilecond 		:  	LEFT_PAR expr RIGHT_PAR				{
															emit(if_eq,$2,newexpr_constbool(1),NULL,nextquad()+2,yylineno);
															$$ = nextquad();
															emit(jump,NULL,NULL,0,0,yylineno);
														}
				;

whilestmt 		:	whilestart whilecond {loop_signal++;} loopstmt {loop_signal--;}					{ 			//sto $3 evgaze oti den exei ginei declare o typos
																											emit(jump,NULL,NULL,$<exprVal>1,0,yylineno);
																											patchlabel($2,nextquad());
																											patchlist($4->breakList,nextquad());
																											patchlist($4->contList,$1);		
																									}
				;				

				

forstmt			:	FOR LEFT_PAR elist SEMICOLON expr SEMICOLON elist RIGHT_PAR {loop_signal++;} stmt {loop_signal--;} {printf("forstmt <- for ( elist; expr; elist ) stmt \n");}
				;

returnstmt		:	RETURN SEMICOLON 			{
													emit(ret,NULL,NULL,NULL,0,yylineno);
													printf("returnstmt <- return; \n");
												}

				| 	RETURN {retFLAG=1;}expr SEMICOLON{retFLAG=0;}		{
																			emit(ret,NULL,NULL,$3,0,yylineno);			//to $2 eiani to retflag logika giati vgazei error
																			printf("returnstmt <- return expr; \n");
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
	Symtbl = new_Symtable();
	makestack();


	yyin = stdin;
	/*
	if(argc>1){
        if(!(yyin=fopen(argv[1],"r"))){
            fprintf(stderr, "Cannot read file: %s\n",argv[1]);
            return 1;
        }
    }*/
		
		

			yyparse();
			printf("\n");
			printSymtable();
			printquads();
			//printSymtable_byscope();
		
		return 0;
}
