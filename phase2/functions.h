#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>



typedef struct Variable {
	const char *name;
	unsigned int scope;
	unsigned int line;
}Variable;

typedef struct Function {
	const char *name;
	//List of arguments
	unsigned int scope;
	unsigned int line;
}Function;

/* an den valoyme to localenum to local mas petaei conflict me to local token poy exoyme ftiaksei*/
enum SymbolType {GLOBAL,LOCALE,FORMAL,USERFUNC,LIBFUNC};


typedef struct SymbolTableEntry {
	bool isActive;
	union {
		Variable *varVal;
		Function *funcVal;
	} value;
	enum SymbolType type;
	struct SymbolTableEntry *next;
}SymbolTableEntry;

typedef struct SymTable{ 
	SymbolTableEntry *entry;
}SymTable;

/*Constracting a new SymbolTable*/
SymTable *new_Symtable();

/*Taking the type argument and comverting it from type enum to string*/
const char* gettype_to_String(enum SymbolType type);

/*Function for inserting a variable in Symtable*/
void insert_variable(SymTable *sym,const char *name,unsigned int scope, unsigned int line, enum SymbolType type);

/*Function for inserting a function in Symtable*/
void insert_function(SymTable *sym,const char *name,unsigned int scope, unsigned int line, enum SymbolType type);

void check_Var_or_Func(SymTable *sym,const char *name,unsigned int scope, unsigned int line, enum SymbolType type);

int check_type_for_print(enum SymbolType type);

int check_if_lib(const char *name);

void hide(int scope);

void printSymtable();

void printSymtable_hide();

char *randomfunc();

/*checks if a x is global or formal*/
enum SymbolType check_Var_type_for_function_arg(int scope);

/*checks if a ->local x , is global or local*/
enum SymbolType check_Var_type_local(int scope);


SymbolTableEntry *look_up_inscope(const char *name,int scope);

int check_type(SymbolTableEntry *ent);

SymbolTableEntry *look_up(const char *name,int scope);

void printSymtable_byscope();

//Function only fro parsing the func with $$=$1 to save the type for later use
SymbolTableEntry *look_up_inscope_noprint(const char *name,int scope);

/*gia na xeiristw px tin print(x) den thelw na ektypwnei error apla na tsekarw an einai libfunc*/
int check_if_lib_noprint(const char *name);