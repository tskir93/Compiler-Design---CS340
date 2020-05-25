#include "avm.h"

instruction *instructions = (instruction*) 0;
unsigned int currinstruction = 0;
unsigned total_instructions = 0;

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

	fread(&numSize,sizeof(unsigned),1,ptr);							
	fread(&stringSize,sizeof(unsigned),1,ptr);
	fread(&namedLibSize,sizeof(unsigned),1,ptr);
	fread(&userfuncSize,sizeof(unsigned),1,ptr);
	fread(&currinstruction,sizeof(unsigned),1,ptr);

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
				printf("to strinconst exei mesa to -> %s \n",stringConsts[i]);			
		}
//	}

	for(i=0;i<namedLibSize;i++){
		namedLibfuncs[i] = (char *) malloc (libfuncslength[i] * sizeof(char));				//kratame xwro analoga to megethos toy string gia na t perasoyme ston pinaka
		fread(namedLibfuncs[i],libfuncslength[i]*sizeof(char),sizeof(char),ptr);			//diavazoume apo to binary ena ena t string kai t apothikevoume ston pinaka
	}
		for(i=0;i<namedLibSize;i++){
				printf("to namedLibfuncs exei mesa to -> %s \n",namedLibfuncs[i]);
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
				printf("to userfuncs exei mesa to -> %s \n",userFuncs[i].id);
		}

	for(i=0;i<currinstruction;i++){
		fread(&instructions[i],sizeof(instruction),1,ptr);
	}

	printf("exoyme %d instructions\n",currinstruction);
}


int main(int argc, char **argv) {
	int x;

		readbinaryfile();
		return 0;
}