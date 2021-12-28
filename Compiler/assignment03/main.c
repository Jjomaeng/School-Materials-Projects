#include <stdio.h>
#include "glob.h"

extern int yyparse();
extern void printHT();

void main()
{
	printf("========================ERROR========================\n");
	cLine = 1;
	cErrors = 0;
	yyparse();
	printf("=====================================================\n");
	printf("%d error(s) detected\n\n", cErrors);

	printHT();
}
