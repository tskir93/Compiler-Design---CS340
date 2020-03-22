%{
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"				/* <---- will be generated from parser.y*/
/* #define YY_DECL int alpha_yylex(void* yylval)*/

struct alpha_token_t {
  	unsigned int     numline;
  	unsigned int     numToken;
  	char          *content;
  	char          *type;
  	struct alpha_token_t *next_token;
};

struct alpha_token_t *head_token = NULL;
struct alpha_token_t *tail_token = NULL;
struct alpha_token_t *display_token = NULL;

int counter;
int comstart = 0;
int nested = 0;
int multi_comm_error = 0;
char *mystring;


int IncreaseCounter(){
	counter++;
	return counter;
}

%}

/* The purpose of the union is to allow storing different kind of objects into nodes emitted by flex 

To explain better you can have for example:

%union
{
    int intVal;
    float floatVal;
    char *stringVal;
}
in .y if you want to provide basic support for CONST_INT, CONST_REAL and string types.
Kathe fora poy anagnwrizoyme ena sumvolo ston lex/flex prin epistrepsoyme ton kwdiko toy, apothikeuoume
sto union kai tin timi toy (an exei)
*/

%option noyywrap
%option yylineno

IF	        "if"
ELSE	    "else"
WHILE	    "while"
FOR		    "for"
FUNCTION	"function"
RETURN		"return"
BREAK		"break"
CONTINUE	"continue"
AND			"and"
NOT 		"not"
OR			"or"
LOCAL		"local"
TRUE		"true"
FALSE		"false"
NIL			"nil"
ASSIGN		"="
PLUS		"+"
MINUS		"-"
MULTIPLY	"*"
DEVIDE		"/"
PERCENTAGE	"%"
EQUAL 		"=="
NOTEQUAL	"!="
DOUBLE_PLUS	"++"
DOUBLE_MINUS	"--"
GREATER_THAN	">"
LESS_THAN		"<"
GR_EQ			">="
LE_EQ			"<="

TAB			"\t"
NEW_LINE	"\n"
DELIM		({TAB}|{NEW_LINE}|{WHITESPACE})*
LETTER		[A-Za-z]
DIGIT		[0-9]
UNDERSCORE	"_"
WHITESPACE  " "
NUMBER		{DIGIT}+
CONST_INT	{DIGIT}({DIGIT})*
CONST_REAL	{CONST_INT}"."({CONST_INT})

ID			{LETTER}({LETTER}|{DIGIT}|{UNDERSCORE})*
LEFT_BR		"{"
RIGHT_BR	"}"
LEFT_SQ_BR	"["
RIGHT_SQ_BR	"]"
LEFT_PAR	"("
RIGHT_PAR	")"
SEMICOLON	";"
COMMA		","
COLON		":"
DOUBLE_COL	"::"
DOT			"."
DOUBLE_DOT	".."

COMMENT		"//".*
MULT_COM    "/*"
MULT_COM_END "*/"
STRING_      \"

%x MULT_COM
%x STRING_

%%

{TAB}         {}

{IF}		    {
               		return IF;
                }
{ELSE}		    {
                	return ELSE;
                }
{WHILE}		    {
                	return WHILE;
                }
{FOR}		    {
                	return FOR;
                }
{FUNCTION}	    {
					return FUNCTION;
                }
{RETURN}	    {
					return RETURN;
                }
{BREAK}		    {
                    return BREAK;
                }
{CONTINUE}	    {
                	return CONTINUE;
                }
{AND}		    {
					return AND;
                }
{NOT} 		    {
					return NOT;
                }
{OR}			{
					return OR;
                }
{LOCAL}		    {
					return LOCAL;
                }
{TRUE}		    {
					return TRUE;
                }
{FALSE}		    {
					return FALSE;
                }
{NIL}			{
					return NIL;
                }
{ASSIGN}		{
                    return ASSIGN;
                }
{PLUS}		    {
					return PLUS;
                }
{MINUS}		    {
					return MINUS;
                }
{MULTIPLY}	    {
					return MULTIPLY;
                }
{DEVIDE}		{
                    return DEVIDE;
                }
{PERCENTAGE}	{
					return PERCENTAGE;
                }
{EQUAL} 		{
					return EQUAL;
                }
{NOTEQUAL}	    {
					return NOTEQUAL;
                }
{DOUBLE_PLUS}	{
					return DOUBLE_PLUS;
                }
{DOUBLE_MINUS}	{
					return DOUBLE_MINUS;
                }
{GREATER_THAN}	{
					return GREATER_THAN;
                }
{LESS_THAN}	    {
					return LESS_THAN;
                }
{GR_EQ}		    {
					return GR_EQ;
                }
{LE_EQ}		    {
					return LE_EQ;
                }

	
{CONST_INT}		{
                    yylval.intVal = atoi(yytext);
 					return CONST_INT;
                }
{CONST_REAL}	{
                    yylval.floatVal = atof(yytext);
 					return CONST_REAL;
                }
{LEFT_BR}		{
                    return LEFT_BR;
                }
{RIGHT_BR}	    {
                    return RIGHT_BR;
                }
{LEFT_SQ_BR}	{
                    return LEFT_SQ_BR;
                }
{RIGHT_SQ_BR}	{
                    return RIGHT_SQ_BR;
                }
{LEFT_PAR}	    {
                    return LEFT_PAR;
                }
{RIGHT_PAR}	    {                 
                    return RIGHT_PAR;
                }
{SEMICOLON}	    {
                    return SEMICOLON;
                }
{COMMA}		    {
                    return COMMA;
                }
{COLON}		    {             
                    return COLON;
                }
{DOUBLE_COL}	{
                	return DOUBLE_COL;
                }
{DOT}			{    
                    return DOT;
                }
{DOUBLE_DOT}	{   
                 	return DOUBLE_DOT;
                }
{ID}			{
                    yylval.stringVal = strdup(yytext);
 					return ID;
                }

{COMMENT}		{}


{WHITESPACE}    {}

{NEW_LINE}		{
					yylineno;
				}


{MULT_COM}		{   
                    comstart=yylineno;
                    multi_comm_error = 1;
                    BEGIN(MULT_COM);                   
                } 

<MULT_COM>{NEW_LINE}    {
                            yylineno;
                        }
<MULT_COM>"/*"			{
                            nested++;
                            char str1[100];
                            sprintf(str1,"%d", yylineno);/*an einai mono se mia grammi tote tipwse ton arithmo tis grammis*/	
							printf("NESTED_COMMENT\n");	
						}
<MULT_COM>"*/"          {
                            if (nested!=0){
                                nested--;
                                break;
                            }
						    char str[100];
							sprintf(str,"%d - %d", comstart,yylineno);
							if(comstart == yylineno){
							    sprintf(str,"%d", comstart);
							}/*an einai mono se mia grammi tote tipwse ton arithmo tis grammis*/	
							printf("MULTI_LINE_COMMENT\n");
							multi_comm_error = 0;
							BEGIN(INITIAL);
						}
<MULT_COM>.				{
	                        
	                    }/*otidipote allo kai na vrei den kanei tipota aplos to agnoei*/


{STRING_}			    {
                            int count=0;
		                    int line=0;
		                    int i=0;
		                    char in;
		                    mystring=(char *)malloc(yyleng *sizeof(char));
		                    while((in = input()) != EOF){
			                    if(in=='\\'){
				                    in=input();

				                    switch(in){
					                    case 'n':
					                        mystring=(char*)realloc(mystring, strlen(mystring) +1);

				 		                    if(mystring == NULL){
            				                    perror("insufficient memory!");
           		 			                    break;
        					                }
					                        mystring[i]='\n';
					                        i++;
					                        break;

					                    case 't':
					                        mystring=(char*)realloc(mystring,  strlen(mystring) +1);
				 		                    
				 		                    if(mystring == NULL){
            				                    perror("insufficient memory!");
           		 			                    break;
        			                        }
					                        mystring[i]='\t';
					                        i++;
					                        break;

					                    case '\\':
					                        mystring=(char*)realloc(mystring, strlen(mystring) +1);
				 		                    if(mystring == NULL){
            				                    perror("insufficient memory!");
           		 			                    break;
        					                }
					                        mystring[i]='\\';
					                        i++;
					                        break;

					                    default:
					                        mystring=(char*)realloc(mystring, strlen(mystring) +2);
				 		                    if(mystring == NULL){
            				                    perror("insufficient memory!");
           		 			                    break;
        					                }
					                        mystring[i]='\\';
					                        i++;
					                        mystring[i]=in;
					                        i++;	
				                    }
			                    }else if(in==STRING_){
				                    count++;
				                    line=yylineno;
				                    mystring[i]='\0';
				                    break;
			                    }else{
				                    mystring=(char*)realloc(mystring, strlen(mystring) +1);
				 		            if(mystring == NULL){
            				            perror("insufficient memory!");
           		 			            break;
        					        }
					                mystring[i]=in;
					                i++;
			                    }
		                    }
		                    if(count % 2==0){
			                    printf("The string has not closed correctly!\n");
			                    printf("Error in line %d",line);
		                    }else{
			                    yylval.stringVal = strdup(mystring);
			                    return STRING;
		                    }
		                    return 1;
	                    }


.		                {
                            printf("Undifined input %s in line %d\n",yytext,yylineno);
                        }


%%
