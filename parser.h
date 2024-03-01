/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NL = 258,
     VAR = 259,
     TQ = 260,
     FTQ = 261,
     FAIRE = 262,
     SI = 263,
     ALORS = 264,
     SINON = 265,
     FSI = 266,
     LIRE = 267,
     AFFICHER = 268,
     DEBUT = 269,
     FIN = 270,
     ENTREE = 271,
     ALGO = 272,
     ID = 273,
     NB = 274,
     AFFECT = 275,
     OU = 276,
     ET = 277,
     SUPEGAL = 278,
     INFEGAL = 279,
     NON = 280
   };
#endif
/* Tokens.  */
#define NL 258
#define VAR 259
#define TQ 260
#define FTQ 261
#define FAIRE 262
#define SI 263
#define ALORS 264
#define SINON 265
#define FSI 266
#define LIRE 267
#define AFFICHER 268
#define DEBUT 269
#define FIN 270
#define ENTREE 271
#define ALGO 272
#define ID 273
#define NB 274
#define AFFECT 275
#define OU 276
#define ET 277
#define SUPEGAL 278
#define INFEGAL 279
#define NON 280




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 13 "parser.y"
{
  int nb;
  char id[64];
  struct asa * noeud;
 }
/* Line 1529 of yacc.c.  */
#line 105 "parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

