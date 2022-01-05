%{
/* scanner.l - lexical analyze for the MiniC
* programmer - ��ȿ��, ��ȿ��
* date - 20/04/2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"

extern lengthCheck();
extern SymbolTable();
extern printError();
extern yyerror(char *s);
extern classifyError();

idx = 0;
nextid = 0;
hashcode, found, sameid;

%}
A [A-Za-z_]
D [0-9]
%%
"const"				return(TCONST);
"else"				return(TELSE);
"if"				return(TIF);
"int"				return(TINT);
"float"				return(TFLOAT);
"return"				return(TRETURN);
"void"				return(TVOID);
"while"				return(TWHILE);
"+"         				return(TADD);
"-"         				return(TSUB);
"*"         				return(TMUL);
"/"         				return(TDIV);
"%"         				return(TLEFT);
"="         				return(TASSIGN);
"=="				return(TEQUAL);
"!="				return(TNOTEQU);
"<="				return(TLESSE);
"<"         				return(TLESSTHAN);
">="				return(TGREATE);
">"         				return(TGREATTHAN);
"!"         				return(TNOT);
"&&"				return(TAND);
"||"				return(TOR);
"++"				return(TINC);
"--"				return(TDEC);
"+="				return(TADDASSIGN);
"-="				return(TSUBASSIGN);
"*="				return(TMULASSIGN);
"/="				return(TDIVASSIGN);
"%="				return(TMODASSIGN);
"("         				return(TOPEN);
")"         				return(TCLOSE);
","         				return(TCOMMA);
"{"         				return(TMIDOPEN);
"}"         				return(TMIDCLOSE);
"["         				return(TBIGOPEN);
"]"         				return(TBIGCLOSE);
";"         				return(TSEMICOLON);
"\n"				{cLine++;}
{A}({A}|{D})*   		 	{if(lengthCheck()==1){SymbolTable(); return(TIDENT);} else {printError(overst); return(TIDENT);}}
{D}+	      			return(TNUMBER);
{D}+"."{D}*     			return (TFNUMBER);
"/*"([^*]|\*+[^*/])*\**"*/" 		{for(int i=0;i<yyleng;i++){if(yytext[i]=='\n') cLine++; }}
"//".*				;
[ \t]				;
{D}+{A}({A}|{D})*  			{printError(illid); return(TIDENT);}
.				{printError(illsp);}
%%
int yywrap(){
	return 1;
}
