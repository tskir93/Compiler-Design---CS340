#include "avm.h"
#define PI 3.14159265
instruction *instructions = (instruction*) 0;
unsigned int currinstruction = 0;
unsigned total_instructions = 0;

unsigned char executionFinished = 0;
unsigned pc = 0;
unsigned currLine = 0;
unsigned codeSize = 0;
instruction* code = (instruction*)0;
unsigned programVarOffset;
unsigned temp;
char result[30];

void readbinaryfile(){
	int i;
	FILE *ptr;

	ptr = fopen("binary.abc","rb");

	if(ptr==NULL){
		printf("Error file is empty\n");
	}

	fread(&magicnumber,sizeof(unsigned),1,ptr);						//diavazei to prwto stoixeio p einai to magic number kai to vazei sti thesi toy magicnumber
	if(magicnumber == 340200501){
		printf("Magic number is correct\n");
	}else{
		printf("Magic number is not correct\n");
	}

	fread(&programVarOffset,sizeof(unsigned),1,ptr);
	fread(&numSize,sizeof(unsigned),1,ptr);							
	fread(&stringSize,sizeof(unsigned),1,ptr);
	fread(&namedLibSize,sizeof(unsigned),1,ptr);
	fread(&userfuncSize,sizeof(unsigned),1,ptr);
	fread(&currinstruction,sizeof(unsigned),1,ptr);

	printf("Ta programvars einai %d\n",programVarOffset);
	printf("To num size einai = %d\n",numSize);
	printf("To stringSize einai = %d\n",stringSize);
	printf("To namedlib size einai = %d\n",namedLibSize);
	printf("To userfunc size einai = %d\n",userfuncSize);

	numConsts=(double *)malloc(numSize*sizeof(double));
	stringConsts=(char **)malloc(stringSize*sizeof(char*));
	namedLibfuncs = (char**)malloc(namedLibSize*sizeof(char*));
	userFuncs = (struct userfunc*)malloc(userfuncSize*sizeof(struct userfunc));
	stringlength = (int*)malloc(stringSize*sizeof(int));
	libfuncslength = (int*)malloc(namedLibSize*sizeof(int));
	userfuncslength = (int*)malloc(namedLibSize*sizeof(int));
	instructions = (instruction*)malloc(currinstruction*sizeof(instruction));

	for(i=0;i<numSize;i++){
		fread(&numConsts[i],sizeof(double),1,ptr);
		printf("to numconst exei mesa to -> %f \n",numConsts[i]);
	}

	for(i=0;i<stringSize;i++){
		fread(&stringlength[i],sizeof(int),1,ptr);					//pernaw ton pinaka p periexei to length kathe string gia na ton exw otan tha desmevw xwro sto fopen binary
	}

	for(i=0;i<namedLibSize;i++){
		fread(&libfuncslength[i],sizeof(int),1,ptr);				//pernav ton pinaka p periexei to length kathe libfunc gia na ton exw otan tha krataw xwro stin fopen 
	}


	for(i=0;i<stringSize;i++){
		stringConsts[i] = (char *) malloc (stringlength[i] * sizeof(char));				//kratame xwro analoga to megethos toy string gia na t perasoyme ston pinaka meta
		fread(stringConsts[i],stringlength[i]*sizeof(char),sizeof(char),ptr);			//diavazoume ena ena ta string kai t apothikevoume ston pinaka twn strings
	}
		for(i=0;i<stringSize;i++){
				printf("to strinconst[%d] = %s \n",i,stringConsts[i]);			
		}
//	}

	for(i=0;i<namedLibSize;i++){
		namedLibfuncs[i] = (char *) malloc (libfuncslength[i] * sizeof(char));				//kratame xwro analoga to megethos toy string gia na t perasoyme ston pinaka
		fread(namedLibfuncs[i],libfuncslength[i]*sizeof(char),sizeof(char),ptr);			//diavazoume apo to binary ena ena t string kai t apothikevoume ston pinaka
	}
		for(i=0;i<namedLibSize;i++){
				printf("to namedLibfuncs[%d] = %s \n",i,namedLibfuncs[i]);
		}
	//}

	for(i=0;i<userfuncSize;i++){
		fread(&userfuncslength[i],sizeof(int),1,ptr);				//pernav ton pinaka p periexei to length kathe libfunc gia na ton exw otan tha krataw xwro stin fopen 
	}	
		
	for(i=0;i<userfuncSize;i++){
		fread(&userFuncs[i].taddress,sizeof(userFuncs),1,ptr);
		fread(&userFuncs[i].localSize,sizeof(userFuncs),1,ptr);
		userFuncs[i].id = (char*)malloc(userfuncslength[i]);
		fread(userFuncs[i].id,userfuncslength[i]*sizeof(char),1,ptr);
	}

	for(i=0;i<userfuncSize;i++){
				printf("to userfuncs[%d] = %s \n",i,userFuncs[i].id);
		}

	for(i=0;i<currinstruction;i++){
		fread(&instructions[i],sizeof(instruction),1,ptr);
		printf("instr[%d]->opcode -> %d\n",i,instructions[i].opcode);
	}

	printf("Exoyme %d instructions\n",currinstruction);
	
}

static void avm_initstack(void){	//arxikopoihsh
unsigned i=0; 
	for(i=0; i<AVM_STACKSIZE;++i){
		(AVM_WIPEOUT(stack[i]));
		stack[i].type=undef_m;	//kathe keli tis stoibas einai arxika undef
	}
}

void avm_tableincrefcounter(avm_table* t){	//auksanei ton refcounter enos pinaka
	++t->refCounter;
}

void avm_tabledecrefcounter(avm_table * t){
	assert(t->refCounter>0);
	if(!--t->refCounter)
	avm_tabledestroy(t);
}

void avm_tablebucketsinit(avm_table_bucket ** p){
	unsigned i=0;
	for(i=0;i<AVM_TABLE_HASHSIZE;i++)
	p[i]=(avm_table_bucket *)0; //cast ton type pointer se zero(kano p=NULL)
}

avm_table * avm_tablenew(void){
	avm_table * t=(avm_table *)malloc(sizeof(avm_table));
	AVM_WIPEOUT(*t);	

	t->refCounter=t->total=0;
	avm_tablebucketsinit(t->numIndexed);
	avm_tablebucketsinit(t->strIndexed);

	return t;
}
void avm_tablebucketsdestroy(avm_table_bucket ** p){
	unsigned i=0;
	avm_table_bucket * b;
	for(i=0; i<AVM_TABLE_HASHSIZE; ++i,++p){	//diatrexei ola ta bucket list
		for(b=* p;b;){	//to p kinete se kathe bucket list sta string-values 
			avm_table_bucket * del=b;
			b=b->next;
			avm_memcellclear(&del->key);
			avm_memcellclear(&del->value);
			free(del);
		}	
		p[i]=(avm_table_bucket *)0;
	}

}
void avm_tabledestroy(avm_table * t){
avm_tablebucketsdestroy(t->strIndexed);
avm_tablebucketsdestroy(t->numIndexed);
free(t);
}

double consts_getnumber(unsigned index){					//sunartisi p epistrefei to number p einai sto index toy pinaka me ta numbers
	if(numConsts!=NULL){
		//printf("to index einai %d\n",index);
		//printf("to numConsts[%d] einai %f\n",index,numConsts[index]);
		return numConsts[index];
	}
}
char* consts_getstring(unsigned index){
	if(stringConsts!=NULL){
		//printf("to index einai %d\n",index);
		//printf("to numConsts[%d] einai %f\n",index,numConsts[index]);
		return stringConsts[index];
	}
}
char* libfuncs_getused(unsigned index){
	if(namedLibfuncs!=NULL){
		//printf("mpainei stin libfuncs_getused\n");
		return namedLibfuncs[index];
	}
}

avm_memcell* avm_translate_operand(vmarg* arg,avm_memcell *reg){
	//printf("mpika sthn translate\n");
	//printf("mpainei edw\n");
	switch (arg->type){

		/*Variables*/
		case global_a:/* 	printf("ekso apo thn translate1 kai %d kai to val %d \n",AVM_STACKSIZE-1-arg->val,arg->val);*/	return &stack[AVM_STACKSIZE -1 -arg->val];
		case local_a: 	/*printf("ekso apo thn translate2 \n");*/	return &stack[topsp-arg->val];
		case formal_a:	/*printf("ekso apo thn translate3 \n");*/	return &stack[topsp+AVM_STACKENV_SIZE+1+arg->val];

		case retval_a:	/*printf("ekso apo thn translate4 \n");*/	return &retval;

		case number_a:{
			//printf("mpainei sto number\n");
			reg->type = number_m;
			reg->data.numVal = consts_getnumber(arg->val);
			//printf(" to reg einai %f\n",reg->data.numVal);
			//printf("to noymero p pernei eiani to :%f\n",consts_getnumber(arg->val));
			//printf("ekso apo thn translate5 \n");
			return reg;
		}

		case string_a:{
			//printf("mpika sthn translate tou string\n");
			reg->type = string_m;
			reg->data.strVal = strdup(consts_getstring(arg->val));
			//printf("ekso apo thn translate6 me string  %s \n",reg->data.strVal);
			return reg;
		}

		case bool_a:{
			reg->type = bool_m;
			reg->data.boolVal = arg->val;
			//printf("ekso apo thn translate7 \n");
			return reg;
		}

		case nil_a:	{
			reg->type = nil_m;
			//printf("ekso apo thn translate8 \n");
			return reg;
		}

		case userfunc_a:{
			reg->type = userfunc_m;
			reg->data.funcVal = arg->val;		//address already stored dioti gia tis sunartiseis poy orizei o xristis gnwrizoume oti i dieuthinsi apothikevetai apeutheias stin timi toy orismatos
			//printf("ekso apo thn translate9 \n");
			return reg;
		}

		case libfunc_a:{
			reg->type = libfunc_m;
			reg->data.libfuncVal = libfuncs_getused(arg->val);
			return reg;
		}


		default: /*printf("ekso apo thn translate10 \n");*/ assert(0);
				//reg->type = undef_m;				//tskir
				//return reg;


	}
	
}

//diaf 15 sel 14
void execute_cycle(void){
	unsigned i;
	//printf("pc is %d\n",pc);
	if(executionFinished){

		return;
	}else{
		if( pc == AVM_ENDING_PC){
			executionFinished = 1;
			//printf("mpainei sto if tis execute\n");
			return;
			
		}else{
			//printf("mpainei sto else tis execute\n");
			assert(pc < AVM_ENDING_PC);
			//i = code + pc ;
			//printf("i ============================> %d\n",i);
			instruction* instr = &instructions[pc];
			//printf("code + pc = %d + %d\n",code,pc);
			//printf("pc-> %d\n",pc);
			
			//printf("AVM_MAX_INSTRUCTIONS->%d\n",AVM_MAX_INSTRUCTIONS);
			//printf("instr->opcode = %d\n",instr->opcode);
			assert(
				instr->opcode >=0 &&
				instr->opcode <= AVM_MAX_INSTRUCTIONS
			);
			//printf("kanei tin assert\n");
			if(instr->srcLine){
				currLine = instr->srcLine;
			}
			//printf("ok\n");
			unsigned oldPC = pc;
			//printf("instr->opcode ***********************= %d\n",instructions[pc].opcode);
			(*executeFuncs[instructions[pc].opcode])(instr);						//tskir
			//(*executeFuncs[instr->opcode])(instr);
			temp++;
			if(pc==oldPC){							//to pc tha allazei logw twn entolwn jump call kai epistrofis apo klisi alliws pame stin epomeni entoli
				++pc;
			}
		}
	}
	//printf("vgainei apo cycle\n");
}

//diaf 15 sel 16 kanoume kai extern sto .h
void memclear_string(avm_memcell* m){
	assert(m->data.strVal);
	free(m->data.strVal);
}

void memclear_table(avm_memcell* m){
	assert(m->data.tableVal);
	avm_tabledecrefcounter(m->data.tableVal);
}

void avm_memcellclear(avm_memcell *m){
	//printf("mpainei stin memclear\n");
	if(m->type != undef_m){
		//printf("mpainei stin m->type!=undef_m\n");
		//printf("to m->typeeinai =>>>%s\n",avm_tostring(m));
		memclear_func_t f = memclearFuncs[m->type];
		if(f){
			(*f)(m);
		}
		m->type = undef_m;
	}
}

//diaf 15 sel 17
//theloyn sumplirwma
void avm_warning(char* format,...){
	printf("\033[0;31m");
	printf("%s\n",format);
	printf("\033[0m");
}

//diaf 15 sel 17	
//+diaf 15 sel 18
void avm_assign(avm_memcell* lv, avm_memcell* rv){
	if(lv == rv){			//same cells? destructive to assign
		return;
	}

	if(lv->type == table_m &&						//same tables? no need to assign
		rv->type == table_m &&
		lv->data.tableVal == rv->data.tableVal){
		return;
	}

	if(rv->type == undef_m){						//from undef r-value? warning
		avm_warning("assigning from 'undef' content!");
	}
	//printf("EIMAI MESA STIN ASSIGN\n");
	avm_memcellclear(lv);		//clear old cell contents
	//printf("tralala kai lv %f kai rv %f \n",lv->data.numVal,rv->data.numVal);
	memcpy(lv,rv,sizeof(avm_memcell));			
	//printf("tralala1 kai lv %f kai rv %f \n",lv->data.numVal,rv->data.numVal);
	/*Now take care of copied values or reference counting*/

	if(lv->type == string_m){							//kathe keli exei to diko tou dinamiko string enw an ekxwrithei pinakas frontizei na toy aukisei to reference counter
	//printf("mpika edo kai eimai kala me %s kai %s \n",lv->data.strVal,rv->data.strVal);
		lv->data.strVal = strdup(rv->data.strVal);
	}else{
		if(lv->type == table_m){
			avm_tableincrefcounter(lv->data.tableVal);
		}
	}

}

void execute_assign(instruction* instr){
	//printf("execute_assign\n");
	avm_memcell* lv = avm_translate_operand(&instr->result,(avm_memcell*)0);
	
//printf("meta tin translate lv tis assign\n");
	
	//printf("kanei tin lv\n");
	avm_memcell* rv = avm_translate_operand(&instr->arg1,&ax);
	//printf("meta tin translate tis rv assign\n");

	
	//printf("kanei tin rv**********************\n");
	
	//assert(lv && ( (&stack[AVM_STACKSIZE-1] >= lv) && (lv > &stack[top]) || (lv==&retval)));
	//printf("kanei to prwto assertion\n");
	assert(rv);
	
	avm_assign(lv,rv);
	//printf("meta to rv einai %f kai to lv ths assign einai %f\n\n",rv->data.numVal, lv->data.numVal);
}


//diaf 15 sel 19 - >sumplirwma
void avm_error(char* format,...){
	printf("\033[0;31m");
	printf("%s\n",format);
	printf("\033[0m");
}


//diaf 15 sel 24
char* avm_tostring(avm_memcell* m){					//caller frees
	//printf("******mpika sthn avm_tostring");
	assert(m->type >= 0 && m->type <= undef_m);
	return (*tostringFuncs[m->type])(m);
}			
//diaf 15 sel 20
unsigned totalActuals = 0;


library_func_t avm_getlibraryfunc(char* id){			//sunartisi p epistrefei ti lib func an uparxei ston pinaka twn library functions
	unsigned i;		
	//printf("mpainei stin avm_getlibraryfunc\n");
								
	if(strcmp("print",id)==0){					//an den tin vrei epistrefei null
		//printf("mpainei stin strcmp\n");
		return libFuncs[0];
	}
	if(strcmp("sqrt",id)==0){
		return libFuncs[1];
	}
	if(strcmp("typeof",id)==0){
		return libFuncs[2];
	}
	if(strcmp("cos",id)==0){
		return libFuncs[3];
	}
	if(strcmp("sin",id)==0){
		return libFuncs[4];
	}
	printf("\033[0;31m");
	printf("This libfunc is not included in namedLibfuncs table\n");
	printf("\033[0m");
	return NULL;
}


//diaf 15 sel 22
void avm_calllibfunc (char* id){
	//printf("mpainei stin avm_callibfunc\n");
	library_func_t f = avm_getlibraryfunc(id);
	if(!f){
		avm_error("Unsupported lib func '%s' called!",id);
		executionFinished = 1;
	}else{
		//notice that enter function and exit function are called manually
		//printf("mpainei edw stin call libfunc\n");
		topsp = top;			//enter function seq. No stack locals.
		totalActuals = 0;
		(*f)();					//call libfunction
		if(!executionFinished){				//an error may naturally occur inside
			execute_funcexit((instruction*)0);		//return sequence
		}
	}
}


void avm_dec_top(void){						//prosexoume kai elegxoume panta gia to endexomeno enos stack overflow
	if(!top){
		avm_error("ERROR - Stack overflow!");
		executionFinished = 1;
	}else{
		--top;
	}
}

void execute_uminus(instruction* instr){}

void execute_and(instruction* instr){}

void execute_or(instruction* instr){}

void execute_not(instruction* instr){}

void execute_jump(instruction* instr){}

void avm_push_envvalue(unsigned val){
	stack[top].type  = number_m;
	stack[top].data.numVal = val;
	avm_dec_top();
}

// h akoloythia klisis oloklirwnetai me thn apothikeusi toy perivalontos
//prosoxi stin arithmitiki twn apothikeumenn timwn -> na ginei elegxos xeirokinita
void avm_callsaveenvironment(void){
	avm_push_envvalue(totalActuals);
	avm_push_envvalue(pc+1);
	avm_push_envvalue(top + totalActuals + 2);
	avm_push_envvalue(topsp);
}


void execute_call(instruction* instr){
	//printf("mpanei stin executecall ****************************\n");
	avm_memcell *func = avm_translate_operand(&instr->arg1,&ax);				//tskir apo &instr->result
	assert(func);
	//printf("check1\n");
	avm_callsaveenvironment();
	//printf("check2\n");
	switch(func->type){
		//printf("check3\n");
		case userfunc_m: 	{						//kseroume ta nomima oria dieuthinsewn entolwn alla episis kseroume oti h prwti entoli synartisis einai h funcenter				
			pc = func->data.funcVal;
			assert(pc < AVM_ENDING_PC);
			assert(code[pc].opcode == funcenter_v);
			break;
		}

		case string_m: 		{
			//printf("einai string\n");
			//printf("***********************************mpainei stin call tou string me string %s\n",func->data.strVal);					
			avm_calllibfunc(func->data.strVal);
			break;
		}

		case libfunc_m :	{						//mporoyme na kaloyme libfuncs kai san strings
			//printf("mpainei sto libfunc_m ->execute_cal\n");
			avm_calllibfunc(func->data.libfuncVal);
			//printf("ok\n");
			break;
		}

		default:			{						//otidipote allo einai runtime error kai simatodotei mazi me ena minima ton termatismo tis ektelesis
			char* s = avm_tostring(func);
			avm_error("ERROR - Call: cannot bind '%s' to function!",s);
			free(s);
			executionFinished = 1;															
		}
	}
	//printf("vgainei apo executecall\n");
}





//diaf 15 sel 21
userfunc* avm_getfuncinfo(unsigned address){}

//diaf 15 sel 21
void execute_funcenter(instruction* instr){
	avm_memcell* func = avm_translate_operand(&instr->result,&ax);
	assert(func);
	assert(pc == func->data.funcVal);			//func address should match PC.

	//callee actions here.
	totalActuals = 0;
	userfunc* funcInfo = avm_getfuncinfo(pc);
	topsp = top;
	top = top - funcInfo->localSize;
}

unsigned avm_get_envvalue(unsigned i){
	//stack[i].type = number_m;
	//assert(stack[i].type = number_m);							//sto x=3;print(x); kanei failed to assert auto 				//tskir 2/6 se sxolia
	unsigned val =(unsigned)stack[i].data.numVal;
	assert(stack[i].data.numVal == ((double)val));
	return val;
}

void execute_funcexit(instruction* unused){
	unsigned oldTop = top;
	top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);					//epistrofi toy proigoumeni perivallontos kai epistrofi apo tin klisi
	pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
	topsp = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);

	while(++oldTop <= top)			//intentionally ignoring first
		avm_memcellclear(&stack[oldTop]);				//garbage collection ->katharismos toy activation record
}

//diaf15 sel 23
unsigned avm_totalactuals(void){
	//printf("topsp = %d\n",topsp);
	//printf("AVM_NUMACTUALS_OFFSET = %d\n");
	return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactual(unsigned i){
	assert(i < avm_totalactuals());
	return &stack[topsp + AVM_STACKENV_SIZE +1 +i];
}


//diaf 15 sel 23
//with the following every library function is manually added in the VM library function resolution map.
void avm_registerlibfunc(char* id,library_func_t addr){
	//printf("mpainei stin avm_registerlibfunc gia tin sqrt\n");
	////printf("mpainei stin avm_registerlibfunc \n");
	//printf("to instr->opcode prin mpei eiani %d\n",instructions[0].opcode);
	if(strcmp("print",id)==0){
		libFuncs[0] =  addr;
		//printf("mpainei stin avm_registerlibfunc\n");
		//printf("to instr->opcode eiani stin print  %d\n",instructions[0].opcode);
	}
	if(strcmp("sqrt",id)==0){
		printf("mpainei stin avm_registerlibfunc gia tin sqrt\n");
		printf("to instr->opcode eiani %d\n",instructions[0].opcode);
		//libFuncs[1] = addr;
	}

	printf("to instr->opcode eiani %d\n",instructions[0].opcode);
}

//implementation of the libfunc 'print'
//it displayes every argument at the console
void libfunc_print(void){
	//printf("mpainei stin libfuncprint\n");

	unsigned n = avm_totalactuals();
	unsigned i;
	//printf("mpainei sto libfunc_print\n");
	for(i=0;i<n;++i){
		char* s = avm_tostring(avm_getactual(i));			//pairnei kathe fora to antistoixo argument apo tin print px an einai print(x,y) pairnei prwta to 0 p eiani t x k meta to 1 ->y
		//printf("to string einai %s\n",s);
		puts("\033[0;33m");
		puts(s);
		puts("\033[0m");
		//free(s);
	}
}

void libfunc_sqrt(void){
	//printf("mpainei stin sqrt\n");
	unsigned n = avm_totalactuals();				//prepei na dexete ena orisma
	avm_memcellclear(&retval);						//opws kai stin type of kanoyme to memclear stin retval
	if(n!=1){
		avm_error("ERROR - Sqrt function could have only one argument!");
		executionFinished = 1;						//kathe fora meta to error teleiwnei to to execution
	}else{
		retval.type = number_m;
		retval.data.numVal = (avm_getactual(0)->data.numVal) * (avm_getactual(0)->data.numVal);			//dinw tipo number k epistrefo to tetragwno toy avm_getactual 0
	}
}

void libfunc_cos(void){
	//printf("mpainei stin cos\n");
	double temp ;
	unsigned n = avm_totalactuals();				//prepei na dexete ena orisma
	avm_memcellclear(&retval);						//opws kai stin type of kanoyme to memclear stin retval
	if(n!=1){
		avm_error("ERROR - Cos function could have only one argument!");
		executionFinished = 1;						//kathe fora meta to error teleiwnei to to execution
	}else{
		retval.type = number_m;
		temp = PI / 180;
		temp = (avm_getactual(0)->data.numVal) * temp;
		retval.data.numVal = cos(temp);			//dinw tipo number k epistrefo to tetragwno toy avm_getactual 0
	}
}

void libfunc_sin(void){
	//printf("mpainei stin sin\n");
	double temp ;
	unsigned n = avm_totalactuals();				//prepei na dexete ena orisma
	avm_memcellclear(&retval);						//opws kai stin type of kanoyme to memclear stin retval
	if(n!=1){
		avm_error("ERROR - Sin function could have only one argument!");
		executionFinished = 1;						//kathe fora meta to error teleiwnei to to execution
	}else{
		retval.type = number_m;
		temp = PI / 180;
		temp = (avm_getactual(0)->data.numVal) * temp;
		retval.data.numVal = sin(temp);			//dinw tipo number k epistrefo to tetragwno toy avm_getactual 0
	}
}


//diaf 15 sel 24
void execute_pusharg(instruction * instr){
	//printf("mpainei stin execute pusharg\n");
	avm_memcell* arg = avm_translate_operand(&instr->arg1,&ax);
	assert(arg);
	
	//this is actually stack[top] = arg, but we have to use avm_assign
	avm_assign(&stack[top],arg);
	++totalActuals;
	avm_dec_top();
}

//diaf 15 sel 24
char* number_tostring(avm_memcell* m){
	sprintf(result,"%f",m->data.numVal);
	//printf("The numberto string is -> %s",result);
	return result;
}

char* string_tostring(avm_memcell* m){	//epistrefei to string
	return m->data.strVal;
}

char* bool_tostring(avm_memcell* m){
	char string[6];
	switch (m->data.boolVal){
		case 0:{
			return "true";
		}
		case 1:{
			return "false";
		}
		
	}
}

char* table_tostring(avm_memcell* m){}

char* userfunc_tostring(avm_memcell* m){}

char* libfunc_tostring(avm_memcell* m){}

char* nil_tostring(avm_memcell* m){}

char* undef_tostring(avm_memcell* m){}


//diaf 15 sel 25		
double add_impl(double x, double y){return x+y;}

double sub_impl(double x, double y){return x-y;}

double mul_impl(double x,double y){return x*y;}

double div_impl(double x, double y){
		if (y!=0){
			return x/y;
		}else{
			avm_error("ERROR - Devide with zero!");
		}
}					//Error check???

double mod_impl(double x, double y){
	return ((unsigned)x) % ((unsigned)y);							//Error check??? 
}

//diaf 15 sel 25
void execute_arithmetic(instruction* instr){
	avm_memcell* lv = avm_translate_operand(&instr->result , (avm_memcell*)0);
	//printf("*****egine h to ths lv\n");
	avm_memcell* rv1 = avm_translate_operand(&instr->arg1 , &bx);
	//printf("metato rv1 to rv1 einai %f\n",rv1->data.numVal);
	avm_memcell* rv2 = avm_translate_operand(&instr->arg2 , &ax);
	//printf("metato rv2 to rv1 einai %f kai to rv2 einai %f\n",rv1->data.numVal, rv2->data.numVal);
	assert(lv && (&stack[AVM_STACKSIZE-1] >= lv) && (lv> &stack[top]) || lv==&retval);	//added by george
	assert(rv1 && rv2);

	if(rv1->type != number_m || rv2->type !=number_m){
		avm_error("ERROR - Not a number in arithmetic!");
		executionFinished = 1;
	}else{
		//printf("mpainei stin execute_arithmetic - number type is ok\n");
		arithmetic_func_t op = arithmeticFuncs[instr->opcode -add_v];
		avm_memcellclear(lv);
		lv->type = number_m;
		//printf("to lv einai %f\n",lv->data.numVal);
		//printf("to rv1 einai %f kai to rv2 einai %f",rv1->data.numVal, rv2->data.numVal);
		lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
		//printf("to lv einai %f\n",lv->data.numVal);
	}

}

void execute_relational(instruction* instr){}

unsigned char jgt_impl(double x, double y){return x>y;}

unsigned char jlt_impl(double x, double y){return x<y;}

unsigned char jge_impl(double x, double y){return x>=y;}

unsigned char jle_impl(double x , double y){return x<=y;}



//diaf15 sel 28
unsigned char number_tobool(avm_memcell* m){return m->data.numVal !=0;}

unsigned char string_tobool(avm_memcell* m){return m->data.strVal[0] != 0;}

unsigned char bool_tobool(avm_memcell* m){return m->data.boolVal;}

unsigned char table_tobool(avm_memcell* m){return 1;}

unsigned char userfunc_tobool(avm_memcell* m){return 1;}

unsigned char libfunc_tobool(avm_memcell* m){return 1;}

unsigned char nil_tobool(avm_memcell* m){return 0;}

unsigned char undef_tobool(avm_memcell* m){return 0;}	//{assert(0;return 0;)}


//diaf15 sel 28
unsigned char avm_tobool(avm_memcell *m){
	assert(m->type>=0 && m->type < undef_m);
	return (*toboolFuncs[m->type])(m);
}

void execute_jeq(instruction* instr){
	assert(instr->result.type == label_a);

	avm_memcell* rv1=avm_translate_operand(&instr->arg1, &ax);
	avm_memcell* rv2=avm_translate_operand(&instr->arg2, &bx);

	unsigned char result = 0;

	if(rv1->type == undef_m || rv2->type == undef_m)
	avm_error("ERROR - 'undef' involved in equality!");

	else if(rv1->type == nil_m || rv2->type == nil_m)
	result = rv1->type == nil_m && rv2->type == nil_m;
	
	else if(rv1->type == bool_m || rv2->type == bool_m)
	result=(avm_tobool(rv1) == avm_tobool(rv2));

	else if(rv1->type != rv2->type)
	avm_error("ERROR - %s == %s is illegal!",typeStrings[rv1->type],typeStrings[rv2->type]);

	else{
		//equality check with dispathcing,not finished
	}

	if(!executionFinished && result)
	pc = instr->result.val;
}

void libfunc_typeof(void){
	unsigned n=avm_totalactuals();
	if(n!=1)
		avm_error("ERROR - Only one argument expected in 'typeof'!");
		else{
			//thats how a library function returns a result
			//it has to only set the 'retval' register!
			avm_memcellclear(&retval);
			retval.type = string_m;
			retval.data.strVal=strdup(typeStrings[avm_getactual(0)->type]);
		}
	
}



void execute_newtable(instruction * instr){
	avm_memcell * lv=avm_translate_operand(&instr->result,(avm_memcell*)0);
	assert(lv && (	&stack[AVM_STACKSIZE-1] >= lv &&	lv>&stack[top]	||	lv==&retval));	//added by george

	avm_memcellclear(lv);
	lv->type=table_m;
	lv->data.tableVal=avm_tablenew();
	avm_tableincrefcounter(lv->data.tableVal);
}

avm_memcell	*	avm_tablegetelem(avm_table*	table,avm_memcell*	index){}

void execute_tablegetelem(instruction * instr){
	avm_memcell* lv=avm_translate_operand(&instr->result,(avm_memcell*)0);
	avm_memcell* t=avm_translate_operand(&instr->arg1,(avm_memcell*)0);
	avm_memcell* i=avm_translate_operand(&instr->arg2,&ax);

	assert(lv	&&	(&stack[AVM_STACKSIZE-1]	>=	lv	&&	lv>&stack[top]	||	lv==&retval));
	assert(t	&&	&stack[AVM_STACKSIZE-1]	>=t	&&	t>&stack[top]);
	assert(i);

	avm_memcellclear(lv);
	lv->type;

	if(t->type!=table_m){
		avm_error("ERROR - illegal use of type	%s as table!",typeStrings[t->type],i);

	}
	else{
		avm_memcell* content=avm_tablegetelem(t->data.tableVal,i);
		if(content)
		avm_assign(lv,content);
		else{
			char* ts=avm_tostring(t);
			char* is=avm_tostring(i);
			avm_warning("WARNING - %s[%s] not found!",ts,is);
			free(ts);
			free(is);
		}
	}
	
}

void avm_tablesetelem(avm_table*	table,avm_memcell* index,avm_memcell*	content){}

void execute_tablesetelem(instruction* instr){
	avm_memcell* t=avm_translate_operand(&instr->result,(avm_memcell*)0);
	avm_memcell* i=avm_translate_operand(&instr->arg1,(avm_memcell*)0);
	avm_memcell* c=avm_translate_operand(&instr->arg2,&ax);

	assert(t &&	&stack[AVM_STACKSIZE-1] >= t && t>&stack[top]);
	assert(i && c);

	if(t->type != table_m)
	avm_error("ERROR - illegal use of type	%s as table!",typeStrings[t->type]);
	else	
	avm_tablesetelem(t->data.tableVal,i,c);

}

void avm_initialize(void){
	avm_initstack();
	top = AVM_STACKSIZE -1 -programVarOffset;
	topsp = top;
	//avm_registerlibfunc("print",libfunc_print);			//eixe provlima me ton opcode opote to allaksa
	//avm_registerlibfunc("sqrt",libfunc_sqrt);				//prepei na tis kanoun registerlibfuncs gia na tis valoume ston pinaka libFuncs apo opou tha kalestoyn
	//avm_registerlibfunc("typeof",libfunc_typeof);

	//same for all the rest library functions,not finished
}

void libfunc_totalarguments(void){
	//get topsp of previous activation record

	unsigned p_topsp=avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
	avm_memcellclear(&retval);

	if(!p_topsp)//if 0,no previous actiovation record
	avm_error("ERROR - 'totalarguments' called outside a function!");
	retval.type=nil_m;
}

void print_tables(void){
	int i;
	printf("\033[0;36m");
	printf("***********CONSTNUMS***********\n");
	printf("Constnums total = %d\n\n",numSize );
	printf("\033[0m");
	for(i=0;i<numSize;i++){
		printf("\033[0;33m");
		printf("%d: %15f \n",i,numConsts[i]);
		printf("\033[0m");
	}
	printf("\n");
	printf("\033[0;36m");
	printf("***********STRINGS***********\n");
	printf("Strings total = %d\n\n",stringSize );
	printf("\033[0m");
	for(i=0;i<stringSize;i++){
		printf("\033[0;33m");
		printf("%d: %15s \n",i,stringConsts[i]);
		printf("\033[0m");
	}
	printf("\n");
	printf("\033[0;36m");
	printf("***********LIBFUNCS***********\n");
	printf("Libfuncs total = %d\n\n",namedLibSize );
	printf("\033[0m");
	for(i=0;i<namedLibSize;i++){
		printf("\033[0;33m");
		printf("%d: %15s \n",i,namedLibfuncs[i]);
		printf("\033[0m");
	}
	printf("\n");
	printf("\033[0;36m");
	printf("***********USERFUNCS***********\n");
	printf("Userfuncs total = %d\n\n",userfuncSize );
	printf("\033[0m");
	for(i=0;i<userfuncSize;i++){
		printf("\033[0;33m");
		printf("%d: %15s \n",i,userFuncs[i].id);
		printf("\033[0m");
	}
	printf("\n");
}
int main(int argc, char **argv) {
		int x,i;
		temp=0;

		readbinaryfile();
		avm_initialize();
		print_tables();
		printf("\033[1;31m");
		printf("\n\n\n***********Execution result***********\n");
		printf("\033[0m");		
		while(executionFinished!=1){
			execute_cycle();
			//printf("mpainei stin executecycle\n");
		}
		//libfunc_print();
		return 0;
}