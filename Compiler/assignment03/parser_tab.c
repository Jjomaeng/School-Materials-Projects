
/*  A Bison parser, made from parser.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	TIDENT	258
#define	TNUMBER	259
#define	TFNUMBER	260
#define	TCONST	261
#define	TELSE	262
#define	TIF	263
#define	TINT	264
#define	TFLOAT	265
#define	TRETURN	266
#define	TVOID	267
#define	TWHILE	268
#define	TEOF	269
#define	TCMNT	270
#define	TEOLCMNT	271
#define	TADD	272
#define	TSUB	273
#define	TDIV	274
#define	TMUL	275
#define	TLEFT	276
#define	TADDASSIGN	277
#define	TSUBASSIGN	278
#define	TMULASSIGN	279
#define	TDIVASSIGN	280
#define	TMODASSIGN	281
#define	TASSIGN	282
#define	TOPEN	283
#define	TCLOSE	284
#define	TCOMMA	285
#define	TMIDOPEN	286
#define	TMIDCLOSE	287
#define	TBIGOPEN	288
#define	TBIGCLOSE	289
#define	TSEMICOLON	290
#define	TDEFAULT	291
#define	TLONGIDENT	292
#define	TNOT	293
#define	TOR	294
#define	TAND	295
#define	TEQUAL	296
#define	TNOTEQU	297
#define	TGREATE	298
#define	TLESSE	299
#define	TINC	300
#define	TDEC	301
#define	TLESSTHAN	302
#define	TGREATTHAN	303
#define	LOWER_THAN_ELSE	304
#define	ELSE	305

#line 1 "parser.y"

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

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		169
#define	YYFLAG		-32768
#define	YYNTBASE	51

#define YYTRANSLATE(x) ((unsigned)(x) <= 305 ? yytranslate[x] : 99)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     4,     7,     9,    11,    14,    17,    20,    21,
    26,    28,    30,    33,    35,    37,    39,    41,    43,    45,
    47,    51,    53,    54,    56,    60,    63,    68,    70,    71,
    73,    76,    77,    82,    86,    88,    89,    94,    96,   100,
   104,   106,   111,   116,   118,   120,   121,   123,   124,   126,
   129,   131,   133,   135,   137,   139,   142,   145,   147,   148,
   154,   162,   167,   173,   178,   182,   186,   188,   190,   194,
   198,   202,   206,   210,   214,   216,   220,   222,   226,   228,
   232,   236,   238,   242,   246,   250,   254,   256,   260,   264,
   266,   270,   274,   278,   280,   283,   286,   289,   292,   294,
   299,   304,   307,   310,   312,   313,   315,   317,   321,   323,
   325,   327,   331
};

static const short yyrhs[] = {    52,
     0,    53,     0,    52,    53,     0,    54,     0,    70,     0,
    55,    67,     0,    55,    35,     0,    55,     1,     0,     0,
    57,    62,    56,    63,     0,    58,     0,    59,     0,    58,
    59,     0,    60,     0,    61,     0,     6,     0,     9,     0,
    12,     0,    10,     0,     3,     0,    28,    64,    29,     0,
    65,     0,     0,    66,     0,    65,    30,    66,     0,    57,
    75,     0,    31,    68,    77,    32,     0,    69,     0,     0,
    70,     0,    69,    70,     0,     0,    57,    72,    71,    35,
     0,    57,    72,     1,     0,    74,     0,     0,    72,    73,
    30,    74,     0,    75,     0,    75,    27,     4,     0,    75,
    27,     5,     0,     3,     0,     3,    33,    76,    34,     0,
     3,    33,    76,     1,     0,     4,     0,     5,     0,     0,
    78,     0,     0,    79,     0,    78,    79,     0,    67,     0,
    80,     0,    82,     0,    83,     0,    84,     0,    81,    35,
     0,    81,     1,     0,    85,     0,     0,     8,    28,    85,
    29,    79,     0,     8,    28,    85,    29,    79,    50,    79,
     0,     8,    28,    85,     1,     0,    13,    28,    85,    29,
    79,     0,    13,    28,    85,     1,     0,    11,    81,    35,
     0,    11,    81,     1,     0,    86,     0,    87,     0,    93,
    27,    86,     0,    93,    22,    86,     0,    93,    23,    86,
     0,    93,    24,    86,     0,    93,    25,    86,     0,    93,
    26,    86,     0,    88,     0,    87,    39,    88,     0,    89,
     0,    88,    40,    89,     0,    90,     0,    89,    41,    90,
     0,    89,    42,    90,     0,    91,     0,    90,    48,    91,
     0,    90,    47,    91,     0,    90,    43,    91,     0,    90,
    44,    91,     0,    92,     0,    91,    17,    92,     0,    91,
    18,    92,     0,    93,     0,    92,    20,    93,     0,    92,
    19,    93,     0,    92,    21,    93,     0,    94,     0,    18,
    93,     0,    38,    93,     0,    45,    93,     0,    46,    93,
     0,    98,     0,    94,    33,    85,    34,     0,    94,    28,
    95,    29,     0,    94,    45,     0,    94,    46,     0,    96,
     0,     0,    97,     0,    86,     0,    97,    30,    86,     0,
     3,     0,     4,     0,     5,     0,    28,    85,    29,     0,
    28,    85,     1,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    28,    30,    31,    33,    34,    36,    37,    38,    40,    41,
    42,    44,    45,    47,    48,    50,    52,    53,    54,    56,
    58,    60,    61,    63,    64,    66,    68,    70,    71,    73,
    74,    76,    77,    77,    79,    80,    80,    82,    83,    84,
    86,    87,    88,    90,    91,    92,    94,    95,    97,    98,
   100,   101,   102,   103,   104,   106,   107,   109,   110,   112,
   113,   114,   116,   117,   119,   120,   122,   124,   125,   126,
   127,   128,   129,   130,   132,   133,   135,   136,   138,   139,
   140,   142,   143,   144,   145,   146,   148,   149,   150,   152,
   153,   154,   155,   157,   158,   159,   160,   161,   163,   164,
   165,   166,   167,   169,   170,   172,   174,   175,   176,   177,
   178,   179,   180
};

static const char * const yytname[] = {   "$","error","$undefined.","TIDENT",
"TNUMBER","TFNUMBER","TCONST","TELSE","TIF","TINT","TFLOAT","TRETURN","TVOID",
"TWHILE","TEOF","TCMNT","TEOLCMNT","TADD","TSUB","TDIV","TMUL","TLEFT","TADDASSIGN",
"TSUBASSIGN","TMULASSIGN","TDIVASSIGN","TMODASSIGN","TASSIGN","TOPEN","TCLOSE",
"TCOMMA","TMIDOPEN","TMIDCLOSE","TBIGOPEN","TBIGCLOSE","TSEMICOLON","TDEFAULT",
"TLONGIDENT","TNOT","TOR","TAND","TEQUAL","TNOTEQU","TGREATE","TLESSE","TINC",
"TDEC","TLESSTHAN","TGREATTHAN","LOWER_THAN_ELSE","ELSE","mini_c","translation_unit",
"external_dcl","function_def","function_header","@1","dcl_spec","dcl_specifiers",
"dcl_specifier","type_qualifier","type_specifier","function_name","formal_param",
"opt_formal_param","formal_param_list","param_dcl","compound_st","opt_dcl_list",
"declaration_list","declaration","@2","init_dcl_list","@3","init_declarator",
"declarator","opt_number","opt_stat_list","statement_list","statement","expression_st",
"opt_expression","if_st","while_st","return_st","expression","assignment_exp",
"logical_or_exp","logical_and_exp","equality_exp","relational_exp","additive_exp",
"multiplicative_exp","unary_exp","postfix_exp","opt_actual_param","actual_param",
"actual_param_list","primary_exp",""
};
#endif

static const short yyr1[] = {     0,
    51,    52,    52,    53,    53,    54,    54,    54,    56,    55,
    57,    58,    58,    59,    59,    60,    61,    61,    61,    62,
    63,    64,    64,    65,    65,    66,    67,    68,    68,    69,
    69,    71,    70,    70,    72,    73,    72,    74,    74,    74,
    75,    75,    75,    76,    76,    76,    77,    77,    78,    78,
    79,    79,    79,    79,    79,    80,    80,    81,    81,    82,
    82,    82,    83,    83,    84,    84,    85,    86,    86,    86,
    86,    86,    86,    86,    87,    87,    88,    88,    89,    89,
    89,    90,    90,    90,    90,    90,    91,    91,    91,    92,
    92,    92,    92,    93,    93,    93,    93,    93,    94,    94,
    94,    94,    94,    95,    95,    96,    97,    97,    98,    98,
    98,    98,    98
};

static const short yyr2[] = {     0,
     1,     1,     2,     1,     1,     2,     2,     2,     0,     4,
     1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
     3,     1,     0,     1,     3,     2,     4,     1,     0,     1,
     2,     0,     4,     3,     1,     0,     4,     1,     3,     3,
     1,     4,     4,     1,     1,     0,     1,     0,     1,     2,
     1,     1,     1,     1,     1,     2,     2,     1,     0,     5,
     7,     4,     5,     4,     3,     3,     1,     1,     3,     3,
     3,     3,     3,     3,     1,     3,     1,     3,     1,     3,
     3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
     3,     3,     3,     1,     2,     2,     2,     2,     1,     4,
     4,     2,     2,     1,     0,     1,     1,     3,     1,     1,
     1,     3,     3
};

static const short yydefact[] = {     0,
    16,    17,    19,    18,     1,     2,     4,     0,     0,    11,
    12,    14,    15,     5,     3,     8,    29,     7,     6,    41,
     9,     0,    35,    38,    13,     0,    59,    28,    30,    46,
     0,    34,     0,     0,     0,    41,   109,   110,   111,     0,
    59,     0,     0,     0,     0,     0,     0,    51,     0,    59,
    49,    52,     0,    53,    54,    55,    58,    67,    68,    75,
    77,    79,    82,    87,    90,    94,    99,    31,    44,    45,
     0,    23,    10,    33,     0,    39,    40,     0,     0,     0,
    95,     0,    96,    97,    98,    27,    50,    57,    56,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   105,     0,
   102,   103,    43,    42,     0,     0,    22,    24,    37,     0,
    66,    65,     0,   113,   112,    76,    90,    78,    80,    81,
    85,    86,    84,    83,    88,    89,    92,    91,    93,    70,
    71,    72,    73,    74,    69,   107,     0,   104,   106,     0,
    26,    21,     0,    62,    59,    64,    59,   101,     0,   100,
    25,    60,    63,   108,    59,    61,     0,     0,     0
};

static const short yydefgoto[] = {   167,
     5,     6,     7,     8,    31,     9,    10,    11,    12,    13,
    21,    73,   116,   117,   118,    48,    27,    28,    14,    33,
    22,    34,    23,    24,    71,    49,    50,    51,    52,    53,
    54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
    64,    65,    66,   147,   148,   149,    67
};

static const short yypact[] = {    25,
-32768,-32768,-32768,-32768,    25,-32768,-32768,     9,    18,    25,
-32768,-32768,-32768,-32768,-32768,-32768,    25,-32768,-32768,    13,
-32768,    12,-32768,    -8,-32768,    42,    79,    25,-32768,    23,
    15,-32768,    50,    20,    84,    21,-32768,-32768,-32768,    65,
    11,    68,    11,    11,    11,    11,    11,-32768,    73,   110,
-32768,-32768,    16,-32768,-32768,-32768,-32768,-32768,    70,     8,
    78,    51,   109,    81,    40,    58,-32768,-32768,-32768,-32768,
    19,    25,-32768,-32768,    42,-32768,-32768,    11,    17,    11,
-32768,    29,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    11,
    11,    11,    11,    11,    11,    11,    11,    11,    11,    11,
    11,    11,    11,    11,    11,    11,    11,    11,    11,    11,
-32768,-32768,-32768,-32768,    42,    83,    92,-32768,-32768,    31,
-32768,-32768,    32,-32768,-32768,     8,-32768,    78,    51,    51,
   109,   109,   109,   109,    81,    81,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,   106,-32768,   113,   119,
-32768,-32768,    25,-32768,   126,-32768,   126,-32768,    11,-32768,
-32768,    90,-32768,-32768,   126,-32768,   147,   158,-32768
};

static const short yypgoto[] = {-32768,
-32768,   154,-32768,-32768,-32768,   -17,-32768,   150,-32768,-32768,
-32768,-32768,-32768,-32768,    10,   153,-32768,-32768,    -5,-32768,
-32768,-32768,    87,    52,-32768,-32768,-32768,   -49,-32768,   124,
-32768,-32768,-32768,   -42,  -100,-32768,    76,    77,    53,    55,
    34,   -21,-32768,-32768,-32768,-32768,-32768
};


#define	YYLAST		172


static const short yytable[] = {    26,
    87,    82,   140,   141,   142,   143,   144,   145,   146,    16,
    26,    29,    32,    37,    38,    39,    88,   121,    35,   113,
    20,    81,    68,    83,    84,    85,    69,    70,    43,   124,
     1,   154,   156,     2,     3,   120,     4,   123,    44,    17,
   -20,   -36,    72,    18,    36,    30,   -32,    91,    45,    75,
    89,   122,   114,    30,   115,    46,    47,   125,   164,   155,
   157,   103,   104,   105,   106,   107,   108,   150,   127,   127,
   127,   127,   127,   127,   127,   127,   127,   127,   137,   138,
   139,    37,    38,    39,    74,   109,    40,    76,    77,    41,
   110,    42,    78,    94,    95,    80,    43,    96,    97,   100,
   101,   102,   111,   112,    86,   162,    44,   163,    90,    17,
   -48,   152,    37,    38,    39,   166,    45,    40,    92,    93,
    41,   153,    42,    46,    47,    98,    99,    43,    37,    38,
    39,   135,   136,    40,   158,   115,    41,    44,    42,   165,
    17,   -47,   159,    43,   129,   130,   168,    45,   131,   132,
   133,   134,   160,    44,    46,    47,    17,   169,    15,    25,
    19,   119,   161,    45,    79,   126,   151,   128,     0,     0,
    46,    47
};

static const short yycheck[] = {    17,
    50,    44,   103,   104,   105,   106,   107,   108,   109,     1,
    28,    17,     1,     3,     4,     5,     1,     1,    27,     1,
     3,    43,    28,    45,    46,    47,     4,     5,    18,     1,
     6,     1,     1,     9,    10,    78,    12,    80,    28,    31,
    28,    30,    28,    35,     3,    33,    35,    40,    38,    30,
    35,    35,    34,    33,    72,    45,    46,    29,   159,    29,
    29,    22,    23,    24,    25,    26,    27,   110,    90,    91,
    92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
   102,     3,     4,     5,    35,    28,     8,     4,     5,    11,
    33,    13,    28,    43,    44,    28,    18,    47,    48,    19,
    20,    21,    45,    46,    32,   155,    28,   157,    39,    31,
    32,    29,     3,     4,     5,   165,    38,     8,    41,    42,
    11,    30,    13,    45,    46,    17,    18,    18,     3,     4,
     5,    98,    99,     8,    29,   153,    11,    28,    13,    50,
    31,    32,    30,    18,    92,    93,     0,    38,    94,    95,
    96,    97,    34,    28,    45,    46,    31,     0,     5,    10,
     8,    75,   153,    38,    41,    90,   115,    91,    -1,    -1,
    45,    46
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 8:
#line 38 "parser.y"
{yyerrok; printError(nosemi);;
    break;}
case 9:
#line 40 "parser.y"
{ident_name(type_function_name,yyvsp[-1]);;
    break;}
case 17:
#line 52 "parser.y"
{yyval = 1; tmp_type = 1;;
    break;}
case 18:
#line 53 "parser.y"
{yyval = 2; tmp_type = 2;;
    break;}
case 19:
#line 54 "parser.y"
{yyval = 3; tmp_type = 3;;
    break;}
case 20:
#line 56 "parser.y"
{hscode = ComputeHS(nextid, idx);;
    break;}
case 26:
#line 66 "parser.y"
{ident_name(type_function_variable,yyvsp[-1]);;
    break;}
case 32:
#line 76 "parser.y"
{if(yyvsp[0] == 4) ident_name(type_array,yyvsp[-1]); else ident_name(type_variable,yyvsp[-1]);;
    break;}
case 34:
#line 77 "parser.y"
{yyerrok; printError(nosemi);;
    break;}
case 36:
#line 80 "parser.y"
{if(yyval == 4) ident_name(type_array, tmp_type); else ident_name(type_variable, tmp_type);;
    break;}
case 41:
#line 86 "parser.y"
{hscode = ComputeHS(nextid, idx);;
    break;}
case 42:
#line 87 "parser.y"
{yyval=4; hscode = ComputeHS(nextid, idx);;
    break;}
case 43:
#line 88 "parser.y"
{yyerrok; printError(noclose);;
    break;}
case 57:
#line 107 "parser.y"
{yyerrok; printError(nosemi);;
    break;}
case 62:
#line 114 "parser.y"
{yyerrok; printError(noclose);;
    break;}
case 64:
#line 117 "parser.y"
{yyerrok; printError(noclose);;
    break;}
case 66:
#line 120 "parser.y"
{yyerrok; printError(nosemi);;
    break;}
case 113:
#line 180 "parser.y"
{yyerrok; printError(noclose);;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 182 "parser.y"

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
