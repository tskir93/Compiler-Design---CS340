#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <stdarg.h>

#define AVM_STACKSIZE 4096
#define AVM_WIPEOUT(m)	memset(&(m),0,sizeof(m))	//set ola ta bytes me miden
#define AVM_STACKENV_SIZE 4
#define AVM_ENDING_PC currinstruction
#define AVM_MAX_INSTRUCTIONS (unsigned)funcexit_v
#define AVM_TABLE_HASHSIZE 211

#define AVM_NUMACTUALS_OFFSET 	+4
#define AVM_SAVEDPC_OFFSET 		+3
#define AVM_SAVEDTOP_OFFSET		+2
#define AVM_SAVEDTOPSP_OFFSET	+1


double consts_getnumber(unsigned index);
char* consts_getstring(unsigned index);
char* libfuncs_getused(unsigned index);

double * numConsts;		//pinakes statheron timon
unsigned numSize;

char** stringConsts;
unsigned stringSize;
int *stringlength;						//pinakas gia na kratame to length twn string wste na to pername k auto sto binary


char** namedLibfuncs;
unsigned namedLibSize;
int *libfuncslength;					//pinakas gia na kratame to length twn libfunc


struct userfunc* userFuncs;
unsigned userfuncSize;
int *userfuncslength;

unsigned magicnumber;

typedef struct userfunc{
	unsigned taddress;							//function taddress
	unsigned localSize;							//total locals
	char* id;									//to kanoume char id apo const char id
}userfunc;

//diaf13 sel 17
/*typedef enum vmopcode{
	assign_v,
	add_v,
	sub_v,
	mul_v,
	div_v,
	mod_v,
	uminus_v,
	and_v,
	or_v,
	not_v,
	jeq_v,
	jne_v,
	jle_v,
	jge_v,
	jlt_v,
	jgt_v,
	call_v,
	pusharg_v,
	funcenter_v,
	funcexit_v,
	newtable_v,
	tablegetelem_v,
	tablesetelem_v,
	nop_v,
	jump_v
}vmopcode;*/

//diaf13 sel 17
typedef enum vmopcode{
	assign_v,
	add_v,
	sub_v,
	mul_v,
	div_v,
	mod_v,
	uminus_v,
	and_v,
	or_v,
	not_v,
	jeq_v,
	jne_v,
	jle_v,
	jge_v,
	jlt_v,
	jump_v,
	jgt_v,
	call_v,
	pusharg_v,
	funcenter_v,
	funcexit_v,
	newtable_v,
	tablegetelem_v,
	tablesetelem_v,
	nop_v
}vmopcode;

typedef enum vmarg_t{
	label_a = 0,
	global_a = 1,
	formal_a = 2,
	local_a = 3,
	number_a = 4,
	string_a = 5,
	bool_a = 6,
	nil_a = 7,
	userfunc_a = 8,
	libfunc_a = 9,
	retval_a = 10
}vmarg_t;

typedef struct vmarg{
	vmarg_t type;
	unsigned val;
}vmarg;


typedef struct instruction{
	vmopcode opcode;
	vmarg result;
	vmarg arg1;
	vmarg arg2;
	unsigned srcLine;
}instruction;
	

//sel21 diaf 13
typedef enum avm_memcell_t{	//ti tupou einai tin ora h timi pou apothikeuetai sto keli
	number_m = 0,
	string_m = 1,
	bool_m = 2,
	table_m = 3,
	userfunc_m = 4,
	libfunc_m = 5,
	nil_m = 6,
	undef_m = 7
}avm_memcell_t;


//phase 4
struct avm_table;
													//auta simbainoun at runtime
typedef struct avm_memcell{
	avm_memcell_t type;	//tipos timis tis stoibas
	union {
		double numVal;
		char* strVal;
		unsigned char boolVal;
		struct avm_table* tableVal;	//tipos gia tous pinakes
		unsigned funcVal;	//to index tou enterfunc instruction
		char* libfuncVal;	//to onoma tous
	}data;
}avm_memcell;

avm_memcell ax,bx,cx;
avm_memcell retval;
unsigned	top,topsp;

struct avm_table* avm_tablenew(void);
void avm_tabledestroy(struct avm_table* t);


avm_memcell* avm_tablegetem(struct avm_table* t,avm_memcell* key);  
void avm_tablesetelem(struct avm_table* t,avm_memcell* key, avm_memcell* value);


typedef struct avm_table_bucket{
	avm_memcell key;
	avm_memcell value;
	struct avm_table_bucket* next;
}avm_table_bucket;


typedef struct avm_table{	//dinamikoi sisxetistikoi pinakes
	unsigned refCounter;	//gia to garbage collection
	struct avm_table_bucket* strIndexed[AVM_TABLE_HASHSIZE];
	struct avm_table_bucket* numIndexed[AVM_TABLE_HASHSIZE];
	unsigned total;		//sunolikos arithos pou briskontai sto table --anti tis xrisis total metriti twn sunolikwn stoixeiwn mporoyn na xrisimopoiithoyn ksexwristes metablites total gia toys epimeroys hash tables
}avm_table;


avm_memcell stack[AVM_STACKSIZE];
//sel25 diaf 13


void avm_tableincrefcounter(avm_table* t);

void avm_tabledecrefcounter(avm_table* t);

void avm_memcellclear (avm_memcell* m);

double consts_getnumber(unsigned index);

char* consts_getstring(unsigned index);

char* libfuncs_getused(unsigned index);

typedef void (*execute_func_t)(instruction*);



extern void execute_assign(instruction*);

/***********************************************************************/
extern void execute_add(instruction*);

extern void execute_sub(instruction*);

extern void execute_mul(instruction*);

extern void execute_div(instruction*);

extern void execute_mod(instruction*);

/***********************************************************************/

extern void	execute_uminus(instruction*);
extern void execute_and(instruction*);
extern void execute_or(instruction*);
extern void execute_not(instruction*);

extern void execute_jeq(instruction*);

extern void execute_jne(instruction*);

extern void execute_jle(instruction*);

extern void execute_jge(instruction*);

extern void execute_jlt(instruction*);

extern void execute_jump(instruction*);

extern void execute_jgt(instruction*);

/***********************************************************************/

extern void execute_call(instruction*);

extern void execute_pusharg(instruction*);

extern void execute_funcenter(instruction*);

extern void execute_funcexit(instruction*);

/***********************************************************************/

extern void execute_newtable(instruction*);

extern void execute_tablegetelem(instruction*);

extern void execute_tablesetelem(instruction*);

/***********************************************************************/

extern void execute_nop(instruction*);

//diaf 15 sel 25

typedef double (*arithmetic_func_t)(double x, double y);

void execute_arithmetic(instruction* instr);

#define execute_add execute_arithmetic

#define execute_sub execute_arithmetic

#define execute_mul execute_arithmetic

#define execute_div execute_arithmetic

#define execute_mod execute_arithmetic

/************************************************************************************/

void execute_relational(instruction* instr);			//opws kanoume gia tous arithmetic kanoume k gia tous relational

#define execute_jne execute_relational

#define execute_jle execute_relational

#define execute_jge execute_relational

#define execute_jlt execute_relational

#define execute_jgt execute_relational

#define execute_nop execute_relational						//den eiami sigouros ti prepei na ginei me ton nop

/************************************************************************************/

extern double add_impl(double x, double y);

extern double sub_impl(double x, double y);

extern double mul_impl(double x,double y);

extern double div_impl(double x, double y);					

extern double mod_impl(double x, double y);	

execute_func_t executeFuncs[] = {
	execute_assign,
	execute_add,
	execute_sub,
	execute_mul,
	execute_div,
	execute_mod,

	execute_uminus,
	execute_and,
	execute_or,
	execute_not,
					
	execute_jeq,
	execute_jne,
	execute_jle,
	execute_jge,
	execute_jlt,
	execute_jump,
	execute_jgt,

	execute_call,
	execute_pusharg,
	0,
	0,
	execute_funcenter,
	execute_funcexit,
	execute_newtable,
	execute_tablegetelem,
	execute_tablesetelem,
	execute_nop
};


//diaf15 sel 16
typedef void(*memclear_func_t)(avm_memcell*);

extern void memclear_string(avm_memcell* m);

extern void memclear_table(avm_memcell* m);

memclear_func_t memclearFuncs[] = {
	0,				/*number*/
	memclear_string,
	0,				/*bool*/
	memclear_table,
	0,				/*userfunc*/
	0,				/*libfunc*/
	0,				/*nil*/
	0				/*undef*/
};

extern void avm_warning(char* format,...);
extern void avm_assign(avm_memcell* lv, avm_memcell* rv);

//diaf 15 sel 19
extern void avm_error(char* format,...);

extern char* avm_tostring(avm_memcell*);			//caller frees

extern void avm_calllibfunc (char* funcName);

extern void avm_callsaveenvironment(void);

//diaf 15 sel 21
extern userfunc* avm_getfuncinfo(unsigned address);

//diaf15 sel 22
typedef void(*library_func_t)(void);
//library_func_t avm_getlibraryfunc(char* id);					//typical hashing

extern void libfunc_print(void);

extern void libfunc_sqrt(void);

extern void libfunc_typeof(void);

extern void libfunc_cos(void);

extern void libfunc_sin(void);

library_func_t libFuncs[] = {
	libfunc_print,
	libfunc_sqrt,
	libfunc_typeof,
	libfunc_cos,
	libfunc_sin
};

//diaf 15 sel 23
void avm_registerlibfunc(char* id,library_func_t addr);

//diaf 15 sel 24
typedef char* (*tostring_func_t)(avm_memcell*);

extern char* number_tostring(avm_memcell*);

extern char* string_tostring(avm_memcell*);

extern char* bool_tostring(avm_memcell*);

extern char* table_tostring(avm_memcell*);

extern char* userfunc_tostring(avm_memcell*);

extern char* libfunc_tostring(avm_memcell*);

extern char* nil_tostring(avm_memcell*);

extern char* undef_tostring(avm_memcell*);

tostring_func_t tostringFuncs[] = {
	number_tostring,
	string_tostring,
	bool_tostring,
	table_tostring,
	userfunc_tostring,
	libfunc_tostring,
	nil_tostring,
	undef_tostring
};

						 


arithmetic_func_t arithmeticFuncs[] = {	//dispatcher for arithmetic functions
	add_impl,
	sub_impl,
	mul_impl,
	div_impl,
	mod_impl
};

typedef unsigned char(*relational_func_t)(double x, double y);

extern unsigned char jgt_impl(double x, double y);

extern unsigned char jlt_impl(double x, double y);

extern unsigned char jge_impl(double x, double y);

extern unsigned char jle_impl(double x , double y);

//diaf 15 sel 26
relational_func_t relationalFuncs[] = {
	jgt_impl,
	jlt_impl,
	jge_impl,
	jle_impl
};

typedef unsigned char(*tobool_func_t)(avm_memcell*);

extern unsigned char number_tobool(avm_memcell* m);

extern unsigned char string_tobool(avm_memcell* m);

extern unsigned char bool_tobool(avm_memcell* m);

extern unsigned char table_tobool(avm_memcell* m);

extern unsigned char userfunc_tobool(avm_memcell* m);

extern unsigned char libfunc_tobool(avm_memcell* m);

extern unsigned char nil_tobool(avm_memcell* m);

extern unsigned char undef_tobool(avm_memcell* m);

tobool_func_t toboolFuncs[] = {
	number_tobool,
	string_tobool,
	bool_tobool,
	table_tobool,
	userfunc_tobool,
	libfunc_tobool,
	nil_tobool,
	undef_tobool
};

avm_memcell	*	avm_tablegetelem(
	avm_table*	table,
	avm_memcell*	index
);

void avm_tablesetelem(
	avm_table*	table,
	avm_memcell* index,
	avm_memcell*	content
);

char* typeStrings[]={
"number",
"string",
"bool",
"table",
"userfunc",
"libfunc",
"nil",
"undef"
};