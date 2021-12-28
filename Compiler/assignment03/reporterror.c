/*
*	reporterror - classify error & reporterror
*	programmer - À¯È¿¹Î
*	date - 21.04.22
*/

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "tn.h"
#include "glob.h"

extern yylex();
extern int* yyleng;
extern char* yytext;

yyerror(s) char* s; {}

// reporterror for each error type
const void printError(ERRORtypes err)
{
	switch (err)
	{
	case 0: //no error
		break;
	case 1: //Illegal Symbol error
		printf("%d\t<Scanner Error> \t== Illegal Symbol == \n", cLine);
		cErrors++;
		break;
	case 2:	//Illegal Ident error
		printf("%d\t<Scanner Error> \t== Illegal ident == \n", cLine);
		cErrors++;
		break;
	case 3:	//overst error
		printf("%d\t<Scanner Error> \t== Long ident == \n", cLine);
		cErrors++;
		break;
	case 4:	//no semicolon error
		printf("%d\t<Parser Error> \t\t== No semicolon == \n", cLine - 1);
		cErrors++;
		break;
	case 5:	//no close error
		printf("%d\t<Parser Error> \t\t== No close == \n", cLine);
		cErrors++;
		break;
	}
}


//  length check about each identifier
const int lengthCheck()
{
	if (yyleng <= 12)  return 1;
	else  return 0;
}

const void classifyError()
{
	printf("wlsd");
	if (strchr("0123456789", yytext[0]) != NULL) printError(illid);	// start with digit
	else printError(illsp);	// use not allowed seperator
}

