%{
    int yylineno;
%}

%%
^(.*)\n  {printf("%d %s", yylineno++, yytext);}
%%

int main()
{
    //Regexp Starting with anything except newline and newline, print
    yylex();
}

int yywrap()
{
    return 1;
}