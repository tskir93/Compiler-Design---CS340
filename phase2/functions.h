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


SymTable *new_Symtable();

void printela();

void printSymtable();

const char* gettype_to_String(enum SymbolType type);
void insert_variable(SymTable *sym,const char *name,unsigned int scope, unsigned int line, enum SymbolType type);
void insert_function(SymTable *sym,const char *name,unsigned int scope, unsigned int line, enum SymbolType type);
void check_Var_or_Func(SymTable *sym,const char *name,unsigned int scope, unsigned int line, enum SymbolType type);
int check_type_for_print(enum SymbolType type);
