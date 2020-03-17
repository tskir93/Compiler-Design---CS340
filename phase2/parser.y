%{
#include "functions.h"

/*declarations*/
/*Names representing tokens must be declared; this is most simply done by writing

        %token   name1  name2 . . .

in the declarations section. (See Sections 3 , 5, and 6 for much more discussion). Every name not defined in the declarations section is assumed to represent a nonterminal symbol. Every nonterminal symbol must appear on the left side of at least one rule. */

int yylex(void);
int yyerror (char* yaccProvidedMessage);

int scope = 0;

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

stmt			:	expr SEMICOLON			{printf("stmt -> expr;\n");}
				|	ifstmt					{printf("stmt -> ifstmt\n");}
				|	whilestmt				{printf("stmt -> whilestmt\n");}
				|	forstmt					{printf("stmt -> forstmt\n");}
				|	returnstmt				{printf("stmt -> returnstmt\n");}
				|	BREAK SEMICOLON				{printf("stmt -> break;\n");}
				|	CONTINUE SEMICOLON			{printf("stmt -> continue;\n");}
				|	block					{printf("stmt -> block\n");}
				|	funcdef					{printf("stmt -> funcdef\n");}
				| 	SEMICOLON				{printf("stmt -> ;\n");}
				;

expr			:	assignexpr						{printf("expr -> assignexpr\n");}
				|	expr PLUS expr				{printf("expr -> expr op expr\n");}
				|	expr MINUS expr				{printf("expr -> expr op expr\n");}
				|	expr MULTIPLY expr				{printf("expr -> expr op expr\n");}
				|	expr DEVIDE	expr				{printf("expr -> expr op expr\n");}
				|	expr PERCENTAGE expr				{printf("expr -> expr op expr\n");}
				|	expr GREATER_THAN expr				{printf("expr -> expr op expr\n");}
				|	expr GR_EQ expr				{printf("expr -> expr op expr\n");}
				|	expr LESS_THAN expr				{printf("expr -> expr op expr\n");}
				|	expr LE_EQ expr				{printf("expr -> expr op expr\n");}
				|	expr EQUAL expr				{printf("expr -> expr op expr\n");}
				|	expr NOTEQUAL expr				{printf("expr -> expr op expr\n");}
				|	expr AND expr				{printf("expr -> expr op expr\n");}
				|	expr OR expr				{printf("expr -> expr op expr\n");}
				|	term 							{printf("expr -> term\n");}
				;



term			: 	LEFT_PAR expr RIGHT_PAR			{printf("term -> ( expr )\n");}
				|	MINUS expr %prec UMINUS			{printf("term -> -expr \n");}
				|	NOT expr						{printf("term -> not expr \n");}
				|	DOUBLE_PLUS lvalue				{printf("term -> ++lvalue \n");}
				|	lvalue DOUBLE_PLUS				{printf("term -> lvalue++ \n");}
				|	DOUBLE_MINUS lvalue				{printf("term -> --lvalue \n");}
				|	lvalue DOUBLE_MINUS				{printf("term -> lvalue-- \n");}
				|	primary							{printf("term -> primary \n");}
				;

assignexpr		:	lvalue ASSIGN expr				 {printf("assignexpr -> lvalue = expr \n");}
				;

primary			:	lvalue						{printf("primary -> lvalue \n");}
				|	call 						{printf("primary -> -call \n");}
				|	objectdef 					{printf("primary -> objectdef \n");}
				|	LEFT_PAR funcdef RIGHT_PAR 			{printf("primary -> ( funcdef ) \n");}
				|	const 						{printf("primary -> const \n");}
				;


lvalue			:	ID 							{printf("lvalue -> ID \n");}
				|	LOCAL ID 					{printf("lvalue ->  LOCAL ID\n");}
				|	DOUBLE_COL ID 				{printf("lvalue ->  ::ID\n");}
				|	member 						{printf("lvalue ->  member\n");}
				;


member			:	lvalue DOT ID 								{printf("member -> lvalue.ID \n");}
				|	lvalue LEFT_SQ_BR expr RIGHT_SQ_BR 			{printf("member -> lvalue { expr } \n");}
				|	call DOT ID 								{printf("member -> call.ID \n");}
				|	call LEFT_SQ_BR expr RIGHT_SQ_BR 			{printf("member -> call { expr } \n");}
				;

call			:	call LEFT_PAR elist RIGHT_PAR 				{printf("call -> call ( elist ) \n");}
				|	lvalue callsuffix							{printf("call -> lvalue callsuffix \n");}
				|	LEFT_PAR funcdef RIGHT_PAR LEFT_PAR elist RIGHT_PAR {printf("call -> ( funcdef )( elist )\n");}
				;

callsuffix		:	normcall								{printf("callsuffix -> normcall\n");}
				|	methodcall								{printf("callsuffix -> methodcall\n");}
				;	

normcall		:	LEFT_PAR elist RIGHT_PAR				{printf("normcall -> ( elist )\n");}
				;


methodcall		:	DOUBLE_DOT ID LEFT_PAR elist RIGHT_PAR       	{printf("methodcall -> ..ID ( elist )\n");}
				;

elist			:	expr									{printf("elist -> expr\n");}
				|	expr COMMA elists								{printf("elist -> ,expr\n");}
				;

elists			:	expr
				|	expr COMMA elists
				|
				;


objectdef		: 	LEFT_SQ_BR elist RIGHT_SQ_BR			{printf("objectdef -> [ elist ]\n");}
				| 	LEFT_SQ_BR indexed RIGHT_SQ_BR			{printf("objectdef -> [ indexed ]\n");}
				;

indexed			:	indexedelem							{printf("indexed -> indexedelem\n");}
				|	indexedelem COMMA indexed 					{printf("indexed -> ,indexedelem \n");}	
				;


indexedelem 	:	LEFT_BR expr COLON expr RIGHT_BR 	{printf("indexedelem -> {expr : expr}\n");}
				;

block			:	LEFT_BR stmt RIGHT_BR 				{printf("block -> { stmt }\n");}	
				;

funcdef			:	FUNCTION ID LEFT_PAR idlist RIGHT_PAR block  			{printf("funcdef -> function ID ( idlist ) block \n");}
				|	FUNCTION LEFT_PAR idlist RIGHT_PAR block				{printf("funcdef -> function ( idlist ) block \n");}
				;


const			:	CONST_INT			{printf("const -> CONST_INT \n");}
				|	CONST_REAL 			{printf("const -> CONST_REAL \n");}
				|	STRING 				{printf("const -> STRING \n");}
				|	NIL  				{printf("const -> NIL \n");}
				|	TRUE 				{printf("const -> TRUE \n");}
				|	FALSE 				{printf("const -> FALSE \n");}
				;



idlist			:	ID 								{printf("idlist -> ID \n");}
				|	ID COMMA idlists 				{printf("idlist -> ,ID \n");}
				|
				;

idlists			:	ID
				| 	ID COMMA idlists
				;

ifstmt			: 	IF LEFT_PAR expr RIGHT_PAR stmt else  	{printf("ifstmt -> if ( expr ) stmt \n");}
				;

else 			: 	ELSE stmt
				|
				;

whilestmt		:	WHILE LEFT_PAR expr RIGHT_PAR stmt 		{printf("whilestmt -> while ( expr ) stmt \n");}
				;


forstmt			:	FOR LEFT_PAR elist SEMICOLON expr SEMICOLON elist SEMICOLON RIGHT_PAR stmt 	{printf("forstmt -> for ( elist; expr; elist; ) stmt \n");}
				;

returnstmt		:	RETURN SEMICOLON 			{printf("returnstmt -> return; \n");}
				| 	RETURN expr SEMICOLON		{printf("returnstmt -> return expr; \n");}
				;



%%
/*programs   -   epilogos   */

int yyerror(char* yaccProvidedMessage){
	fprintf(stderr, "%s: at line %, before token: %s\n",yaccProvidedMessage,yylineno,yytext);
	printf("INPUT NOT VALID\n");
}





int main(int argc, char **argv) {
		yyin = stdin;

		
		Symtbl = new_Symtable();

		printSymtable();
		yyparse();

		
		return 0;
}
