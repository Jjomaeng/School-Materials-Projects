/* main.c 
* programmer -¡∂πŒ»Ò
* date - 20/04/2021
*/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "tn.h"
#include "glob.h"

extern yylex();
extern char* yytext;
extern int num_line;
extern int nextid;

void main()
{
	enum tnumber tn;  // token number
	printf(" Line number	Token type	ST-index	Token\n");
	while ((tn = yylex()) != TEOF) {

		switch (tn) {
		case TCONST: printf("  %d		Const				%s\n", num_line, yytext); break;
		case TELSE: printf("  %d		Else				%s\n", num_line, yytext); break;
		case TIF: printf("  %d		If				%s\n", num_line, yytext); break;
		case TINT: printf("  %d		Int				%s\n", num_line, yytext); break;
		case TRETURN: printf("  %d		Return				%s\n", num_line, yytext); break;
		case TVOID: printf("  %d		Void				%s\n", num_line, yytext); break;
		case TWHILE: printf("  %d		While				%s\n", num_line, yytext); break;
		case TADD: printf("  %d		Add				%s\n", num_line, yytext); break;
		case TSUB: printf("  %d		Sub				%s\n", num_line, yytext); break;
		case TMUL: printf("  %d		Mul				%s\n", num_line, yytext); break;
		case TDIV: printf("  %d		Div				%s\n", num_line, yytext); break;
		case TLEFT: printf("  %d		Left				%s\n", num_line, yytext); break;
		case TASSIGN: printf("  %d		Assign				%s\n", num_line, yytext); break;
		case TEQUAL: printf("  %d		Equal				%s\n", num_line, yytext); break;
		case TNOTEQU: printf("  %d		Not_equal				%s\n", num_line, yytext); break;
		case TLESSE: printf("  %d		Lesse				%s\n", num_line, yytext); break;
		case TLESSTHAN: printf("  %d		LessThan				%s\n", num_line, yytext); break;
		case TGREATE: printf("  %d		Greater				%s\n", num_line, yytext); break;
		case TGREATTHAN: printf("  %d		GreatThan				%s\n", num_line, yytext); break;
		case TNOT: printf("  %d		Not				%s\n", num_line, yytext); break;
		case TAND: printf("  %d		And				%s\n", num_line, yytext); break;
		case TOR: printf("  %d		Or				%s\n", num_line, yytext); break;
		case TINC: printf("  %d		Increase				%s\n", num_line, yytext); break;
		case TDEC: printf("  %d		Decrease				%sn", num_line, yytext); break;
		case TADDASSIGN: printf("  %d		Add_Assignment_op				%s\n", num_line, yytext); break;
		case TSUBASSIGN: printf("  %d		Sub_Assignment_op				%s\n", num_line, yytext); break;
		case TMULASSIGN: printf("  %d		Mul_Assignment_op				%s\n", num_line, yytext); break;
		case TDIVASSIGN: printf("  %d		Div_Assignment_op				%s\n", num_line, yytext); break;
		case TMODASSIGN: printf("  %d		Mod_Assignment_op				%s\n", num_line, yytext); break;
		case TOPEN: printf("  %d		open				%s\n", num_line, yytext); break;
		case TCLOSE: printf("  %d		close				%s\n", num_line, yytext); break;
		case TCOMMA: printf("  %d		Comma				%s\n", num_line, yytext); break;
		case TMIDOPEN: printf("  %d		Midopen				%s\n", num_line, yytext); break;
		case TMIDCLOSE: printf("  %d		Midclose				%s\n", num_line, yytext); break;
		case TBIGOPEN: printf("  %d		Bigopen				%s\n", num_line, yytext); break;
		case TBIGCLOSE: printf("  %d		Bigclose				%s\n", num_line, yytext); break;
		case TSEMICOLON: printf("  %d		Semicolon				%s\n", num_line, yytext); break;
		case TNUMBER: printf("  %d		Number				%d\n", num_line, atoi(yytext)); break;
		case TFLOAT: printf("  %d		Float				%f\n", num_line, atof(yytext)); break;
		case TIDENT: printf("  %d 		Identifier 	  %d 		%s\n", num_line, nextid, yytext); break;
		case TDEFAULT: printf("  %d		**error!!**				%s %s\n", num_line,yytext,classifyError()); break;
		case TLONGIDENT: printf("  %d		**error!!**				%s %s\n", num_line, yytext, lengthCheck()); break;



			
		}
	}
}
