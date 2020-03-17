all:
	bison -v --yacc --defines --output =parser.c parser.y
	flex --outfile=al.c al.l	
	gcc  -o final al.c functions.c parser.c


clean:
	rm al.c
	rm al
	rm parser.h
	rm parser.c
	rm *.output
