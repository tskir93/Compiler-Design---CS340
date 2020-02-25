%{
#include <stdlib.h>
#include <stdio.h>
#define YY_DECL int alpha_yylex(void* yylval)

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
void CreateToken(unsigned int numline,unsigned int numToken,char *content,char *type){
	struct alpha_token_t *new_token=(struct alpha_token_t *)malloc(sizeof(struct alpha_token_t));
	new_token->numline=numline;
    new_token->numToken=numToken;
	new_token->content=strdup(content);
	new_token->type=strdup(type);
	new_token->next_token=NULL;
	
	if(head_token == NULL){
		head_token = new_token;
		tail_token = head_token;
		return;
	}else{
		tail_token -> next_token = new_token;
		tail_token = new_token;
		return;
	}
}

int IncreaseCounter(){
	counter++;
	return counter;
}

void PrintTokens(){
 	display_token = head_token;
 	printf("Line No \t | \t numOfToken \t | \t Content \t | \t Type\n");
	while(display_token!=NULL){
		
		printf("%d \t\t\t #%d \t\t\t %s \t\t\t %s\n",display_token->numline,display_token->numToken,display_token->content,display_token->type);      
		display_token=display_token->next_token;
	}
	if(display_token==NULL){
		return;
	}
}

%}

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
DELIM		({TAB}|{NEW_LINE})*
LETTER		[A-Za-z]
DIGIT		[0-9]
UNDERSCORE	"_"
WHITESPACE  [\r\n \t\n]
NUMBER		{DIGIT}+
CONST_INT	{DIGIT}({DIGIT})*
CONST_REAL	{CONST_INT}"."({CONST_INT})

ID			{LETTER}({LETTER}|{DIGIT}|{UNDERSCORE})*
SENTENCE    {LETTER}({LETTER}|{DIGIT}|{UNDERSCORE}|{WHITESPACE}|{DELIM})*
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
STRING      \"
%x MULT_COM

%x STRING

%%

{IF}		    {
                    CreateToken(yylineno,IncreaseCounter(),"if","KEYWORD");
                    return 1;
                }
{ELSE}		    {
                    CreateToken(yylineno,IncreaseCounter(),"else","KEYWORD");
                    return 1;
                }
{WHILE}		    {
                    CreateToken(yylineno,IncreaseCounter(),"while","KEYWORD");
                    return 1;
                }
{FOR}		    {
                    CreateToken(yylineno,IncreaseCounter(),"for","KEYWORD");
                    return 1;
                }
{FUNCTION}	    {
                    CreateToken(yylineno,IncreaseCounter(),"function","KEYWORD");
                    return 1;
                }
{RETURN}	    {
                    CreateToken(yylineno,IncreaseCounter(),"return","KEYWORD");
                    return 1;
                }
{BREAK}		    {
                    CreateToken(yylineno,IncreaseCounter(),"break","KEYWORD");
                    return 1;
                }
{CONTINUE}	    {
                    CreateToken(yylineno,IncreaseCounter(),"continue","KEYWORD");
                    return 1;
                }
{AND}		    {
                    CreateToken(yylineno,IncreaseCounter(),"and","KEYWORD");
                    return 1;
                }
{NOT} 		    {
                    CreateToken(yylineno,IncreaseCounter(),"not","KEYWORD");
                    return 1;
                }
{OR}			{
                    CreateToken(yylineno,IncreaseCounter(),"or","KEYWORD");
                    return 1;
                }
{LOCAL}		    {
                    CreateToken(yylineno,IncreaseCounter(),"local","KEYWORD");
                    return 1;
                }
{TRUE}		    {
                    CreateToken(yylineno,IncreaseCounter(),"true","KEYWORD");
                    return 1;
                }
{FALSE}		    {
                    CreateToken(yylineno,IncreaseCounter(),"false","KEYWORD");
                    return 1;
                }
{NIL}			{
                    CreateToken(yylineno,IncreaseCounter(),"nil","KEYWORD");
                    return 1;
                }
{ASSIGN}		{
                    CreateToken(yylineno,IncreaseCounter(),"=","OPERATOR");
                    return 1;
                }
{PLUS}		    {
                    CreateToken(yylineno,IncreaseCounter(),"+","OPERATOR");
                    return 1;
                }
{MINUS}		    {
                    CreateToken(yylineno,IncreaseCounter(),"-","OPERATOR");
                    return 1;
                }
{MULTIPLY}	    {
                    CreateToken(yylineno,IncreaseCounter(),"*","OPERATOR");
                    return 1;
                }
{DEVIDE}		{
                    CreateToken(yylineno,IncreaseCounter(),"/","OPERATOR");
                    return 1;
                }
{PERCENTAGE}	{
                    CreateToken(yylineno,IncreaseCounter(),"%","OPERATOR");
                    return 1;
                }
{EQUAL} 		{
                    CreateToken(yylineno,IncreaseCounter(),"==","OPERATOR");
                    return 1;
                }
{NOTEQUAL}	    {
                    CreateToken(yylineno,IncreaseCounter(),"!=","OPERATOR");
                    return 1;
                }
{DOUBLE_PLUS}	{
                    CreateToken(yylineno,IncreaseCounter(),"++","OPERATOR");
                    return 1;
                }
{DOUBLE_MINUS}	{
                    CreateToken(yylineno,IncreaseCounter(),"--","OPERATOR");
                    return 1;
                }
{GREATER_THAN}	{
                    CreateToken(yylineno,IncreaseCounter(),">","OPERATOR");
                    return 1;
                }
{LESS_THAN}	    {
                    CreateToken(yylineno,IncreaseCounter(),"<","OPERATOR");
                    return 1;
                }
{GR_EQ}		    {
                    CreateToken(yylineno,IncreaseCounter(),">=","OPERATOR");
                    return 1;
                }
{LE_EQ}		    {
                    CreateToken(yylineno,IncreaseCounter(),"<=","OPERATOR");
                    return 1;
                }
	
{CONST_INT}		{
                    CreateToken(yylineno,IncreaseCounter(),yytext,"CONST_INT");
                    return 1;
                }
{CONST_REAL}	{
                    CreateToken(yylineno,IncreaseCounter(),yytext,"CONST_REAL");
                    return 1;
                }
{LEFT_BR}		{
                    CreateToken(yylineno,IncreaseCounter(),"{","PUNCTUATION_MARK");
                    return 1;
                }
{RIGHT_BR}	    {
                    CreateToken(yylineno,IncreaseCounter(),"}","PUNCTUATION_MARK");
                    return 1;
                }
{LEFT_SQ_BR}	{
                    CreateToken(yylineno,IncreaseCounter(),"[","PUNCTUATION_MARK");
                    return 1;
                }
{RIGHT_SQ_BR}	{
                    CreateToken(yylineno,IncreaseCounter(),"]","PUNCTUATION_MARK");
                    return 1;
                }
{LEFT_PAR}	    {
                    CreateToken(yylineno,IncreaseCounter(),"(","PUNCTUATION_MARK");
                    return 1;
                }
{RIGHT_PAR}	    {                 
                    CreateToken(yylineno,IncreaseCounter(),")","PUNCTUATION_MARK");
                    return 1;
                }
{SEMICOLON}	    {
                    CreateToken(yylineno,IncreaseCounter(),";","PUNCTUATION_MARK");
                    return 1;
                }
{COMMA}		    {
                    CreateToken(yylineno,IncreaseCounter(),",","PUNCTUATION_MARK");
                    return 1;
                }
{COLON}		    {             
                    CreateToken(yylineno,IncreaseCounter(),":","PUNCTUATION_MARK");
                    return 1;
                }
{DOUBLE_COL}	{
                    CreateToken(yylineno,IncreaseCounter(),"::","PUNCTUATION_MARK");
                    return 1;
                }
{DOT}			{    
                    CreateToken(yylineno,IncreaseCounter(),".","PUNCTUATION_MARK");
                    return 1;
                }
{DOUBLE_DOT}	{   
                    CreateToken(yylineno,IncreaseCounter(),"..","PUNCTUATION_MARK");
                    return 1;
                }
{ID}			{
                    CreateToken(yylineno,IncreaseCounter(),yytext,"ID");
                    return 1;
                }
{COMMENT}		{
                    CreateToken(yylineno,IncreaseCounter(),yytext,"COMMENT");
                    return 1;
                }

{WHITESPACE}    {
	                return 1;
	            }  

{MULT_COM}		{   
                    comstart=yylineno;
                    BEGIN(MULT_COM);
                } 
<MULT_COM>{NEW_LINE}    {
                            yylineno;
                        }
<MULT_COM>"/*"			{
                            nested++;
                            char str1[100];
                            sprintf(str1,"%d", yylineno);/*an einai mono se mia grammi tote tipwse ton arithmo tis grammis*/	
							CreateToken(yylineno,IncreaseCounter(),str1,"NESTED_COMMENT");	
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
							CreateToken(yylineno,IncreaseCounter(),str,"MULTI_LINE_COMMENT");
							BEGIN(INITIAL);
						}
<MULT_COM>.				{}/*otidipote allo kai na vrei den kanei tipota aplos to agnoei*/


{STRING}			    {
                            int count=0;
		                    int line=0;
		                    int i=0;
		                    int strsz=yyleng;
		                    char in;
		                    char *mystring=(char *)malloc(strsz*sizeof(char));

		                    while((in = input()) != EOF){
			                    if(in=='\\'){
				                    in=input();

				                    switch(in){
					                    case 'n':
					                        mystring=realloc(mystring, (strsz+1)*sizeof(char));

				 		                    if(mystring == NULL){
            				                    perror("insufficient memory!");
           		 			                    break;
        					                }
					                        mystring[i]='\n';
					                        i++;
					                        break;

					                    case 't':
					                        mystring=realloc(mystring, (strsz+1)*sizeof(char));
				 		                    
				 		                    if(mystring == NULL){
            				                    perror("insufficient memory!");
           		 			                    break;
        			                        }
					                        mystring[i]='\t';
					                        i++;
					                        break;

					                    case '\\':
					                        mystring=realloc(mystring, (strsz+1)*sizeof(char));
				 		                    if(mystring == NULL){
            				                    perror("insufficient memory!");
           		 			                    break;
        					                }
					                        mystring[i]='\\';
					                        i++;
					                        break;

					                    default:
					                        mystring=realloc(mystring,(strsz+2)*sizeof(char));
				 		                    if(mystring == NULL){
            				                    perror("insufficient memory!");
           		 			                    break;
        					                }
					                        mystring[i]='\\';
					                        i++;
					                        mystring[i]=in;
					                        i++;	
				                    }
			                    }else if(in=='\"'){
				                    count++;
				                    line=yylineno;
				                    mystring[i]='\0';
				                    break;
			                    }else{
				                    mystring=realloc(mystring, (strsz+1)*sizeof(char));
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
			                    CreateToken(yylineno,IncreaseCounter(),mystring,"STRING");
		                    }
		                    return 1;
	                    }
.		                {
                            printf("Undifined input %s in line %d\n",yytext,yylineno);
                        }


%%

int main(int argc, char** argv)
{
	if(argc>1){
        if(!(yyin=fopen(argv[1],"r"))){
            fprintf(stderr, "Cannot read file: %s\n",argv[1]);
            return 1;
        }
    }
    int i = 1; 
    do{
        i = alpha_yylex(head_token);
   
    }while(i==1);
    PrintTokens();
    return 0;
}
