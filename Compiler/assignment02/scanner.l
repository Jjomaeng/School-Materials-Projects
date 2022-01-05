%{
/* scanner.l - lexical analyze for the MiniC
* programmer - ¿Ã»ø¡¯,¡∂πŒ»Ò 
* date - 20/04/2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tn.h"
#include "glob.h"

int num_line = 1;
int idx = 0;
int nextid = 0;
int hashcode, found, sameid;
%}
A [A-Za-z_]
D [0-9]
%%
[/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]   return(TCMNT);
"const"				return(TCONST);
"else"				return(TELSE);
"if"				return(TIF);
"int"				return(TINT);
"return"				return(TRETURN);
"void"				return(TVOID);
"while"				return(TWHILE);
"+"         return(TADD);
"-"         return(TSUB);
"*"         return(TMUL);
"/"         return(TDIV);
"%"         return(TLEFT);
"="         return(TASSIGN);
"=="				return(TEQUAL);
"!="				return(TNOTEQU);
"<="				return(TLESSE);
"<"         return(TLESSTHAN);
">="				return(TGREATE);
">"         return(TGREATTHAN);
"!"         return(TNOT);
"&&"				return(TAND);
"||"				return(TOR);
"++"				return(TINC);
"--"				return(TDEC);
"+="				return(TADDASSIGN);
"-="				return(TSUBASSIGN);
"*="				return(TMULASSIGN);
"/="				return(TDIVASSIGN);
"%="				return(TMODASSIGN);
"("         return(TOPEN);
")"         return(TCLOSE);
","         return(TCOMMA);
"{"         return(TMIDOPEN);
"}"         return(TMIDCLOSE);
"["         return(TBIGOPEN);
"]"         return(TBIGCLOSE);
";"         return(TSEMICOLON);
{A}({A}|{D})*   		 {if(lengthCheck()==yytext){SymmbolTable(); return(TIDENT);} else return(TLONGIDENT);}
{D}+	      return(TNUMBER);
{D}+"."{D}*     return (TFLOAT);
"//".*			return(TEOLCMNT);
[ \t]+				;
[\n]        ++num_line;
.|{D}({A}|{D})*				return(TDEFAULT);

%%
int yywrap(){
printf(" End of Lex\n");
return 1;
}
