%{
	#include<stdio.h>
	#include<stdlib.h>
	int n = 2;
	void yyerror();
%}

%start stmt
%token ID NUM
%left '+' '-'
%left '/' '*'
%%

stmt : expr
    | ID '=' expr
;
expr : expr '+' expr
	| expr '-' expr
	| expr '*' expr
	| expr '/' expr
	| '(' expr ')'
	| ID
	| NUM
;
%%

void main()
{
	while(n)
	{
        printf("INPUT AN EXPRESSION : ");
        yyparse();
        printf("VALID EXPRESSION IDENTIFIED\n\n");
	}
}

void yyerror()
{
	printf("EXPRESSION IS INVALID\n\n");
	exit(0);
}
