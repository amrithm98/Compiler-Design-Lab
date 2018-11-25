/* A Bison parser, made by GNU Bison 3.2.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    NUM = 259,
    PROG = 260,
    BEG = 261,
    INT = 262,
    THEN = 263,
    IF = 264,
    ELSE = 265,
    EIF = 266,
    WHILE = 267,
    EWHILE = 268,
    END = 269,
    DO = 270,
    COMMA = 271,
    DOT = 272,
    SEMICOLON = 273,
    ASSIGN = 274,
    EQUAL = 275,
    LT = 276,
    GT = 277,
    READ = 278,
    WRITE = 279
  };
#endif
/* Tokens.  */
#define ID 258
#define NUM 259
#define PROG 260
#define BEG 261
#define INT 262
#define THEN 263
#define IF 264
#define ELSE 265
#define EIF 266
#define WHILE 267
#define EWHILE 268
#define END 269
#define DO 270
#define COMMA 271
#define DOT 272
#define SEMICOLON 273
#define ASSIGN 274
#define EQUAL 275
#define LT 276
#define GT 277
#define READ 278
#define WRITE 279

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 40 "parser.y" /* yacc.c:1912  */

    char *name;
    int value;

#line 110 "y.tab.h" /* yacc.c:1912  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
