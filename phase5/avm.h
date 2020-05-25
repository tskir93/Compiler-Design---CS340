#include <stdio.h>
#include <stdlib.h>

#define AVM_STACKSIZE 4096
#define AVM_WIPEOUT(m)	memset(&(m),0,sizeof(m))	//set ola ta bytes me miden


#define AVM_TABLE_HASHSIZE 211

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
typedef enum avm_memcell_t{	//timi kathe keliou
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
		unsigned funcVal;
		char* libfuncVal;
	}data;
}avm_memcell;


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
	unsigned refCounter;
	struct avm_table_bucket* strIndexed[AVM_TABLE_HASHSIZE];
	struct avm_table_bucket* numIndexed[AVM_TABLE_HASHSIZE];
	unsigned total;		//sunolikos arithos pou briskontai sto table --anti tis xrisis total metriti twn sunolikwn stoixeiwn mporoyn na xrisimopoiithoyn ksexwristes metablites total gia toys epimeroys hash tables
}avm_table;


avm_memcell stack[AVM_STACKSIZE];
//sel25 diaf 13


void avm_tableincrefcounter(avm_table* t);

void avm_tabledecrefcounter(avm_table* t);

void avm_memcellclear (avm_memcell* m);

