#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "tn.h"
#include "glob.h"

extern yylex();
extern int* yyleng;
extern char *yytext;

const char* reporterror() 
{
	switch (ERR)
	{
	case 0:
		return(yytext);
		break;
	case 1:
		return("Illegal Character");
		break;
	case 2:
		return("Illegal IDENT");
		break;
	case 3:
		return("TOO LONG IDENT");
		break;
	}

}

const char* lengthCheck() 
{
	if (yyleng <= 12) ERR = noerror;
	else ERR = overst;

	return(reporterror());
}

const char* classifyError() 
{
	if (strchr("0123456789", yytext[0]) != NULL) ERR = illid;
	else ERR = illsp;

	return(reporterror());
}


