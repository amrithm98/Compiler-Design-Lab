#include <iostream>
#include "calc.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

int main(void)
{
	int ntoken;
	ntoken = yylex();
	while(ntoken)
	{
		printf("\n%d",ntoken);
		ntoken = yylex();
	}
	return 0;
}

