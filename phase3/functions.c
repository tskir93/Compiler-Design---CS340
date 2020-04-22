#include "functions.h"

SymTable *head; 


int random_num = 0;
int i=0;
char name[] ="_f";

/*phase 3*/
quad * quads = (quad*) 0;
unsigned total = 0;
unsigned int currQuad = 0;
int tempcounter = 0;

unsigned programVarOffset = 0;
unsigned functionLocalOffset = 0;
unsigned formalArgOffset = 0;
unsigned scopeSpaceCounter = 1;



//diaf 10 sel 10
unsigned nextquad(void){
	return currQuad;
}

void insert_variable(SymTable *sym,const char *name,unsigned int scope, unsigned int line, enum SymbolType type){
	int temp_scope;
	/*desmevoyme xwro gia ena kainourgio node sto symtable*/
	SymbolTableEntry *new = (SymbolTableEntry *)malloc(sizeof(SymbolTableEntry));
	Variable *new_var = (Variable *)malloc(sizeof(Variable));
	new->value.varVal = (Variable *)malloc(sizeof(Variable));
	
	SymbolTableEntry *temp = sym->entry;

	new_var -> name = strdup(name);
	new_var -> scope = scope;
	new_var -> line = line;

	new->isActive = 1;
	new->value.varVal = (Variable *) new_var;
	new->type = type;
	new->next = NULL;
	
	if(temp == NULL){
		head->entry = new;
		//temp = new;

	}else{
		
			temp_scope=new_var->scope;
			temp = sym->entry;

			while(temp->next!=NULL && temp->next->value.funcVal->scope<temp_scope){
				temp = temp->next;
			}
			new->next=temp->next;
			temp->next=new;
		
	}

}

/*sunartisi gia eisagwgi enos function sto symtable*/
void insert_function(SymTable *sym,const char *name,unsigned int scope, unsigned int line, enum SymbolType type){
	int temp_scope;
	/*desmevoyme xwro gia ena kainourgio node sto symtable*/
	SymbolTableEntry *new = (SymbolTableEntry *)malloc(sizeof(SymbolTableEntry));
	Function *new_func = (Function *)malloc(sizeof(Function));
	new->value.funcVal = (Function *)malloc(sizeof(Function));
	
	SymbolTableEntry *temp = sym->entry;

	new_func -> name = name;
	new_func -> scope = scope;
	new_func -> line = line;

	new->isActive = 1;
	new->value.funcVal = (Function *) new_func;
	new->type = type;
	new->next = NULL;

	
	if(temp == NULL){
		head->entry = new;
		//temp = new;

	}else{
		
			temp_scope=new_func->scope;
			temp = sym->entry;

			while(temp->next!=NULL && temp->next->value.funcVal->scope<temp_scope){
				temp = temp->next;
			}
			new->next=temp->next;
			temp->next=new;
		
	}
}

/*synartisi poy elegxei an auto poy diavase einai variable i function*/
void check_Var_or_Func(SymTable *sym,const char *name,unsigned int scope, unsigned int line, enum SymbolType type){
	if (type == GLOBAL || type == LOCALE || type == FORMAL){
		insert_variable(sym,name,scope,line,type);
		
	}else if( type == USERFUNC || type == LIBFUNC){
		insert_function(sym,name,scope,line, type);
		
	}
}

/*synartisi poy elegxei an auto poy diavase einai variable i function*/
int check_type_for_print (enum SymbolType type){
	if (type == GLOBAL || type == LOCALE || type == FORMAL){
		return 0;
	}else if( type == USERFUNC || type == LIBFUNC){
		return 1;
	}
}

int check_type(SymbolTableEntry *ent){
	if(ent!=NULL){
		if (ent->type == GLOBAL || ent->type == LOCALE || ent->type == FORMAL){
			return 0;
		}else if( ent->type == USERFUNC || ent->type == LIBFUNC){
			return 1;
		}
	}
}



/*ftiaxnei enan kainourgio keno symtable kai kanei return ton deikti stin arxi toy symtable*/
SymTable *new_Symtable(){

	SymTable *new = (SymTable *)malloc(sizeof(SymTable));
	head = new;
	
	//printf("ftiaxnei ton sumboltable\n");

	insert_function(new,"print",0,0,LIBFUNC);
	insert_function(new,"input",0,0,LIBFUNC);
	insert_function(new,"objectmemberkeys",0,0,LIBFUNC);
	insert_function(new,"objecttotalmembers",0,0,LIBFUNC);
	insert_function(new,"objectcopy",0,0,LIBFUNC);
	insert_function(new,"totalarguments",0,0,LIBFUNC);
	insert_function(new,"argument",0,0,LIBFUNC);
	insert_function(new,"typeof",0,0,LIBFUNC);
	insert_function(new,"strtonum",0,0,LIBFUNC);
	insert_function(new,"sqrt",0,0,LIBFUNC);
	insert_function(new,"cos",0,0,LIBFUNC);
	insert_function(new,"sin",0,0,LIBFUNC);

	return head;
}

/*thelei emploutismo gia na kanei swsto print*/
void printSymtable(){
	SymbolTableEntry *ent = head->entry;
	int flag = 0;
	printf("-----------------------------------------*****************Symtable output*****************-----------------------------------------\n\n\n");
	
	while (ent!=NULL && flag==0){
		if(check_type_for_print(ent->type)==0){
			
			printf("\"%s\"",ent->value.varVal->name);
			if(strlen(ent->value.varVal->name) <=2){
					printf("\t\t\t\t\t");
				}else if(strlen(ent->value.varVal->name) > 2 && strlen(ent->value.varVal->name)<6){
					printf("\t\t\t");
				}else if(strlen(ent->value.varVal->name)>=6 && strlen(ent->value.varVal->name)<15){
					printf("\t\t\t\t");	
				}else{
					printf("\t");
				}
			printf("[ %s ]\t",gettype_to_String(ent->type));

			printf("( line %d )\t\t",ent->value.varVal->line);
			printf("( scope %d )\n",ent->value.varVal->scope);

		}else if(check_type_for_print(ent->type)==1){
			
			printf("\"%s\"\t\t",ent->value.funcVal->name);
			if(strlen(ent->value.funcVal->name) <=2){
					printf("\t\t\t");
				}else if(strlen(ent->value.funcVal->name)<6){
					printf("\t\t\t");
				}else if(strlen(ent->value.funcVal->name)>=6 && strlen(ent->value.funcVal->name)<12){
					printf("\t\t");	
				}else{
					printf("\t");
				}


			printf("[ %s ]\t",gettype_to_String(ent->type));
			
			printf("( line %d )\t\t",ent->value.funcVal->line);
			printf("( scope %d )\n",ent->value.funcVal->scope);

		}
		if(ent->next!=NULL){
			ent = ent->next;
		}else{
			flag=1;
		}
	}
}

void hide(int scope){
	SymbolTableEntry *ent = head -> entry;
	
	while(ent!=NULL){
		if(check_type_for_print(ent->type)==0){
			if(ent->value.varVal->scope == scope){
				ent->isActive = 0;
			}
		}else if(check_type_for_print(ent->type)==1){
			if(ent->value.funcVal->scope == scope){
				ent->isActive = 0;
			}
		}
		if(ent->next!=NULL){
			ent = ent->next;
		}else{
			break;
		}
	}

}


void printSymtable_hide(){
	SymbolTableEntry *ent = head->entry;



	printf("-----------------------------------------*****************Symtable output*****************-----------------------------------------\n\n\n");
	
	while (ent!=NULL){
		if(check_type_for_print(ent->type)==0){
			if(ent->isActive == 1){
				printf("\"%s\"",ent->value.varVal->name);
				if(strlen(ent->value.varVal->name) <=2){
					printf("\t\t\t\t\t");
				}else if(strlen(ent->value.varVal->name) > 3 && strlen(ent->value.varVal->name)<6){
					printf("\t\t\t");
				}else if(strlen(ent->value.varVal->name)>=6 && strlen(ent->value.varVal->name)<15){
					printf("\t\t");	
				}else{
					printf("\t");
				}
				printf("[ %s ]\t",gettype_to_String(ent->type));
				printf("( line %d )\t",ent->value.varVal->line);
				printf("( scope %d )\n",ent->value.varVal->scope);
			}
		}else if(check_type_for_print(ent->type)==1){
			if(ent->isActive ==1){
				printf("\"%s\"\t\t",ent->value.funcVal->name);
				if(strlen(ent->value.funcVal->name) <=2){
					printf("\t\t\t\t\t");
				}else if(strlen(ent->value.funcVal->name)<6){
					printf("\t\t\t");
				}else if(strlen(ent->value.funcVal->name)>=6 && strlen(ent->value.funcVal->name)<12){
					printf("\t\t");	
				}else{
					printf("\t");
				}

				printf("[ %s ]\t\t",gettype_to_String(ent->type));
				printf("( line %d )\t\t",ent->value.funcVal->line);
				printf("( scope %d )\n",ent->value.funcVal->scope);
			}
		}
		if(ent->next!=NULL){
			ent = ent->next;
		}else{
			break;
		}
	}
}

/*standard sunartisi gia metatropi enum se string gia na to ektupwsoume*/
const char* gettype_to_String(enum SymbolType type) 
{
	switch (type) 
	{
		case GLOBAL: return "GLOBAL";
		case LOCALE: return "LOCAL";
		case FORMAL: return "FORMAL";
		case USERFUNC: return "USERFUNC";
		case LIBFUNC: return "LIBFUNC";
	}
}


int check_if_lib(const char *name,int line){
	if(strcmp("print",name)==0){
		printf("\033[1;31m");														
		printf("ERROR in line %d - Collision with %s, is a LIBFUNC\n",line,name);				
		printf("\033[0m");
		return 1;
	}
	else if(strcmp("input",name)==0){
		printf("\033[1;31m");														
		printf("ERROR in line %d - Collision with %s, is a LIBFUNC\n",line,name);				
		printf("\033[0m");
		return 1;
	}
	else if(strcmp("objectmemberkeys",name)==0){
		printf("\033[1;31m");														
		printf("ERROR in line %d - Collision with %s, is a LIBFUNC\n",line,name);				
		printf("\033[0m");
		return 1;
	}
	else if(strcmp("objecttotalmembers",name)==0){
		printf("\033[1;31m");														
		printf("ERROR in line %d - Collision with %s, is a LIBFUNC\n",line,name);				
		printf("\033[0m");
		return 1;
	}
	else if(strcmp("objectcopy",name)==0){
		printf("\033[1;31m");														
		printf("ERROR in line %d - Collision with %s, is a LIBFUNC\n",line,name);				
		printf("\033[0m");
		return 1;
	}
	else if(strcmp("totalarguments",name)==0){
		printf("\033[1;31m");														
		printf("ERROR in line %d - Collision with %s, is a LIBFUNC\n",line,name);				
		printf("\033[0m");
		return 1;
	}
	else if(strcmp("argument",name)==0){
		printf("\033[1;31m");														
		printf("ERROR in line %d - Collision with %s, is a LIBFUNC\n",line,name);				
		printf("\033[0m");
		return 1;
	}
	else if(strcmp("typeof",name)==0){
		printf("\033[1;31m");														
		printf("ERROR in line %d - Collision with %s, is a LIBFUNC\n",line,name);				
		printf("\033[0m");
		return 1;
	}
	else if(strcmp("strtonum",name)==0){
		printf("\033[1;31m");														
		printf("ERROR in line %d - Collision with %s, is a LIBFUNC\n",line,name);				
		printf("\033[0m");
		return 1;
	}
	else if(strcmp("sqrt",name)==0){
		printf("\033[1;31m");														
		printf("ERROR in line %d - Collision with %s, is a LIBFUNC\n",line,name);				
		printf("\033[0m");
		return 1;
	}
	else if(strcmp("cos",name)==0){
		printf("\033[1;31m");														
		printf("ERROR in line %d - Collision with %s, is a LIBFUNC\n",line,name);				
		printf("\033[0m");
		return 1;
	}
	else if(strcmp("sin",name)==0){
		printf("\033[1;31m");														
		printf("ERROR in line %d - Collision with %s, is a LIBFUNC\n",line,name);				
		printf("\033[0m");
		return 1;
	}
	
	//printf("%s is not a lib func\n",name);
	return 0;

}


char *randomfunc(){
	char *out = (char*)malloc(sizeof(char));
	sprintf(out, "%s%d", name, random_num) ;
	random_num++;
		//printf("name = %s\n",out);
	return (out);
}


enum SymbolType check_Var_type_for_function_arg(int scope){
	if (scope==0){ 
		return GLOBAL;
	}else{ 
		return FORMAL;
	}
	
}
/*tsekarei an to argument poy einai mesa stin sunartisi uparxei sto global scope i oxi*/
enum SymbolType check_Var_type_local(int scope){
	if (scope==0){ 
		return GLOBAL;
	}else{ 
		return LOCALE;
	}
	
}


SymbolTableEntry *look_up_inscope(const char *name,int scope)
{
	SymbolTableEntry *temp = head->entry;
	const char *temp_name = name;
	while(temp!=NULL){
		
		if(temp->type == FORMAL || temp->type == GLOBAL || temp->type == LOCALE ){
			if ((strcmp(temp->value.varVal->name,name)==0) && temp->value.varVal->scope==scope){
				//printf("Already the %s is in SymTable in this scope %d\n",temp->value.varVal->name,temp->value.varVal->scope);
				return temp;
			}

		}
		else if(temp->type == USERFUNC || temp->type == LIBFUNC){
			if ((strcmp(temp->value.funcVal->name,name)==0) && temp->value.funcVal->scope == scope) {
				//printf("Already the %s is in SymTable in this scope %d\n",temp->value.funcVal->name,temp->value.funcVal->scope);
				return temp;
			}

		}
		temp=temp->next;

	}
	//printf(" %s not found in scope  %d \n",name,scope);
	return NULL;
}

SymbolTableEntry *look_up(const char *name,int scope){
	//printf("6");
 	SymbolTableEntry *temp = head->entry;
	const char *temp_name = name;
	int temp_scope=scope;
	//printf("lala");
	while(temp_scope>0 || temp_scope==0){
		//printf("temp_scope einai %d ",temp_scope);
		
		while((temp->next!=NULL && temp->value.varVal->scope<temp_scope)  || (temp->next!=NULL && temp->value.funcVal->scope<temp_scope)){
			temp=temp->next;
		}//pigainoume sto scope pou exoume os input
		//printf("h metabliti1 einai %s sto scope %d",temp->value.varVal->name,temp->value.varVal->scope);
		//printf("eimai edo pou tha eprepe");
	//printf("exo typo %s kai  onoma %s ",gettype_to_String(temp->type),temp->value.varVal->name);
	//printf("\nscope pou eimai %d  kai temp_scope %d",temp->value.varVal->scope,temp_scope);
			if(temp->type == FORMAL || temp->type == GLOBAL || temp->type == LOCALE ){ //ean isxuei auto tote einai to proto stoixeio sto scope tou opote to brhkame
				if ((strcmp(temp->value.varVal->name,temp_name)==0) && temp->value.varVal->scope==temp_scope){
					//printf("\nexoume tin metabliti %s sto scope %d kai stin line %d\n",temp->value.varVal->name,temp->value.varVal->scope,temp->value.varVal->line);
					return temp;
				}

			}
			else if(temp->type == USERFUNC || temp->type == LIBFUNC){
				if ((strcmp(temp->value.funcVal->name,temp_name)==0) && temp->value.funcVal->scope == temp_scope) {
					//printf("\nexoume tin sinartisi %s sto scope %d kai stin line %d\n",temp->value.funcVal->name,temp->value.funcVal->scope,temp->value.funcVal->line);
					return temp;
				}

			}

//printf("autoi pou eimaste %s kai autoi pou psaxoume %s",temp->value.varVal->name,temp_name);		
			while((temp!=NULL && strcmp(temp->value.varVal->name,temp_name)!=0) || (temp!=NULL &&  strcmp(temp->value.funcVal->name,temp_name)!=0) ){
					temp=temp->next;
				//printf("mpika");
				}
//printf("h metabliti2 einai %s",temp->value.varVal->name);
				if(temp!=NULL){
					if(temp->type == FORMAL || temp->type == GLOBAL || temp->type == LOCALE ){
						if ((strcmp(temp->value.varVal->name,name)==0) && temp->value.varVal->scope==temp_scope){
							//printf("\nAlready in SymTable in the scope %d\n",temp->value.varVal->scope);
						return temp;
						}

					}
					else if(temp->type == USERFUNC || temp->type == LIBFUNC){
						if ((strcmp(temp->value.funcVal->name,name)==0) && temp->value.funcVal->scope ==temp_scope) {
							//printf("\nAlready in SymTable in the scope %d\n",temp->value.funcVal->scope);
							return temp;
						}

					}
				}
				
			
			temp=head->entry;
			temp_scope--;
		}
		//printf("the  %s is not found in scope %d or smaller\n",name,scope);
		return NULL;
	
}

int check_if_function_before(int scope){ /* we check if we have function in the previous scope */
	
	SymbolTableEntry *temp = head->entry;
	int temp_scope;
	temp_scope=scope-1;
	

	while((temp!=NULL && temp->value.funcVal->scope<temp_scope) || (temp!=NULL && temp->value.varVal->scope<temp_scope)){
	//printf("\ntemp scope einai %d kai to allo einai %d",temp_scope,temp->value.funcVal->scope); 
		temp=temp->next;
		//printf("\nh metabliti2 einai %s",temp->value.varVal->name);
	}
//printf("lala");

	while((temp->next!=NULL && temp->next->value.funcVal->scope<=temp_scope) || (temp->next!=NULL && temp->next->value.varVal->scope<=temp_scope)){ 
		if(check_type_for_print(temp->type)==1 && check_if_lib_noprint(temp->value.funcVal->name)==0) 
		break;
		temp=temp->next;
	}
	//printf("\nh metabliti3 einai %s",temp->value.varVal->name);
	if(check_type_for_print(temp->type)==1 && check_if_lib_noprint(temp->value.funcVal->name)==0){ 
		return 1;
	}
	return 0;

}

/*gia na xeiristw px tin print(x) den thelw na ektypwnei error apla na tsekarw an einai libfunc*/
int check_if_lib_noprint(const char *name){
	if(strcmp("print",name)==0){				return 1;
	}
	else if(strcmp("input",name)==0){		return 1;
	}
	else if(strcmp("objectmemberkeys",name)==0){				return 1;
	}
	else if(strcmp("objectotalmembers",name)==0){			return 1;
	}
	else if(strcmp("objectcopy",name)==0){			return 1;
	}
	else if(strcmp("totalarguments",name)==0){			return 1;
	}
	else if(strcmp("argument",name)==0){			return 1;
	}
	else if(strcmp("typeof",name)==0){				return 1;
	}
	else if(strcmp("strtonum",name)==0){				return 1;
	}
	else if(strcmp("sqrt",name)==0){				return 1;
	}
	else if(strcmp("cos",name)==0){				return 1;
	}
	else if(strcmp("sin",name)==0){				return 1;
	}
	
	return 0;

}

/*SymbolTableEntry *look_up_inscope_noprint(const char *name,int scope)
{
	SymbolTableEntry *temp = head->entry;
	const char *temp_name = name;
	while(temp!=NULL){
		
		if(temp->type == FORMAL || temp->type == GLOBAL || temp->type == LOCALE ){
			if ((strcmp(temp->value.varVal->name,name)==0) && temp->value.varVal->scope==scope){
				if(scope==0){
					
					return temp;
				}else{
					
					return temp;
				}	
			}

		}
		else if(temp->type == USERFUNC || temp->type == LIBFUNC){
			if ((strcmp(temp->value.funcVal->name,name)==0) && temp->value.funcVal->scope == scope){
				if(scope==0){
					
					return temp;
				}else{
						
					return temp;
				}
				
			}

		}
		temp=temp->next;

	}
	
	return NULL;
}*/

SymbolTableEntry *look_up_inscope_noprint(const char *name,int scope)
{
	SymbolTableEntry *temp = head->entry;
	const char *temp_name = name;
	while(temp!=NULL){
		
		if(temp->type == FORMAL || temp->type == GLOBAL || temp->type == LOCALE ){
			if ((strcmp(temp->value.varVal->name,name)==0) && temp->value.varVal->scope==scope){
				return temp;
			}

		}
		else if(temp->type == USERFUNC || temp->type == LIBFUNC){
			if ((strcmp(temp->value.funcVal->name,name)==0) && temp->value.funcVal->scope == scope) {
				return temp;
			}

		}
		temp=temp->next;

	}
	return NULL;
}



//phase3


//diaf 9 sel 38
void expand(void){
	assert (total == currQuad);
	quad* p = (quad*)malloc(NEW_SIZE);
	if(quads){
		memcpy(p, quads,CURR_SIZE);
		free(quads);
	}
	quads = p;
	total += EXPAND_SIZE;
}

//diaf 9 sel 38
void emit(
	iopcode		op,
	expr*		arg1,
	expr*		arg2,
	expr* 		result,
	unsigned	label,
	unsigned	line
	){

	if (currQuad == total)
		expand();

	quad* p = quads + currQuad++;
	p->op = op;
	p->arg1	= arg1;
	p->arg2	= arg2;
	p->result = result;
	p->label = label;
	p->line = line;
}

//diaf 9 sel 44
char *newtempname(){
	char *out = (char*)malloc(sizeof(char));
	sprintf(out, "%s%d", name, tempcounter) ;
	tempcounter++;
		//printf("name = %s\n",out);
	return (out);
}

//diaf 9 sel 44
void resettemp(){
	tempcounter = 0;
}

//diaf 9 sel 44-45
//den kserw ti tipo prepei na exei nomizw symboltable entry
SymbolTableEntry *newtemp(SymTable *Symtable,unsigned int scope, unsigned int line){
	char *name = newtempname();
	SymbolTableEntry *sym = look_up_inscope_noprint(name,scope);
	
	if (sym!=NULL){
		return sym; //epistrefoume tin idi diathesimi  metabliti
	}else{
        
		//char * new_name = newtempname();
        insert_variable(Symtable,name,scope,line,LOCALE);
        SymbolTableEntry *sym = look_up_inscope_noprint(name,scope);
        return sym;
	}
}

 scopespace_t currscopespace(void){
	if(scopeSpaceCounter == 1){
		return programvar;
	}else if(scopeSpaceCounter % 2 == 0){
		return formalarg;
	}else{
		return functionlocal;
	}
}

unsigned currscopeoffset(void){
	switch (currscopespace()){
		case programvar 	: 	return programVarOffset;
		case functionlocal 	:	return functionLocalOffset;
		case formalarg 		:	return formalArgOffset;
		default				: 	assert(0);
	}
}

void inccurrscopeoffset(void){
	switch(currscopespace()){
		case programvar 	: ++programVarOffset;break;
		case functionlocal 	: ++functionLocalOffset;break;
		case formalarg 		: ++formalArgOffset;break;
		default 			: assert(0);
	}
}

void enterscopespace(void){
	++scopeSpaceCounter;
}

void exitscopespace(void){
	assert(scopeSpaceCounter>1);
	--scopeSpaceCounter;
}

//diaf 10 sel 10
void resetformalargsoffset(void){
	formalArgOffset = 0;
}
//diaf 10 sel 10
void resetfunctionlocaloffset(void){
	functionLocalOffset = 0;
}

//diaf 10 sel 10
void restorecurrscopeoffset(unsigned n){
		switch (currscopespace()){
		case programvar 	: 	programVarOffset = n;break;
		case functionlocal 	:	functionLocalOffset = n;break;
		case formalarg 		:	formalArgOffset = n;break;
		default				: 	assert(0);
	}
}



void push(struct stack* s,unsigned offset){ 
	s->args[++s->top] = offset;
}

unsigned pop(struct stack* s)
{
	return s->args[s->top--];		
}

struct stack *newStack(){
	struct stack* s = (struct stack*)malloc(sizeof(struct stack));
	s->top = -1;
	s->args = (unsigned *)malloc(1024 * sizeof(unsigned));
	return s;
}

void makestack(){
	scopeoffsetStack = newStack();
	loopcounterstack = newStack();
}


//symplirwnoyme ena arxika undifined label me tin patchlabel
void patchlabel(unsigned quadNo,unsigned label){
	assert (quadNo < currQuad);
	quads[quadNo].label = label;
}

expr* lvalue_expr (SymbolTableEntry* sym){
	assert(sym);
	expr* e = (expr*)malloc (sizeof(expr));
	memset(e,0,sizeof(expr));
	e->next = (expr*)0;
	e->sym = sym;
	//printf("mpaieni s autin edw\n");
	switch (sym->type){
		case GLOBAL			:	e->type = var_e;break;
		case LOCALE			: 	e->type = var_e;break;
		case FORMAL			: 	e->type = var_e;break;
		case USERFUNC		: 	e->type = programfunc_e;break;
		case LIBFUNC		: 	e->type = libraryfunc_e;break;
		default				:	assert(0);
	}
	return e;
}


//diaf 10 sel 24
expr* newexpr (expr_t t){
	expr* e = (expr*)malloc(sizeof(expr));
	memset(e,0,sizeof(expr));
	e->type = t;
	return e;
}

//diaf 10 sel 24
expr* newexpr_conststring(char *s){
	expr* e = newexpr(conststring_e);
	e->val.strConst = strdup(s);
	return e;
}

//diaf10 sel 24
expr* emit_iftableitem(SymTable *Symtable,unsigned int scope,expr* e,unsigned line){
	if(e->type != tableitem_e){
		return e;
	}else{
		expr* result = newexpr(var_e);
		//printf("mpaineis edw kai ftiaxnei tin metavliti\n");
		result->sym = newtemp(Symtable,scope,line);
		emit(tablegetelem,e,e->index,result,0,line);
		return result;
	}
}

expr* member_item(SymTable *Symtable,unsigned int scope,expr* lvalue, char* name,unsigned line){
	lvalue = emit_iftableitem(Symtable,scope,lvalue,line);
	expr* tableitem = newexpr(tableitem_e);
	tableitem->sym = lvalue->sym;
	tableitem->index = newexpr_conststring(name);
	return tableitem;
}

//diaf10 sel 27
expr* make_call(SymTable *Symtable,unsigned int scope,expr *lvalue, expr* reversed_elist,unsigned line){
	expr* func = emit_iftableitem(Symtable,scope,lvalue,line);
	while(reversed_elist){
		emit(param,reversed_elist,NULL,NULL,0,line);
		reversed_elist = reversed_elist->next;
	}
	emit(Call,func,NULL,NULL,0,line);
	expr* result = newexpr(var_e);
	result->sym = newtemp(Symtable,scope,line);
	emit(getretval,NULL,NULL,result,0,line);
	return result;
}

expr* newexpr_constnum(double i){
	expr* e = newexpr(constnum_e);
	e->val.numConst = i;
	return e;
}

expr* newexpr_constbool(unsigned int b){
	expr* e = newexpr(constbool_e);
	e->val.boolConst = b; //tsekare to
	return e;
}



int check_arith(expr *e){
	if(	e->type == constbool_e 	||
		e->type == conststring_e||
		e->type == nil_e		||
		e->type == newtable_e 	||
		e->type == programfunc_e||
		e->type == libraryfunc_e||
		e->type == boolexpr_e	){
		printf("\033[1;31m");
		printf("Compile Error - Illegal expr used\n");
		printf("\033[0m");
		return 1;
	}else{
		return 0;
	}
	
}


int check_corr_type(expr *e){
	if(	e->type == programfunc_e||
		e->type == libraryfunc_e||
		e->type == boolexpr_e	||
		e->type == newtable_e 	||
		e->type == constbool_e 	||
		e->type == conststring_e||
		e->type == nil_e){
		return 1;
	}else{
		return 0;
	}
}

//diaf 11 sel 26
void patchlist(int list,int label){
	while(list){
		int next = quads[list].label;
		quads[list].label = label;
		list = next;
	}
}

void make_stmt(stmt_t* s){
	s->breakList = s->contList = 0;
}

int newlist(int i){
	quads[i].label = 0;
	return i;
}

//diaf 11 sel 26
int mergelist(int l1,int l2){
	if(!l1){
		return l2;
	}
	else{
		if(!l2){
			return l1;
		}else{
			int i = l1;
			while(quads[i].label){
				i=quads[i].label;
			}
			quads[i].label = l2;
			return l1;
		}
	}
}


const char* get_ic_type_to_String(iopcode type){ //metatrepei to enum iopcode se string
	switch (type) 
	{
		case assign: return "assign";
		case add: return "add";
		case sub: return "sub";
		case mul: return "mul";
		case divi: return "divi";
		case mod: return "mod";
		case uminus: return "uminus";
		case and: return "and";
		case or: return "or";
		case not: return "not";
		case if_eq: return "if_eq";
		case if_noteq: return "if_noteq";
		case if_lesseq: return "if_lesseq";
		case if_greatereq: return "if_greatereq";
		case if_less: return "if_less";
		case if_greater: return "if_greater";
		case Call: return "call";
		case param: return "param";
		case ret: return "ret";
		case getretval: return "getretval";
		case funcstart: return "funcstart";
		case funcend: return "funcend";
		case tablecreate: return "tablecreate";
		case tablegetelem: return "tablegetelem";
		case tablesetelem: return "tablesetelem";
	
	}
}

int check_expr(expr *ex){ //tiponei ta expr
switch(ex->type){
	/*case var_e:
		{printf("%-15s",ex->val.strConst);
		return 1;}
	case tableitem_e:
		{printf("%-15s",ex->val.strConst);
		return 1;}
	case programfunc_e:
		{printf("%-15s",ex->val.strConst);
		return 1;}
	case libraryfunc_e:
		{printf("%-15s",ex->val.strConst);
		return 1;}*/
	case arithexpr_e:
		{printf("%-15s",ex->val.numConst);
		//printf("mpainei1\n");
		return 1;}
	/*case boolexpr_e:
		{printf("%-15s",ex->val.strConst);
		return 1;}*/
	case assignexpr_e:
		{printf("%-15s",ex->val.strConst);
		//printf("mpainei2\n");
		return 1;}
	/*case newtable_e:
		{printf("%-15s",ex->val.strConst);
		return 1;}*/
	case constnum_e:
		{printf("%-15d",ex->x);
		//printf("mpainei3\n");
		return 1;}
	case constbool_e:
		{if(ex->val.boolConst==1)printf("true");
		else printf("false");return 1;}

	case conststring_e:
		{printf("%-15s",ex->val.strConst);
		return 1;}
	case nil_e:
		{return 1;}
	default: return 0;
	}
}


void printquads(){	//tiponei ta quads
	int counter = 0;
	quad *temp=quads;
	printf("-----------------------------------------*****************Symtable output*****************-----------------------------------------\n\n\n");
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n","quads","opcode","result","arg1","arg2","label");
	printf("-----------------------------------------------------------------------------------------------------------------------------------\n");

	while(counter < currQuad){
			//printf("mpainei stin while\n");
	temp=quads+counter;
	//printf("kanei tin temp=\n");
	printf("%-14d %-15s",counter+1,get_ic_type_to_String(temp->op));
	//if(temp != NULL){
	//	printf("h temp eiani nyll\n");
	//}
	if(temp->result!=NULL){
		printf("%-15s",temp->result->sym->value.varVal->name);//(temp->result);
	}
	if(temp->arg1!=NULL){
		if(check_expr(temp->arg1)!=0){
			//printf("mpaieni sto if\n");
		}else{
			//printf("mpainei sto else\n");
			if(temp->arg1->sym!=NULL){
				//printf("mpainei sto else sto ifasdsadas\n");
				printf("%-15s",temp->arg1->sym->value.varVal->name);//(temp->result);
			}
		}
	}//print_expr(temp->arg1);
	if(temp->arg2!=NULL){			//printf("mpaieni edw1");//print_expr(temp->arg2);
		//printf("mpainei edw;adsdsadsadsadsa	");
		if(check_expr(temp->arg2)!=0){
			//printf("mpainei edw;");
		}else{
			if(temp->arg2->sym!=NULL){//
				printf("%-15s",temp->arg2->sym->value.varVal->name);//(temp->result);
			}
		}
	}
	if(temp->label!=0)printf("%d\n",temp->label);
	printf("\n");
	counter++;	
	}
	
}


