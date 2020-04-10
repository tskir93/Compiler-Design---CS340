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
int ret = 0; 	
/* metavliti gia ton elegxo an mesolavei sunartisi */
int check_if_open_func = 0;
int loop_signal = 0;
int block_func_signal = 0;
int assign_op = 0;
int is_func = 0;
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

%type <exprNode> lvalue
%type <stringVal> expr
%type <stringVal> assignexpr
%type <stringVal> idlist
%type <stringVal> call

/*tou lew na perimenei ena sfalma shift/reduce poy einai to ifstmt*/
%expect 1


%%
/*rules*/
/*ta deksia meri ginontai reduced sta aristera meri otan vrethoun kata ti diarkeia tis suntaktikis analusis*/

program 		:	stmts	

/*ta statements einai 0 h perissotera kai gia na to petuxoyme auto prepei na ftiaksoume allo ena kanona*/
stmts			: 	stmt stmts
				|
				;				

stmt			:	expr SEMICOLON			{printf("stmt <- expr;\n\n");}
				|	ifstmt					{printf("stmt <- ifstmt\n\n");}
				|	whilestmt				{printf("stmt <- whilestmt\n\n");}
				|	forstmt					{printf("stmt <- forstmt\n\n");}
				|	returnstmt				{printf("stmt <- returnstmt\n\n");}
				|	BREAK SEMICOLON				{
				                                    if(loop_signal==0 && scope==0){
				                                    	printf("\033[1;31m");
				                                        printf("Error in line %d - Use of 'break' while not in a loop\n",yylineno);
				                                        printf("\033[0m");
				                                    }
				                                    printf("stmt <- break;\n\n");}
				|	CONTINUE SEMICOLON			{
				                                    if(loop_signal==0 && scope==0){
				                                   		printf("\033[1;31m");
				                                        printf("Error in line %d - Use of 'break' while not in a loop\n",yylineno);
				                                        printf("\033[0m");
				                                    }
				                                    printf("stmt <- continue;\n\n");}
				|	block					{printf("stmt <- block\n\n");}
				|	funcdef					{printf("stmt <- funcdef\n\n");}
				| 	SEMICOLON				{printf("stmt <- ;\n\n");}
				;

expr			:	assignexpr						{   

                                                        printf("expr <- assignexpr\n");}
				|	expr PLUS expr				{printf("expr <- expr op expr\n");}
				|	expr MINUS expr				{printf("expr <- expr op expr\n");}
				|	expr MULTIPLY expr				{printf("expr <- expr op expr\n");}
				|	expr DEVIDE	expr				{printf("expr <- expr op expr\n");}
				|	expr PERCENTAGE expr				{printf("expr <- expr op expr\n");}
				|	expr GREATER_THAN expr				{printf("expr <- expr op expr\n");}
				|	expr GR_EQ expr				{printf("expr <- expr op expr\n");}
				|	expr LESS_THAN expr				{printf("expr <- expr op expr\n");}
				|	expr LE_EQ expr				{printf("expr <- expr op expr\n");}
				|	expr EQUAL expr				{printf("expr <- expr op expr\n");}
				|	expr NOTEQUAL expr				{printf("expr <- expr op expr\n");}
				|	expr AND expr				{printf("expr <- expr op expr\n");}
				|	expr OR expr				{printf("expr <- expr op expr\n");}
				|	term 							{printf("expr <- term\n");}
				;



term			: 	LEFT_PAR expr RIGHT_PAR			{printf("term <- ( expr )\n");}
				|	MINUS expr %prec UMINUS			{printf("term <- -expr \n");}
				|	NOT expr						{printf("term <- not expr \n");}

				|	DOUBLE_PLUS lvalue				{
														if(check_type_for_print($2->type)==1){
															printf("\033[1;31m");
															printf("Error in line %d - DOUBLE_PLUS lvalue action could not be used with Functions\n",yylineno);}
															printf("\033[0m");
															printf("term <- ++lvalue \n");}
															

				|	lvalue DOUBLE_PLUS				{
														if(check_type_for_print($1->type)==1){
															printf("\033[1;31m");
															printf("Error in line %d - lvalue DOUBLE_PLUS action could not be used with Functions\n",yylineno);
															printf("\033[0m");
														}
														printf("term <- lvalue++ \n");}

				|	DOUBLE_MINUS lvalue				{
														if(check_type_for_print($2->type)==1){
															printf("\033[1;31m");
															printf("Error in line %d - DOUBLE_MINUS lvalue action could not be used with Functions\n",yylineno);}
															printf("\033[0m");
															printf("term <- --lvalue \n");}

				|	lvalue DOUBLE_MINUS				{
														if(check_type_for_print($1->type)==1){
															printf("\033[1;31m");
															printf("Error in line %d - lvalue DOUBLE_MINUS action could not be used with Functions\n",yylineno);}
															printf("\033[0m");
															printf("term <- lvalue-- \n");}

				|	primary							{printf("term <- primary \n");}
				;

assignexpr		:	lvalue 			{if($1!=NULL ){
													if(check_type_for_print($1->type)==1){
															printf("\033[1;31m");
															printf("Error in line %d - ASSIGN action could not be used with Functions\n",yylineno);
															printf("\033[0m");
													}}}



							ASSIGN expr				 
															{printf("assignexpr <- lvalue = expr \n");}

				;

primary			:	lvalue						{printf("primary <- lvalue \n");}
				|	call 						{printf("primary <- call \n");}
				|	objectdef 					{printf("primary <- objectdef \n");}
				|	LEFT_PAR funcdef RIGHT_PAR 			{printf("primary <- ( funcdef ) \n");}
				|	const 						{printf("primary <- const \n");}
				;


lvalue			:	ID 							{	
                                                    if(look_up_inscope($1,scope)==NULL){
                                                        if(ret==0){
                                                        	
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
                                                         
													    }else if(ret!=0){
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
                                                    if(look_up_inscope($1,scope)!=NULL && ret!=0 && scope==0){
                                                    		printf("\033[1;31m");
													            printf("Error in line %d - Use of 'return' while not in a function\n",yylineno);
													            printf("\033[0m");
                                                    }
													//printSymtable();
													//toy dinw tin timi poy exei to lvalue gia na tin xrisimopoiisw meta stoys kanones lvalue ++ klp
														if(look_up_inscope_noprint($1,scope)!=NULL){
															$$ = look_up_inscope_noprint($1,scope);
														}
														printf("lvalue <- ID \n");
												    }

				|	LOCAL ID 					{if(look_up_inscope_noprint($2,scope)==NULL && ret==0){ 
															if(check_if_lib($2,yylineno)==0){
															printf("mpainei edw\n");
																insert_variable(Symtbl,$2,scope,yylineno,check_Var_type_local(scope));
															}
													}else if(look_up_inscope_noprint($2,scope)!=NULL ){
														//printf("OK found locally.\n");
													}

													//toy dinw tin timi poy exei to lvalue gia na tin xrisimopoiisw meta stoys kanones lvalue ++ klp
													$$ = look_up_inscope_noprint($2,scope);
													printf("lvalue <-  LOCAL ID\n");}

				|	DOUBLE_COL ID 				{if(look_up_inscope_noprint($2,0)==NULL){
														printf("\033[1;31m");
														printf("\nError in line %d - This var isn't declared in GLOBAL scope \n",yylineno);
														printf("\033[0m");
												}
												$$ = look_up_inscope_noprint($2,0);
												printf("lvalue <-  ::ID\n");}//}
				|	member 						{printf("lvalue <-  member\n");}	
				;

member			:	lvalue DOT ID 								{printf("member <- lvalue.ID \n");}
				|	lvalue LEFT_SQ_BR expr RIGHT_SQ_BR 			{printf("member <- lvalue { expr } \n");}
				|	call DOT ID 								{printf("member <- call.ID \n");}
				|	call LEFT_SQ_BR expr RIGHT_SQ_BR 			{printf("member <- call { expr } \n");}
				;

call			:	call LEFT_PAR elist RIGHT_PAR 				{printf("call <- call ( elist ) \n");}				/*tsekarw px tin print(x) kai an einai libfunc opws i print theloyme apla na kanei lookup sto x kai oxi insert*/
				|	lvalue {if(check_type($1)==1){
								if(check_if_lib_noprint($1->value.funcVal->name)==1){
								    libfunc=1;
								    is_func=1;
								}
							}} callsuffix
																	{printf("call <- lvalue callsuffix \n");}


				|	LEFT_PAR funcdef RIGHT_PAR LEFT_PAR elist RIGHT_PAR						 {printf("call <- ( funcdef )( elist )\n");}
				;

callsuffix		:	normcall		
															{printf("callsuffix <- normcall\n");}
				|	methodcall								{printf("callsuffix <- methodcall\n");}
				;	

normcall		:	LEFT_PAR elist RIGHT_PAR				{printf("normcall <- ( elist )\n");}
				;


methodcall		:	DOUBLE_DOT ID LEFT_PAR elist RIGHT_PAR       	{printf("methodcall <- ..ID ( elist )\n");}
				;

elist			:	expr														{printf("elist <- expr\n");}
				|	expr COMMA elists														{printf("elist <- ,expr\n");}
				|
				;

elists			:	expr
				|	expr COMMA elists
				|
				;


objectdef		: 	LEFT_SQ_BR elist RIGHT_SQ_BR			{printf("objectdef <- [ elist ]\n");}
				| 	LEFT_SQ_BR indexed RIGHT_SQ_BR			{printf("objectdef <- [ indexed ]\n");}
				;

indexed			:	indexedelem							{printf("indexed <- indexedelem\n");}
				|	indexedelem COMMA indexed 					{printf("indexed <- ,indexedelem \n");}	
				;


indexedelem 	:	LEFT_BR expr COLON expr RIGHT_BR 	{printf("indexedelem <- {expr : expr}\n");}
				;

block			:	LEFT_BR RIGHT_BR
				|	LEFT_BR{++scope;} stmt stmts RIGHT_BR{;hide(scope--);} 				{printf("block <- { stmt }\n");}	
				;

funcdef			:	FUNCTION ID 			{           
                                                        ++check_if_open_func;
                                                        ++block_func_signal;
                                                        if(look_up_inscope($2,scope)==NULL){
															if(check_if_lib($2,yylineno)==0){
																insert_function(Symtbl,$2,scope,yylineno,USERFUNC);
																printf("%s function scope %d\n",$2, scope);
															}
											}else{
											    if(check_if_lib($2,yylineno)==1){
												    printf("Collision with library function %s\n",$2);
											    }else{
												    printf("\033[1;31m");
												    printf("Error in  line %d - This var is already defined before\n",yylineno);	
												    printf("\033[0m");
											    }
											} //printSymtable();
											}
					LEFT_PAR 
					{++scope;} idlist {--scope;}RIGHT_PAR		
					block {--check_if_open_func;--block_func_signal;}													{printf("funcdef <- function ID ( idlist ) block \n");}
				|	FUNCTION {++check_if_open_func;++block_func_signal;insert_function(Symtbl,randomfunc(),scope,yylineno,USERFUNC); //printSymtable();
				}
						LEFT_PAR {++scope;} idlist {--scope;}RIGHT_PAR block	{--check_if_open_func;--block_func_signal;}						{printf("funcdef <- function ( idlist ) block \n");}
				;


const			:	CONST_INT			{printf("const <- CONST_INT \n");}
				|	CONST_REAL 			{printf("const <- CONST_REAL \n");}
				|	STRING 				{printf("const <- STRING \n");}
				|	NIL  				{printf("const <- NIL \n");}
				|	TRUE 				{printf("const <- TRUE \n");}
				|	FALSE 				{printf("const <- FALSE \n");}
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
																		printf("Error in line %d - Formal argument already declared in this scope\n",yylineno);
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
																		printf("Error in line %d - Formal argument already declared in this scope\n",yylineno);
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
																		printf("Error in line %d - Formal argument already declared in this scope\n",yylineno);
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
																		printf("Error in line %d - Formal argument already declared in this scope\n",yylineno);
																		printf("\033[0m");
																	}
															}
															}	
															{printf("idlist <- ,ID \n");}
				;

ifstmt			: 	IF LEFT_PAR expr RIGHT_PAR stmt  {printf("ifstmt <- if ( expr ) stmt \n");}
				|   IF LEFT_PAR expr RIGHT_PAR stmt ELSE stmt {printf("ifstmt <- if ( expr ) stmt \n");}
				;

whilestmt		:	WHILE LEFT_PAR expr RIGHT_PAR {loop_signal++;} stmt {loop_signal--;} 		{printf("whilestmt <- while ( expr ) stmt \n");}
				;


forstmt			:	FOR LEFT_PAR elist SEMICOLON expr SEMICOLON elist RIGHT_PAR {loop_signal++;} stmt {loop_signal--;} {printf("forstmt <- for ( elist; expr; elist ) stmt \n");}
				;

returnstmt		:	RETURN SEMICOLON 			{printf("returnstmt <- return; \n");}
				| 	RETURN {ret=1;}expr SEMICOLON{ret=0;}		{printf("returnstmt <- return expr; \n");}
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
			//printSymtable_byscope();
		
		return 0;
}
