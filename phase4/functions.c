#include "functions.h"


SymTable *head; 


int random_num = 0;
int i=0;
char name[] ="_f";

/*phase 3*/
quad *quads = (quad*) 0;
unsigned total = 0;
unsigned int currQuad = 0;
int tempcounter = 0;

instruction *instructions = (instruction*) 0;						//kratame ola ta instructions 
unsigned int currinstruction = 0; 								//kratame to teleutaio instruction gia na to xrisimopoiisoume stin nextinstructionlabel()
unsigned total_instructions = 0;

struct incomplete_jump* ij_head = NULL;
unsigned ij_total = 0;

unsigned programVarOffset = 0;
unsigned functionLocalOffset = 0;
unsigned formalArgOffset = 0;
unsigned scopeSpaceCounter = 1;

unsigned currprocessedquad = 0;

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
				}else if(strlen(ent->value.varVal->name) > 2 && strlen(ent->value.varVal->name)<6){				//phasi 3 peiraksa auto gia na euthugrammisw mia grammi +2tabs
					printf("\t\t\t\t\t");
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
void expand(void){	//megalonoume ton dinamiko pinaka mas
	assert (total == currQuad);
	quad* p = (quad*)malloc(NEW_IN_SIZE);
	if(quads){
		memcpy(p, quads,CURR_IN_SIZE);
		free(quads);
	}
	quads = p;
	total += EXPAND_SIZE;
}
/*
void expand_numC(void){	//megalonoume ton dinamiko pinaka ton numbers
	assert (total_num == curr_num);
	double* i = (double*)malloc(NEW_NUM);
	if(numConsts){
		memcpy(i, numConsts,CURR_NUM);
		free(numConsts);
	}
	numConsts = i;
	total_num += EXPAND_SIZE;
}

void expand_stringC(void){	//megalonoume ton dinamiko pinaka ton string
	assert (total_string == curr_string);
	char ** i = (char**)malloc(NEW_STRING);
	if(stringConsts){
		memcpy(i, stringConsts,CURR_STRING);
		free(stringConsts);
	}
	stringConsts = i;
	total_string += EXPAND_SIZE;
}

void expand_libfuncs(void){	//megalonoume ton dinamiko pinaka ton libfuncs
	assert (total_libfuncs == curr_libfuncs);
	char ** i = (char**)malloc(NEW_STRING);
	if(namedLibfuncs){
		memcpy(i, namedLibfuncs,CURR_STRING);
		free(namedLibfuncs);
	}
	namedLibfuncs = i;
	total_libfuncs += EXPAND_SIZE;
}

void expand_userfuncs(void){	//megalonoume ton dinamiko pinaka ton userfuncs
	assert (total_userfuncs == curr_userfuncs);
	struct userfunc* i = (struct userfunc *)malloc(NEW_STRING);
	if(userFuncs){
		memcpy(i, userFuncs,CURR_STRING);
		free(userFuncs);
	}
	userFuncs = i;
	total_userfuncs += EXPAND_SIZE;
}
*/
//diaf 9 sel 38
void emit(	//paragogi mias neas entolis
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
char *newtempname(){	//paragei ena neo onoma xrhsimopoiontas ton tempcounter
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
SymbolTableEntry *newtemp(SymTable *Symtable,unsigned int scope, unsigned int line){	//epistrefei eite mia nea krifi metabliti h mia idi diathesimi me to onoma newtempname
	char *name = newtempname();
	SymbolTableEntry *sym = look_up_inscope_noprint(name,scope);
	
	if (sym!=NULL){
		return sym; //epistrefoume tin idi diathesimi  metabliti
	}else{
        
		//char * new_name = newtempname();
        insert_variable(Symtable,name,scope,line,LOCALE);
        SymbolTableEntry *sym = look_up_inscope_noprint(name,scope);
        //sym->lala =1;
        return sym;
	}
}

 scopespace_t currscopespace(void){	//anagnorizoume to paron scope
	if(scopeSpaceCounter == 1){
		return programvar;
	}else if(scopeSpaceCounter % 2 == 0){
		return formalarg;
	}else{
		return functionlocal;
	}
}

unsigned currscopeoffset(void){	//gia kathe scope space diatiro ksexoristo offset
	switch (currscopespace()){
		case programvar 	: 	return programVarOffset;
		case functionlocal 	:	return functionLocalOffset;
		case formalarg 		:	return formalArgOffset;
		default				: 	assert(0);
	}
}

void inccurrscopeoffset(void){	//me kathe nea dilosi metablitis ayksanetai to offset to sugekrimenou scope
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

expr* lvalue_expr (SymbolTableEntry* sym){	//ftiaxnoume  ena lvalue_exp apo ena sym
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
expr* emit_iftableitem(SymTable *Symtable,unsigned int scope,expr* e,unsigned line){	//otan exoume lvalue.id opou to lvalue einai st.pnk paragoume tin entoli pou pairnei auto to stoixeio
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
expr* make_call(SymTable *Symtable,unsigned int scope,expr *lvalue, expr* reversed_elist,unsigned line){	//kaloume mia sinartisi
	expr* func = emit_iftableitem(Symtable,scope,lvalue,line);
	//emit(param,reversed_elist,NULL,NULL,0,line);				//added this to prin the sprite in the tes
	
	while(reversed_elist){
		emit(param,reversed_elist,NULL,NULL,0,line);
		reversed_elist = reversed_elist->next;
	}
	//reversed_elist = lvalue;
	//emit(param,reversed_elist,NULL,NULL,0,line);

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



int check_arith(expr *e){	//elegxoume gia tin sosti xrisi ekfraseon se arithmitikes praxeis
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
void patchlist(intlist_node *list,int label){
	while(list){
		patchlabel(list->val, nextquad());
		list = list->next;	
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
		case jump: return "jump";			//tskir: added jump
	
	}
}

int check_expr(expr *ex){ //tiponei ta expr
switch(ex->type){
	//case var_e:
	//	{printf("%-15s",ex->val.strConst);
	//	return 1;}
	//case tableitem_e:
	//	printf("mpainei edw gia tableitem\n");
	//	{printf("%-15s",ex->val.strConst);
	//	return 1;}
	case programfunc_e:
		//printf("mpainei edw programfunc\n");
		{printf("%-15s",ex->sym->value.varVal->name);
		return 1;}
	/*case libraryfunc_e:
		{printf("%-15s",ex->sym->value.varVal->name);
		return 1;}*/
////	case arithexpr_e:
////		{printf("%-15s",ex->val.numConst);
		//printf("mpainei1\n");
////		return 1;}
	/*case boolexpr_e:
		{printf("%-15s",ex->val.strConst);
		return 1;}*/
////	case assignexpr_e:
////		{printf("%-15s",ex->val.strConst);
		//printf("mpainei2\n");
////		return 1;}
	/*case newtable_e:
		{printf("%-15s",ex->val.strConst);
		return 1;}*/
	case constnum_ereal:
		{printf("%-15.2f",ex->y);
		//printf("mpainei3\n");
		return 1;}
	case constnum_e:
		{printf("%-15d",ex->x);
		//printf("mpainei3\n");
		return 1;}
	case constbool_e:
		//printf("mpainei edw\n");
		{if(ex->val.boolConst==1)printf("%-15s","\'false\'");
		else printf("%-15s","\'true\'");return 1;}

	case conststring_e:
		{printf(" \"%s%-12s ",ex->val.strConst,"\"");
		return 1;}
////	case nil_e:
////		{return 1;}
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

	if(temp->result!=NULL){
		//printf("mpainei sto 1o\n");
		if(temp->op == ret){							//checks if op is return and if it is we check whats the return arg with checkexpr
			//printf("mpainei edw gia return\n");
			check_expr(temp->result);					//an einai arithmos tha tupwsei ton arithmo
		}else if(temp->op == tablesetelem && temp->result->type!=newtable_e){				//checks if op is tablesetelem kai kanei print analoga ti einai( to exw elegxei me arithmo gia arxi)
			//printf("mpainei edw\n");
			printf("%-15s",temp->result->sym->value.varVal->name);				//typwnei to temp.val -> _f0
			
			check_expr(temp->result);
		//}else if(){
			//printf("mpainei edw gia auto\n");
			//printf("einai tupoy %s\n",get_ic_type_to_String(temp->result.type));
		}else{
			//if(temp->result->sym->value.varVal->name!=NULL){
				printf("%-15s",temp->result->sym->value.varVal->name);//(temp->result);
			//}
		}
	}
	if(temp->arg1!=NULL){
		//printf("mpainei sto 2o\n");
		if(check_expr(temp->arg1)!=0 ){
			//printf("mpaieni sto if\n");

		}else{
			if(temp->arg1->sym!=NULL ){
				//printf("mpainei sto edwwwwwwwww\n");
				//printf("mpainei sto else sto ifasdsadas\n");

				printf("%-14s",temp->arg1->sym->value.varVal->name);//(temp->result);
				//printf("seg\n");
			}
		}
	}
	if(temp->arg2!=NULL){			//printf("mpaieni edw1");//print_expr(temp->arg2);
		//printf("mpainei edwadsdsadsadsads\n");
		if(check_expr(temp->arg2)!=0){
			//printf("mpainei edw;");
		}else{
			if(temp->arg2->sym!=NULL){//
				printf("%-14s",temp->arg2->sym->value.varVal->name);//(temp->result);
			}
		}
	}
	
	if(temp->label!=0){
		//printf("mpainei edw\n");
		printf("%d\n",temp->label);
	}else{
			printf("\n");								//kanei print to enter an den uparxei label
	}
	counter++;	
	}	
	
}

//bazo ena item stin arxi tis listas
void insertlist(intList* head,int val){ 
	intlist_node * current = malloc(sizeof(intlist_node));
	current->val=val;
	current->next=head->List;
	head->List=current;
}

void whilestmt_check_lists(intList *breaklist_head,intList* contlist_head,unsigned arg1){
	if(breaklist_head->List!=NULL){	
		patchlabel(breaklist_head->List->val,nextquad());
	//}else{
	//	patchlabel(0,nextquad());
	}
	if(contlist_head->List!=NULL){
		patchlabel(contlist_head->List->val,arg1);	
//	}else{
	//	patchlabel(0,nextquad());
	}
}

void forstmt_check_lists(intList *breaklist_head,intList* contlist_head,unsigned arg1){
	if(breaklist_head->List!=NULL){		
		patchlabel(breaklist_head->List->val,nextquad()+1);
//	}else{
//		patchlabel(0,nextquad());
	}
	if(contlist_head->List!=NULL){
		patchlabel(contlist_head->List->val,arg1+1);	
//	}else{
//		patchlabel(0,nextquad());
	}
}

/**************************************** phase 4****************************************************/
//diaf 9 sel 38
unsigned nextinstructionlabel(void){
	return currinstruction;
}

void expand_instr(void){	//megalonoume ton dinamiko pinaka mas
	assert (total_instructions == currinstruction);
	instruction* i = (instruction*)malloc(NEW_IN_SIZE);
	if(instructions){
		memcpy(i, instructions,CURR_IN_SIZE);
		free(instructions);
	}
	instructions = i;
	total_instructions += EXPAND_SIZE;
}

void emit_instr(instruction *t){
	//printf("mpainei stin emit instr\n");
	if (currinstruction == total_instructions)
		expand_instr();
	instruction* p = instructions + currinstruction++;
	p->opcode = t->opcode;
	p->arg1	= t->arg1;
	p->arg2	= t->arg2;
	p->result = t->result;
	p->srcLine = t->srcLine;
	//printf("vgainei apo tin emit instr\n");
}




avmbinaryfile(){
	int i;
	FILE *binfile;
	binfile = fopen("binary.abc","wb");						//wb s write binary
	if(binfile == NULL){
		printf("Error opening file\n");
		exit(1);
	}
	unsigned magicnumber = 340200501;
	fwrite(&magicnumber, sizeof(unsigned),1,binfile);					//writing magicnumber in binary file
	fwrite(&numSize,sizeof(unsigned),1,binfile);						//pername to megethos kathe pinaka meta to magicnumber k m auti ti seira tha t diavasoyme k sto readbinary
	fwrite(&stringSize,sizeof(unsigned),1,binfile);
	fwrite(&namedLibSize,sizeof(unsigned),1,binfile);
	fwrite(&userfuncSize,sizeof(unsigned),1,binfile);
	fwrite(&currinstruction,sizeof(unsigned),1,binfile);

	for(i=0;i<stringSize;i++){
		stringlength[i] = strlen(stringConsts[i]);						//+1 gia to \0
	}

	for(i=0;i<namedLibSize;i++){
		libfuncslength[i] = strlen(namedLibfuncs[i]);
	}

	//pername ola ta arrays sto binary
	for(i=0;i<numSize;i++){
		fwrite(&numConsts[i],sizeof(double),1,binfile);					//grafei olo ton pinaka me ta numConsts sto binary
	}

	for(i=0;i<stringSize;i++){
		fwrite(&stringlength[i],sizeof(int),1,binfile);					//pernaw ton pinaka p periexei to length kathe string gia na ton exw otan tha desmevw xwro sto fopen binary
	}

	for(i=0;i<namedLibSize;i++){
		fwrite(&libfuncslength[i],sizeof(int),1,binfile);				//pernav ton pinaka p periexei to length kathe libfunc gia na ton exw otan tha krataw xwro stin fopen 
	}

	for(i=0;i<stringSize;i++){
		fwrite(stringConsts[i],sizeof(char),strlen(stringConsts[i]),binfile);
	}

	for(i=0;i<namedLibSize;i++){
		fwrite(namedLibfuncs[i],sizeof(char),strlen(namedLibfuncs[i]),binfile);
	}

	for(i=0;i<userfuncSize;i++){
		userfuncslength[i] = strlen(userFuncs[i].id);
	}

	for(i=0;i<userfuncSize;i++){
		fwrite(&userfuncslength[i],sizeof(int),1,binfile);				//pernav ton pinaka p periexei to length kathe libfunc gia na ton exw otan tha krataw xwro stin fopen 
	}

	for(i=0;i<userfuncSize;i++){
		fwrite(&userFuncs[i].taddress,sizeof(userFuncs),1,binfile);
		fwrite(&userFuncs[i].localSize,sizeof(userFuncs),1,binfile);
		fwrite(userFuncs[i].id,sizeof(char),strlen(userFuncs[i].id),binfile);
	}

	for(i=0;i<currinstruction;i++){
		fwrite(&instructions[i],sizeof(instruction),1,binfile);
	}



	fclose(binfile);


	//arrays();
	//code();
}


//unsigned magicnumber(){
//	unsigned x = 340200501;
//	return x;
//}


//arrays(){
	//strings();
	//numbers();
	//userfunctions();
//	libfunctions();

//}
/*
strings(){
	unsigned n;
	if( !match(UNSIGNED)){
		return false;
	}else{
		for(n=currtoken.intVal;n;--n){
			string();
		}
	}
}*/

//----------------------------------entoles gia avm-------------------------------------------------------------

//----------------------------------code for generation-------------------------------------------------------------

unsigned consts_newstring(const char *s){
	int i;
	if(stringConsts == NULL){
		//printf("mpainei sto numconsts=null\n");
		//printf("to n eiani iso me = %f\n",n);
		stringConsts=(char **)malloc(1024*sizeof(char*));
		stringlength = (int*)malloc(1024*sizeof(int));
	}
	for(i=0;i<stringSize;i++){
		if(strcmp(s,stringConsts[i])==0){					//an to string uparxei idi epistrefei to i poy vrisketai ston pinaka
			return i;
		}
	}	
	stringConsts[stringSize] = strdup(s);
	i = stringSize;											//ekxwroyme sto i to teleutaio index gia na mporoyme na to epistrepsoyme
	stringSize++;											//auksanoyme to stringsize poy mas leei posa strings exei o pinakas
	return i;
}

unsigned consts_newnumber(double n){
	int i;
	if(numConsts == NULL){
		//printf("mpainei sto numconsts=null\n");
		//printf("to n eiani iso me = %f\n",n);
		numConsts=(double *)malloc(1024*sizeof(double));
	}
	for(i=0;i<numSize;i++){
		if(numConsts[i] == n){
			return i;
		}
	}
	printf("ola kala\n");
	numConsts[numSize] = n;								//vazw to n sto teleutaio stoixeio toy pinaka
	i = numSize;										//krataw to index gia na to epistrepsw
	numSize++;
	return i;											//epistrefw ti thesi p evala to teleutaio double
}

unsigned libfuncs_newused(const char* s){
	int i;
	if(namedLibfuncs == NULL){
		namedLibfuncs = (char**)malloc(1024*sizeof(char*));
		libfuncslength = (int*)malloc(1024*sizeof(int));
	}
	for(i=0;i<namedLibSize;i++){
		if(strcmp(s,namedLibfuncs[i])==0){					//an to string uparxei idi epistrefei to i poy vrisketai ston pinaka
			return i;
		}
	}	
	namedLibfuncs[namedLibSize] = strdup(s);
	i = namedLibSize;											//ekxwroyme sto i to teleutaio index gia na mporoyme na to epistrepsoyme
	namedLibSize++;											//auksanoyme to namedLibSize poy mas leei posa strings exei o pinakas
	return i;
}

unsigned userfuncs_newfunc(SymbolTableEntry* sym){
	int i;
	if(userFuncs == NULL){
		userFuncs = (struct userfunc*)malloc(1024*sizeof(struct userfunc));
		userfuncslength = (int*)malloc(1024*sizeof(int));
	}
	for(i=0;i<userfuncSize;i++){
		if(strcmp(userFuncs[i].id,sym->value.funcVal->name)==0){
			return i;
		}
	}
	userFuncs[userfuncSize].id = sym->value.funcVal->name;
	userFuncs[userfuncSize].taddress = nextinstructionlabel();
	userFuncs[userfuncSize].localSize = sym->value.funcVal->totalLocals;
	i = userfuncSize;
	userfuncSize++;
	return i;

}



//sel 11 diaf 14
void make_operand(expr* e, vmarg* arg){	//exr->input,vmarg->output
	if(e == NULL)
	{
		arg=NULL;
		//printf("to expr einai null\n");
		//exit(1);
		return;
	}
	switch(e->type){
		case var_e:			//auta kseroume epipleon oti tha einai kai krifes metablites
		case tableitem_e:
		case arithexpr_e:
		case boolexpr_e:
		case newtable_e:{
			assert(e->sym);
			arg->val = e->sym->offset;

			switch(e->sym->space){
				case programvar: arg->type = global_a;break;
				case functionlocal: arg->type = local_a;break;
				case formalarg: arg->type = formal_a;break;
				default: assert(0);
			}
			break;
		}

		case constbool_e:{
			arg->val = e->val.boolConst;
			arg->type = bool_a;
			break;
		}

		case conststring_e:{
			arg->val = consts_newstring(e->val.strConst);
			
			arg->type = string_a;
			break;
		}

		case constnum_e:{
			//printf("mpainei edw\n");
			arg->val = consts_newnumber(e->x);
			printf("e->x == %d\n",e->x);
			printf("argval = %d\n",arg->val);
			arg->type = number_a;
			break;
		}
		
		case constnum_ereal:{
			arg->val = consts_newnumber(e->y);
			arg->type = number_a;
			break;
		}

		case nil_e:{
			 arg->type = nil_a;
			break;
		}

		case programfunc_e:{
			printf("mpanei sto programfunc_e\n");
			arg->val = userfuncs_newfunc(e->sym);
			arg->type = userfunc_a;
			break;
		}

		case libraryfunc_e:{
			arg->type = libfunc_a;
			arg->val = libfuncs_newused(e->sym->value.funcVal->name);
			break;
		}

		//default: assert(0);
	}
}

//pame sto telos twn incomplete jumps kai prosthetoume to kainourgio incomplete jump
//oysiastika ftiaxnoume mia lista apo jumps poy sti sunexeia tin xrisimopoioume gia na kanoyme patch ta incomplete jumps
//diaf 14 sel 15
void add_incomplete_jump(unsigned instrNo,unsigned iaddress){
	incomplete_jump *new = (struct incomplete_jump*)malloc(sizeof(incomplete_jump));
	new->instrNo = instrNo;
	new->iaddress = iaddress;
	new->next = NULL;
	incomplete_jump *temp = ij_head;

	if(temp == NULL){				//an eiani kena ta incomplete jumps to vazoume stin arxi
		temp = new;
		ij_head = temp;
		ij_total++;			
	}else{							//alliws briskoume to telos k ta vazoume ekei
		while(temp->next!=NULL){
			temp = temp->next;
		}
		temp->next = new;
		ij_total++;
	}
}

//diaf 14 sel 15
void patch_incomplete_jumps(){
	incomplete_jump *temp = ij_head;
	int i;
	for(i=0;i<ij_total;i++){
		if(temp!=NULL){
			if(temp->iaddress == currQuad){
				instructions[temp->instrNo].result.val = currinstruction;						//an to jump ston proigoumeno kwdika edeixne sto telos twra to kanoyme na deixnei sto kainourgio telos twn instructions
			}else{
				instructions[temp->instrNo].result.val = quads[temp->iaddress].taddress;		
			}
			temp = temp->next;
		}
	}
}

void make_numberoperand(vmarg* arg, double val){
	arg->val = consts_newnumber(val);
	arg->type = number_a;
}

void make_booloperand(vmarg* arg, unsigned val){
	arg->val = val;
	arg->type = bool_a;
}

void make_retvaloperand(vmarg* arg){
	arg->type = retval_a;
}

unsigned currprocessed_quad(){
	return currprocessedquad;
}

//sel 17 diaf 14
void generate(vmopcode op,quad* quad){
	instruction *t = (instruction *)malloc(sizeof(instruction));
	t->opcode = op;
	make_operand(quad->arg1,&t->arg1);
	make_operand(quad->arg2,&t->arg2);
	make_operand(quad->result,&t->result);
	quad->taddress = nextinstructionlabel();
	//printf("mpainei stin generate\n");
	emit_instr(t); 									
}

void reset_operand(vmarg *arg){
	arg->type = nil_a;
}


void generate_ADD(quad* quad){generate(add_v,quad);}
void generate_SUB(quad* quad){generate(sub_v,quad);}
void generate_MUL(quad* quad){generate(mul_v,quad);}
void generate_DIV(quad* quad){generate(div_v,quad);}
void generate_MOD(quad* quad){generate(mod_v,quad);}
void generate_NEWTABLE(quad* quad){generate(newtable_v,quad);}
void generate_TABLEGETELEM(quad* quad){generate(tablegetelem_v,quad);}
void generate_TABLESETELEM(quad* quad){generate(tablesetelem_v,quad);}
void generate_ASSIGN(quad* quad){generate(assign_v,quad);}

void generate_NOP(){
	instruction *t = (instruction *)malloc(sizeof(instruction));
	t->opcode = nop_v;

	emit_instr(t);
}



//sel 18 diaf 14
void generate_relational(vmopcode op,quad* quad){
	//printf("mpainei stin generate relational\n");
	instruction *t = (instruction *)malloc(sizeof(instruction));
	t->opcode = op;
	make_operand(quad->arg1,&t->arg1);
	make_operand(quad->arg2,&t->arg2);

	t->result.type = label_a;
	if(quad->label < currprocessed_quad()){
		t->result.val = quads[quad->label].taddress;
	}else{
		add_incomplete_jump(nextinstructionlabel(),quad->label);
	}
	quad->taddress = nextinstructionlabel();
	emit_instr(t);
}

void generate_JUMP(quad* quad){generate_relational(jump_v,quad);}
void generate_IF_EQ(quad* quad){generate_relational(jeq_v,quad);}
void generate_IF_NOTEQ(quad* quad){generate_relational(jne_v,quad);}
void generate_IF_GREATER(quad* quad){generate_relational(jgt_v,quad);}
void generate_IF_GREATEREQ(quad* quad){generate_relational(jge_v,quad);}
void generate_IF_LESS(quad* quad){generate_relational(jlt_v,quad);}
void generate_IF_LESSEQ(quad* quad){generate_relational(jle_v,quad);}

//sel20 diaf 14
void generate_NOT(quad* quad){
	quad->taddress = nextinstructionlabel();
	instruction *t = (instruction *)malloc(sizeof(instruction));

	t->opcode = jeq_v;
	make_operand(quad->arg1,&t->arg1);
	make_booloperand(&t->arg2,1);
	t->result.type = label_a;
	t->result.val = nextinstructionlabel()+3;
	emit_instr(t);

	t->opcode = assign_v;
	make_booloperand(&t->arg1,1);
	reset_operand(&t->arg2);
	make_operand(quad->result,&t->result);
	emit_instr(t);

	t->opcode = jump_v;
	reset_operand(&t->arg1);
	reset_operand(&t->arg2);
	t->result.type = label_a;
	t->result.val = nextinstructionlabel()+2;
	emit_instr(t);

	t->opcode = assign_v;
	make_booloperand(&t->arg1,0);
	reset_operand(&t->arg2);
	make_operand(quad->result,&t->result);
	emit_instr(t);
}

//true = 0 , false = 1
//sel22 diaf 14
void generate_OR(quad* quad){
	quad->taddress = nextinstructionlabel();
	instruction *t = (instruction *)malloc(sizeof(instruction));

	t->opcode = jeq_v;
	make_operand(quad->arg1,&t->arg1);
	make_booloperand(&t->arg2,0);							//anti true vazw 0 giati to true anti 1 poy eprepe na einai to exoyme ulopoiisei na einai 0
	t->result.type = label_a;
	t->result.val = nextinstructionlabel()+4;
	emit_instr(t);

	make_operand(quad->arg2,&t->arg1);
	t->result.val = nextinstructionlabel()+3;
	emit_instr(t);

	t->opcode = assign_v;
	make_booloperand(&t->arg1,1);
	reset_operand(&t->arg2);
	make_operand(quad->result,&t->result);
	emit_instr(t);

	t->opcode = jump_v;
	reset_operand(&t->arg1);
	reset_operand(&t->arg2);
	t->result.type = label_a;
	t->result.val = nextinstructionlabel()+2;
	emit_instr(t);

	t->opcode = assign_v;
	make_booloperand(&t->arg1,0);
	reset_operand(&t->arg2);
	make_operand(quad->result,&t->result);
	emit_instr(t);
}

//sel23
void generate_PARAM(quad* quad){
	//printf("mpainei sto operand\n");
	quad->taddress = nextinstructionlabel();
	instruction *t = (instruction *)malloc(sizeof(instruction));
	t->opcode = pusharg_v;
	make_operand(quad->arg1,&t->arg1);
	make_operand(quad->arg2,&t->arg2);
	make_operand(quad->result,&t->result);
	emit_instr(t);
}

void generate_CALL(quad* quad){
	quad->taddress = nextinstructionlabel();
	instruction *t = (instruction *)malloc(sizeof(instruction));
	t->opcode = call_v;	//added by goerge
	make_operand(quad->arg1,&t->arg1);
	make_operand(quad->arg2,&t->arg2);
	make_operand(quad->result,&t->result);
	emit_instr(t);
}

void generate_GETRETVAL(quad* quad){
	quad->taddress = nextinstructionlabel();
	instruction *t = (instruction *)malloc(sizeof(instruction));
	t->opcode = assign_v;
	make_operand(quad->result,&t->result);
	make_retvaloperand(&t->arg1);
	make_operand(quad->arg2,&t->arg2);
	emit_instr(t);
}

void generate_FUNCSTART(quad* quad){
	//printf("mpainei edw\n");
	quad->taddress = nextinstructionlabel();
	//sel 25 thelei sumplirwmwaaaaaaaaaaaa
	
	instruction *t = (instruction *)malloc(sizeof(instruction));
	//printf("mpainei edw1\n");
	t->opcode = funcenter_v;
	//printf("mpainei edw 2\n");
	t->srcLine = quad->line;
	//printf("mpainei edw 3\n");
	make_operand(quad->result,&t->result);
	make_operand(quad->arg1,&t->arg1);
	make_operand(quad->arg2,&t->arg2);
	emit_instr(t);
}

void generate_RETURN(quad* quad){

	quad->taddress = nextinstructionlabel();
	instruction *t = (instruction *)malloc(sizeof(instruction));
	t->opcode = assign_v;
	make_retvaloperand(&t->result); //added by george
	make_operand(quad->arg1,&t->arg1);
	make_operand(quad->arg2,&t->arg2);
	emit_instr(t);

	//thelei simplirwmma sel 25 diaf 14

	t->opcode = jump_v;
	reset_operand(&t->arg1);
	reset_operand(&t->arg2);
	t->result.type = label_a;
	emit_instr(t);
}

void generate_FUNCEND(quad* quad){
	//thelei simplirwma sel26 diaf 14
	quad->taddress = nextinstructionlabel();
	instruction *t = (instruction *)malloc(sizeof(instruction));
	t->opcode = funcexit_v;
	make_operand(quad->result,&t->result);
	emit_instr(t);
}

generator_func_t generators[] = {
	generate_ADD,
	generate_SUB,
	generate_MUL,
	generate_DIV,
	generate_MOD,
	generate_NEWTABLE,
	generate_TABLEGETELEM,
	generate_TABLESETELEM,
	generate_ASSIGN,
	generate_NOP,
	generate_JUMP,
	generate_IF_EQ,
	generate_IF_NOTEQ,
	generate_IF_GREATER,
	generate_IF_GREATEREQ,
	generate_IF_LESS,
	generate_IF_LESSEQ,
	generate_NOT,
	generate_OR,
	generate_PARAM,
	generate_CALL,
	generate_GETRETVAL,
	generate_FUNCSTART,
	generate_RETURN,
	generate_FUNCEND
};

void generate_all(void){
	unsigned i;
	printf("total quads = %d\n",currQuad);

	for(i = 0;i<currQuad;i++){
		(*generators[quads[i].op])(quads+i);
		currprocessedquad = i;							//to i mas deixnei poio eiani to currentprocessed quad p eimaste
		//printf("ftanei edw\n");
	printf("total instructions = %d\n",currinstruction);

	}


}

void print_tables(void){
	int i;
	printf("***********CONSTNUMS***********\n");
	printf("Constnums total = %d\n\n",numSize );
	for(i=0;i<numSize;i++){
		printf("%d : %f \n",i,numConsts[i]);
	}
	printf("\n");

	printf("***********STRINGS***********\n");
	printf("Strings total = %d\n\n",stringSize );
	for(i=0;i<stringSize;i++){
		printf("%d : %s \n",i,stringConsts[i]);
	}
	printf("\n");

	printf("***********LIBFUNCS***********\n");
	printf("Libfuncs total = %d\n\n",namedLibSize );
	for(i=0;i<namedLibSize;i++){
		printf("%d : %s \n",i,namedLibfuncs[i]);
	}
	printf("\n");

	printf("***********USERFUNCS***********\n");
	printf("Userfuncs total = %d\n\n",userfuncSize );
	for(i=0;i<userfuncSize;i++){
		printf("%d : %s \n",i,userFuncs[i].id);
	}
	printf("\n");
}

