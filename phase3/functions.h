#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>
#include <assert.h>

#define EXPAND_SIZE 1024
#define CURR_SIZE (total*sizeof(struct quad))
#define NEW_SIZE (EXPAND_SIZE*sizeof(struct quad)+CURR_SIZE)

struct stack* scopeoffsetStack ;
struct stack* loopcounterstack;

typedef struct stmt_t {
	int breakList;						//periexei toys arithmoys olwn twn quads poy kathena antistoixei se unfinished jump logw kapiou break p periexetai sto stmt
	int contList;						//periexei toyw arithmoys olwn twn quads poy kathena antistoixei se unfinished jump logw kapioy continue p periexetai sto stmt
	unsigned enter;
	unsigned test;

}stmt_t;

typedef struct call{
	struct expr* elist;
	unsigned char method;
	char* name;
}call;

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
	unsigned int iaddress;
	unsigned int totalLocals;
}Function;

/* an den valoyme to localenum to local mas petaei conflict me to local token poy exoyme ftiaksei*/
enum SymbolType {GLOBAL,LOCALE,FORMAL,USERFUNC,LIBFUNC};

typedef enum scopespace_t{
	programvar,functionlocal,formalarg
}scopespace_t;

typedef struct SymbolTableEntry {
	bool isActive;
	union {
		Variable *varVal;
		Function *funcVal;
	} value;
	enum SymbolType type;
	//int lala;
	unsigned offset;
	enum scopespace_t space;
	struct SymbolTableEntry *next;
}SymbolTableEntry;

typedef struct SymTable{ 
	SymbolTableEntry *entry;
}SymTable;


SymTable *new_Symtable();

const char* gettype_to_String(enum SymbolType type);

void insert_variable(SymTable *sym,const char *name,unsigned int scope, unsigned int line, enum SymbolType type);

void insert_function(SymTable *sym,const char *name,unsigned int scope, unsigned int line, enum SymbolType type);

void check_Var_or_Func(SymTable *sym,const char *name,unsigned int scope, unsigned int line, enum SymbolType type);

int check_type_for_print(enum SymbolType type);

int check_if_lib(const char *name,int line);

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

int check_if_function_before(int scope);

int check_if_lib_noprint(const char *name);

SymbolTableEntry *look_up_inscope_noprint(const char *name,int scope);

SymbolTableEntry *look_up(const char *name,int scope);

//last added

typedef enum expr_t{
	var_e,
	tableitem_e,
	programfunc_e,
	libraryfunc_e,
	arithexpr_e,
	boolexpr_e,
	assignexpr_e,
	newtable_e,
	constnum_e,
	constbool_e,
	conststring_e,
	nil_e
}expr_t;

//diaf 10 sel 7
typedef struct expr{
    enum expr_t type;
    SymbolTableEntry* sym;
    struct expr* index;
    int x;
    float y;
    union{
        	double numConst;					//allaxa auto apo int se double
         	char* strConst;
         	unsigned char boolConst;
    }val;
    struct expr* next;
}expr;



typedef enum iopcode {
	assign, add, sub, mul, divi, mod, uminus, and, or, not, if_eq, if_noteq, if_lesseq, if_greatereq, if_less , jump , if_greater, Call, param, ret, getretval, funcstart, funcend, tablecreate, tablegetelem, tablesetelem
}iopcode;

void expand(void);

//diaf 9 sel 44
char *newtempname();
void resettemp();
SymbolTableEntry *newtemp(SymTable *Symtable,unsigned int scope, unsigned int line);



//to result prin ta args
typedef struct quad{
	iopcode		op;
	expr*		arg1;
	expr*		arg2;
	expr* 		result;
	unsigned	label;
	unsigned	line;
}quad;

void emit(iopcode		op,
	expr*		arg1,
	expr*		arg2,
	expr* 		result,
	unsigned	label,
	unsigned	line
);

enum scopespace_t currscopespace(void);

//analoga me to currscopespace epistrefei to offset toy scope
unsigned currscopeoffset(void);

//auksanei to offset toy scope
void inccurrscopeoffset(void);

//auksanei to scopespacecounter
void enterscopespace(void);

//meiwnei to scopespacecounter
void exitscopespace(void);

unsigned nextquad(void);

void resetformalargsoffset(void);

void resetfunctionlocaloffset(void);

void restorecurrscopeoffset(unsigned n);


void makestack();

struct stack {
	int top;
	unsigned *args;
};


void patchlabel(unsigned quadNo,unsigned label);

expr* lvalue_expr (SymbolTableEntry* sym);

expr* newexpr (expr_t t);

expr* newexpr_conststring(char *s);

expr* newexpr_constbool(unsigned int b);

expr* emit_iftableitem(SymTable *Symtable,unsigned int scope,expr* e,unsigned line);

expr* member_item(SymTable *Symtable,unsigned int scope,expr* lvalue, char* name,unsigned line);

expr* make_call(SymTable *Symtable,unsigned int scope,expr *lvalue, expr* reversed_elist,unsigned line);

expr* newexpr_constnum (double i);

expr* newexpr_constbool(unsigned int b);

int check_arith(expr *e);

int check_corr_type(expr *e);

//diaf 11 sel 26
void patchlist(int list,int label);

void make_stmt(stmt_t* s);
	
int newlist(int i);

int mergelist(int l1,int l2);

int check_expr(expr *ex);

const char* get_ic_type_to_String(iopcode type);

void printquads();

