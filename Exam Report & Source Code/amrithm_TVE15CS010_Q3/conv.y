/**

Author  : Amrith M
Code    : INFIX TO POSTFIX CONVERSION
INPUT   : input.txt

Grammar : Given Below

Execution : sh exec.sh && ./a.out < input.txt

*/

%{
    #include <stdio.h>
    #include <stdlib.h>

    void yyerror(char *err);
%}

//Union stores either name or val of an item at a time 

%union
{
    char *name;
    int val;
};

//Precedence Given based on input

%left '*' '/'
%left '+' '-'

%token ID NUM
%type<name> ID
%type<val> NUM
%type<val> expression

%start prog

%%
prog : expression;
expression : expression '+' expression  { $$ = $1 + $3; printf("+");}
            | expression '*' expression { $$ = $1 * $3; printf("*");}
            | expression '-' expression { $$ = $1 - $3; printf("-");}
            | expression '/' expression { $$ = $1 / $3; printf("/");}
            | ID    {   printf("%s",$1); }
            | NUM   {   printf("%d",$1); }
            ;
%%

void yyerror(char *name)
{
    printf("\nError: %s", name);
}

int yywrap()
{
    return 1;
}

int main()
{
    //yyparse askes yylex for tokens and parses it 
    
    yyparse();

    printf("\n");
    
    return 0;
}
