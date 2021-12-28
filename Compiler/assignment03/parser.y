%{
#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include "glob.h"

hscode = 0;
int tmp_type;

/*yacc source for Mini C*/
extern yylex();
extern printError();
extern yyerror();
extern int cLine;
void ident_name(type_enum type,int form);
extern ComputeHS(int nid, int leng);
%}

%token TIDENT TNUMBER TFNUMBER TCONST TELSE TIF  TINT TFLOAT TRETURN TVOID TWHILE TEOF TCMNT TEOLCMNT
%token TADD TSUB TDIV TMUL TLEFT TADDASSIGN TSUBASSIGN TMULASSIGN TDIVASSIGN TMODASSIGN TASSIGN
%token TOPEN TCLOSE TCOMMA TMIDOPEN TMIDCLOSE TBIGOPEN TBIGCLOSE TSEMICOLON TDEFAULT TLONGIDENT
%token TNOT TOR TAND TEQUAL TNOTEQU TGREATE TLESSE TINC TDEC TLESSTHAN TGREATTHAN

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
mini_c 			: translation_unit
			;
translation_unit 		: external_dcl
			| translation_unit external_dcl
			;
external_dcl 		: function_def
		  	| declaration
			;
function_def 		: function_header compound_st
			| function_header TSEMICOLON
			| function_header error {yyerrok; printError(nosemi);}
			;
function_header 		: dcl_spec function_name {ident_name(type_function_name,$1);} formal_param
			;
dcl_spec 			: dcl_specifiers
			;
dcl_specifiers 		: dcl_specifier
		 	| dcl_specifiers dcl_specifier
			;
dcl_specifier 		: type_qualifier
			| type_specifier
			;
type_qualifier 		: TCONST
			;
type_specifier 		: TINT					{$$ = 1; tmp_type = 1;}
		 	| TVOID							{$$ = 2; tmp_type = 2;}
			| TFLOAT						{$$ = 3; tmp_type = 3;}
			;
function_name 		: TIDENT {hscode = ComputeHS(nextid, idx);}
			;
formal_param 		: TOPEN opt_formal_param TCLOSE
			;
opt_formal_param 		: formal_param_list
		   	|
			;
formal_param_list 		: param_dcl
		    	| formal_param_list TCOMMA param_dcl
			;
param_dcl 		: dcl_spec declarator	{ident_name(type_function_variable,$1);}
			;
compound_st 		: TMIDOPEN opt_dcl_list opt_stat_list TMIDCLOSE
			;
opt_dcl_list 		: declaration_list
			|
			;
declaration_list 		: declaration
			| declaration_list declaration
			;
declaration 		: dcl_spec init_dcl_list {if($2 == 4) ident_name(type_array,$1); else ident_name(type_variable,$1);} TSEMICOLON
			| dcl_spec init_dcl_list error {yyerrok; printError(nosemi);}
			;
init_dcl_list 		: init_declarator
			| init_dcl_list {if($$ == 4) ident_name(type_array, tmp_type); else ident_name(type_variable, tmp_type);} TCOMMA init_declarator
			;
init_declarator 		: declarator
		 	| declarator TASSIGN TNUMBER
		 	| declarator TASSIGN TFNUMBER
			;
declarator 		: TIDENT {hscode = ComputeHS(nextid, idx);}
	     		| TIDENT TBIGOPEN opt_number TBIGCLOSE {$$=4; hscode = ComputeHS(nextid, idx);}
			| TIDENT TBIGOPEN opt_number error {yyerrok; printError(noclose);}
			;
opt_number 		: TNUMBER
			| TFNUMBER
	     		|
			;
opt_stat_list 		: statement_list
		 	|
			;
statement_list 		: statement
		 	| statement_list statement
			;
statement 		: compound_st
	   		| expression_st
	   		| if_st
	   		| while_st
	   		| return_st
	   		;
expression_st 		: opt_expression TSEMICOLON
			| opt_expression error {yyerrok; printError(nosemi);}
			;
opt_expression 		: expression
		 	|
			;
if_st 			: TIF TOPEN expression TCLOSE statement %prec LOWER_THAN_ELSE
			| TIF TOPEN expression TCLOSE statement ELSE statement
			| TIF TOPEN expression error  {yyerrok; printError(noclose);}
			;
while_st 			: TWHILE TOPEN expression TCLOSE statement
			| TWHILE TOPEN expression error 	 {yyerrok; printError(noclose);}
			;
return_st 			: TRETURN opt_expression TSEMICOLON
			| TRETURN opt_expression error  	 {yyerrok; printError(nosemi);}
			;
expression 		: assignment_exp
			;
assignment_exp 		: logical_or_exp
			| unary_exp TASSIGN assignment_exp
			| unary_exp TADDASSIGN assignment_exp
			| unary_exp TSUBASSIGN assignment_exp
			| unary_exp TMULASSIGN assignment_exp
			| unary_exp TDIVASSIGN assignment_exp
			| unary_exp TMODASSIGN assignment_exp
			;
logical_or_exp 		: logical_and_exp
			| logical_or_exp TOR logical_and_exp
			;
logical_and_exp 		: equality_exp
		 	| logical_and_exp TAND equality_exp
			;
equality_exp 		: relational_exp
			| equality_exp TEQUAL relational_exp
			| equality_exp TNOTEQU relational_exp
			;
relational_exp 		: additive_exp
			| relational_exp TGREATTHAN additive_exp
			| relational_exp TLESSTHAN additive_exp
			| relational_exp TGREATE additive_exp
			| relational_exp TLESSE additive_exp
			;
additive_exp 		: multiplicative_exp
			| additive_exp TADD multiplicative_exp
			| additive_exp TSUB multiplicative_exp
			;
multiplicative_exp 		: unary_exp
		    	| multiplicative_exp TMUL unary_exp
		    	| multiplicative_exp TDIV unary_exp
		    	| multiplicative_exp TLEFT unary_exp
			;
unary_exp 		: postfix_exp
	   		| TSUB unary_exp
	   		| TNOT unary_exp
	   		| TINC unary_exp
	   		| TDEC unary_exp
			;
postfix_exp 		: primary_exp
	      		| postfix_exp TBIGOPEN expression TBIGCLOSE
	      		| postfix_exp TOPEN opt_actual_param TCLOSE
	      		| postfix_exp TINC
	      		| postfix_exp TDEC
			;
opt_actual_param 		: actual_param
		  	|
			;
actual_param 		: actual_param_list
			;
actual_param_list 		: assignment_exp
		   	| actual_param_list TCOMMA assignment_exp
primary_exp 		: TIDENT
	     		| TNUMBER
			| TFNUMBER
	     		| TOPEN expression TCLOSE
			| TOPEN expression error 	{yyerrok; printError(noclose);}
			;
%%
void ident_name(type_enum type, int form)
{
	if (HT[hscode]->type != 0) {
		type = type_already;
	}
	switch (type) {
	case type_already:
		break;
	case type_function_name:
		if (form == 1) { HT[hscode]->type = 1; }
		else if (form == 2) { HT[hscode]->type = 2; }
		else if (form == 3) { HT[hscode]->type = 3; }
		break;

	case type_function_variable:
		if (form == 1) { HT[hscode]->type = 4; }
		else if (form == 2) { HT[hscode]->type = 5; }
		else if (form == 3) { HT[hscode]->type = 6; }
		break;

	case type_variable:
		if (form == 1) { HT[hscode]->type = 7; }
		else if (form == 2) { HT[hscode]->type = 8; }
		else if (form == 3) { HT[hscode]->type = 9; }
		break;

	case type_array:
		if (form == 1) { HT[hscode]->type = 10; }
		else if (form == 2) { HT[hscode]->type = 11; }
		else if (form == 3) { HT[hscode]->type = 12; }
		break;
	}
}
