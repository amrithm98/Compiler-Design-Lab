%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<iostream>
    #include<string>
    #include<vector>
    #include<stack>
    using namespace std;

    int yylex();
    void yyerror(const char *s);

    struct sym_rec 
    {
        char *name;
        int data_offset;
        sym_rec *next;
    };

    sym_rec *HEAD = 0;
    int data_offset = 0;
    int output_line_no = 1;
    extern int yylineno;

    sym_rec *put_symbol(char *name);
    sym_rec *get_symbol(char *name);
    void install(char *name);
    void context_check(char *name);
    void printError(int x);
    void display_symtab();
    void write_machine_code();

    stack<int> refStack;
    vector<string> machine_code;

%}

%union
{
    char *name;
    int value;
}

%token ID NUM PROG BEG INT THEN IF ELSE EIF WHILE EWHILE END DO COMMA DOT SEMICOLON ASSIGN EQUAL LT GT READ WRITE
%type <name> ID
%type <value> NUM
%start program

%left '|'
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'
%left '<' '>'

%%
program : PROG declarations BEG command_sequence END;

declarations : %empty 
                | INT id_seq ID { install($3); }
                  DOT { machine_code.push_back("res " + to_string(data_offset)); }
                ;

id_seq : %empty | id_seq ID { install($2); } COMMA
                ;

command_sequence : %empty 
                | command_sequence command SEMICOLON
                ;
                    
command :   %empty
            | ID ASSIGN expression
            | IF expression THEN command_sequence ELSE command_sequence EIF
            | WHILE expression DO command_sequence EWHILE
            | READ ID
            | WRITE expression
            ;

expression :    NUM
                | ID
                | '(' expression ')'
                | expression '+' expression
                | expression '*' expression
                | expression '-' expression
                | expression '/' expression
                | expression '=' expression
                | expression LT expression
                | expression GT expression
                ;

%%

void printError(int x)
{
    switch(x)
    {
        case 1 :
            cout << "\nError " << yylineno << " Redefinition of Variable " << endl;
            break;
        case 2 :
            cout << "\nError " << yylineno << " Undefined Variable " << endl;
            break;
        case 3 :
            cout << "\nError " << yylineno << " Type Error " << endl;
            break;
    }
    cout << "\nExiting Program Compilation !!!!\n";
    exit(0);
}

sym_rec *get_symbol(char *name)
{
    sym_rec *temp = HEAD;
    while(temp != NULL)
    {
        if(strcmp(temp->name , name ) == 0)
            return temp;

        temp = temp->next;
    }

    return NULL;
}

sym_rec *put_symbol(char *name)
{
    sym_rec *node = new sym_rec;
    
    node->name = strdup(name);
    node->data_offset = data_offset;

    data_offset = data_offset + 1;

    node->next = HEAD;
    HEAD = node;

    return node;
}

void context_check(char *name)
{
    sym_rec *temp = get_symbol(name);
    if(temp == NULL)
    {
        printError(2);
        return ;
    }
}

void install(char *name)
{
    sym_rec *temp = get_symbol(name);
    if(temp != NULL)
    {
        printError(1);
        return ;
    }
    put_symbol(name);
}

void display_symtab()
{
    sym_rec *temp = HEAD;
    cout << "\nSYMBOL TABLE \n============ \n";
    cout << "Name \t\t Offset\n----- \t\t -------\n";

    while(temp != NULL)
    {
        cout << temp->name << "\t\t" << temp->data_offset << endl;
        temp = temp->next;
    }
}

void write_machine_code()
{
    cout << "\nMACHINE CODE \n============= \n";
    cout << "OpCode \t\t Operand\n------ \t\t -------\n";
}

void yyerror(const char *name)
{
    cout << "\nRESULT : Error : " << name << endl;
}

int main()
{
    yyparse();

    cout << "\nRESULT : Successfully Parsed the Given Program \n";
    
    display_symtab();

    write_machine_code();

    return 0;
}