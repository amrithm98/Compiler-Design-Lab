/**

Author  : Amrith M
Code    : String Replace
INPUT   : input.txt
          File contains P and R followed by file contents in the new line

Execution : lex prog.l && g++ lex.yy.c && ./a.out < input.txt

*/

%{
    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>
    #include<iostream>
    #include<fstream>
    #include<string>
    char p[100], r[100];
    void check(char *name);
    using namespace std;
%}

letter [a-zA-Z]
digit [0-9]

%%   
[ \t]                               {   ;   }
[\n]                                {   yylineno++; printf("\n");   }                  
({letter}|{digit})+                 {   check(yytext);  }
.                                   {   printf("%s", yytext) ;  }
%%

void check(char *name)
{
    if(strcmp(name, p) == 0)
    {
        printf("%s ",r);
    }
    else
    {
        printf("%s ",name);
    }
}

int yywrap()
{
    return 1;
}

int main()
{
    scanf("%s %s",p,r);
    cout << "\nP : " << p << " R: " << r << endl;
    yylex();
    cout << "\n";
    return 0;
}
