#include <iostream>
#include "prog.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

int main(void)
{
	int ntoken;
	ntoken = yylex();
	while(ntoken)
	{
		printf("\nToken : %d Value : %s",ntoken,yytext);
		ntoken = yylex();
	}
	return 0;
}
