%{
	#include <stdio.h>
%}

letter [a-zA-Z]
digit [0-9]
id {letter}*|({letter}{digit})+
notid ({digit}{letter})+

%%
"."				{return '.';}
":="			{return ASSIGN;}
";"				{return ';';}
"+" 			{return '+';}
"-"             {return '-';}
"*"             {return '*';}
"/"				{return '/';}
"="             {return '=';}
"<"				{return '<';}
">"             {return '>';}
")"				{return ')';}
","				{return ',';}
"read"			{return READ;}
"prog"			{return PROG;}
"write"			{return WRITE;}
"begin"			{return BEGIN;}
"integer"		{return INTEGER;}
"while"			{return WHILE;}
"do"			{return DO;}
"if"			{return IF;}
"else"			{return ELSE;}
"endif"			{return ENDIF;}
"end"			{return END;}
"then"			{return THEN;}
"endwhile"		{return ENDWHILE;}
{id}			return IDENTIFIER;
{notid} 		{printf("\n%s is not an identifier at line %d\n", yytext,yylineno); exit(0);}
[1-9][0-9]*		{return DIGIT};
\n				{yylineno++;}
[ \t]			;
"("				{return '(';}
%%

int yywrap(void)
{
	return 1;
}