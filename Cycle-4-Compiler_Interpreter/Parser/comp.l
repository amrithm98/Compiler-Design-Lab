/*** Definition section ***/

%{
/* C code to be copied verbatim */
	#include <stdio.h>
	#include <stdlib.h>
	#include "y.tab.h"
	#include <iostream>
	using namespace std;
%}

/* This tells flex to read only one input file */
%option noyywrap
%%
	/*** Rules section ***/

	/* [0-9]+ matches a string of one or more digits */
"prog"		return PROG;
"integer"	return INT;
"begin"		return BEG;
"read"		return READ;
"if"		return IF;
"then"		return THEN;
"else"		return ELSE;
"endif"		return EIF;
"while"		return WHILE;
"do"		return DO;
"endwhile"	return EWHILE;
"write"		return WRITE;
"end"		return END;
[a-zA-Z_][_a-zA-Z0-9]*	{ printf("\nIdentifier : %s",yytext); yylval.name = strdup(yytext); return IDENTI; }
[0-9]+					{ yylval.num = atoi(yytext); return NUM; }
\< 			return LS;
\. 			return DOT;
\, 			return COMMA;
\:= 		return EQUAL;
[+] 		return PLUS;
[-] 		return MINUS;
[*] 		return MULT;
[/] 		return DIV;

%%
/*** C Code section ***/

// int yywrap(void)
// {
// 	return 1;
// }