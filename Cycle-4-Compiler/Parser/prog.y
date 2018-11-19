%{
	#include<stdio.h>
	#include<stdlib.h>
    #include<prog.h>
	int n = 2;
	void yyerror();
    extern int yylex();
    extern int yyparse();
    extern FILE *yyin;
%}

%union{int integer; char*  identifier;}
%start program
%token <identifier> IDENTIFIER 
%token <integer> NUMBER
%token IF ELSE THEN DO PROG BEGIN END WHILE READ WRITE ENDIF ENDWHILE ASSIGN INTEGER
%left '+' '-'
%left '/' '*'
%%

program         : PROG declarations BEGIN command_sequence END
;

declarations    : expression
                | INTEGER id_seq IDENTIFIER '.'
;

id_seq          : expression
                | id_seq IDENTIFIER ','
;

command_sequence : expression
                | command_sequence command
;

command         : expression 
                | IDENTIFIER ASSIGN expression
                | IF expression THEN command_sequence ELSE command_sequence ENDIF
                | WHILE expression DO command_sequence ENDWHILE
                | READ IDENTIFIER
                | WRITE expression
;

expression      : NUMBER 
                | IDENTIFIER 
                | '(' expression ')'
                | expression '+' expression
                | expression '-' expression
                | expression '*' expression
                | expression '/' expression
                | expression '<' expression
                | expression '>' expression
                | expression '=' expression
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
