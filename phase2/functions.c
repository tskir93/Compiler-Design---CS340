#include "functions.h"

SymTable *head; 
int i=0;

/*synartisi gia eisagwgi enos variable sto symtable*/
void insert_variable(SymTable *sym,const char *name,unsigned int scope, unsigned int line, enum SymbolType type){
	int temp_scope;
	SymbolTableEntry *new = (SymbolTableEntry *)malloc(sizeof(SymbolTableEntry));
	Variable *new_var = (Variable *)malloc(sizeof(Variable));
	new->value.varVal = (Variable *)malloc(sizeof(Variable));

	SymbolTableEntry *temp = sym->entry;

	new_var -> name = strdup(name);
	new_var -> scope = scope;
	new_var -> line = line;
	

	/*vazoyme ston symtable to variable p ftiaksame*/
	new->isActive = 1;
	new->value.varVal =(Variable *) new_var;

	if(temp == NULL){
		head->entry = new;
		//temp = new;
	}else{
		temp_scope=new_var->scope;
		temp = sym->entry;
		while(temp->next!=NULL && temp->next->value.varVal->scope<temp_scope){
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



/*ftiaxnei enan kainourgio keno symtable kai kanei return ton deikti stin arxi toy symtable*/
SymTable *new_Symtable(){

	SymTable *new = (SymTable *)malloc(sizeof(SymTable));
	head = new;
	
	printf("ftiaxnei ton sumboltable\n");

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

	printf("-----------------------------------------*****************Symtable output*****************-----------------------------------------\n\n\n");
	
	while (ent!=NULL){
		if(check_type_for_print(ent->type)==0){
			
			printf("\"%s\"",ent->value.varVal->name);
			if(strlen(ent->value.varVal->name)<6){
				printf("\t\t\t");
			}else if(strlen(ent->value.varVal->name)>=6 && strlen(ent->value.varVal->name)<12){
				printf("\t\t");	
			}else{
				printf("\t");
			}
			printf("[ %s ]\t",gettype_to_String(ent->type));
			printf("( line %d )\t",ent->value.varVal->line);
			printf("( scope %d )\n",ent->value.varVal->scope);

		}else if(check_type_for_print(ent->type)==1){
			printf("\"%s\"\t\t",ent->value.funcVal->name);
			if(strlen(ent->value.varVal->name)<6){
				printf("\t\t\t");
			}else if(strlen(ent->value.varVal->name)>=6 && strlen(ent->value.varVal->name)<12){
				printf("\t\t");	
			}else{
				printf("\t");
			}

			printf("[ %s ]\t\t",gettype_to_String(ent->type));
			printf("( line %d )\t\t",ent->value.funcVal->line);
			printf("( scope %d )\n",ent->value.funcVal->scope);

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
				if(strlen(ent->value.varVal->name)<6){
					printf("\t\t\t");
				}else if(strlen(ent->value.varVal->name)>=6 && strlen(ent->value.varVal->name)<12){
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
				if(strlen(ent->value.varVal->name)<6){
					printf("\t\t\t");
				}else if(strlen(ent->value.varVal->name)>=6 && strlen(ent->value.varVal->name)<12){
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

int look_up(const char *name)
{	
	int type;
	SymbolTableEntry *temp = head->entry;

	const char *temp_name = name;
	
	while(temp!=NULL && (temp_name!=temp->value.varVal->name ||temp_name!=temp->value.funcVal->name)){
		temp=temp->next;
	}
	if(temp!=NULL){
		
		printf("/n name %s  scope %d  line %d",temp->value.funcVal->name,temp->value.funcVal->scope,temp->value.funcVal->line);
		return 1;
	}
	return 0;
}


int check_lib_func(Variable *x){
	SymbolTableEntry *ent = head->entry;

	while(ent!=NULL && ent->type == LIBFUNC){
		if(x->name != ent->value.funcVal->name){
			ent = ent->next;
		}else{
			printf("Error - A LIBFUNC have the same Name \n");
			return 1;
		}
	}
	return 0;
}