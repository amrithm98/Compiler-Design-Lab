%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<iostream>
    #include<string>
    #include<vector>
    #include<stack>
    #include<fstream>
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
    vector< pair<string, int> > machine_code;

%}

%union
{
    char *name;
    int value;
}

%token ID NUM PROG BEG INT THEN IF ELSE EIF WHILE EWHILE END DO COMMA DOT 
%token SEMICOLON ASSIGN EQUAL LT GT READ WRITE
%type <name> ID
%type <value> NUM
%start program

%left '|'
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'
%left '<' '>'

%%
program : PROG declarations BEG command_sequence END { machine_code.push_back(make_pair("halt", 0)); }

declarations : %empty 
                | INT id_seq ID { install($3); }
                  DOT { machine_code.push_back(make_pair("res",data_offset)); }
                ;

id_seq : %empty | id_seq ID { install($2); } COMMA
                ;

command_sequence : %empty 
                | command_sequence command SEMICOLON
                ;
                    
command :   %empty
            | ID ASSIGN expression  { 
                                        int offset = get_symbol($1)->data_offset;

                                        machine_code.push_back(make_pair("store", offset));
                                    }

            | IF expression THEN    {
                                        machine_code.push_back(make_pair("jmp_false",0));
                                        refStack.push(machine_code.size() - 1);
                                    }

              command_sequence      

              ELSE                  {
                                        machine_code.push_back(make_pair("goto",0));

                                        int pos = refStack.top();
                                        refStack.pop();

                                        machine_code[pos].second = machine_code.size() + 1;

                                        refStack.push(machine_code.size() - 1);

                                    }

              command_sequence EIF {
                                            int pos = refStack.top();
                                            refStack.pop();

                                            machine_code[pos].second = machine_code.size() + 1;
                                    }

            | WHILE                 {
                                        refStack.push(machine_code.size() - 1);
                                    }

              expression            {
                                        machine_code.push_back(make_pair("jmp_false",0));
                                        refStack.push(machine_code.size() - 1);
                                    }

              DO command_sequence   {
                                        int pos = refStack.top();
                                        refStack.pop();

                                        machine_code.push_back(make_pair("goto", refStack.top() + 1));
                                        refStack.pop();

                                        machine_code[pos].second = machine_code.size() + 1;
                                    }
              EWHILE
            | READ ID               { 
                                        context_check($2);

                                        int offset = get_symbol($2)->data_offset;

                                        machine_code.push_back(make_pair("read", offset));
                                    }

            | WRITE expression      { 
                                        machine_code.push_back(make_pair("write",0));
                                    }
            ;

expression :    NUM             {   machine_code.push_back(make_pair("load_int", $1) ); }

                | ID            {       
                                        int offset = get_symbol($1)->data_offset;
                                        machine_code.push_back(make_pair("load_var",offset));
                                }
                | '(' expression ')'
                | expression '+' expression {  machine_code.push_back(make_pair("add", 0)); }
                | expression '*' expression {  machine_code.push_back(make_pair("mul", 0)); }
                | expression '-' expression {  machine_code.push_back(make_pair("sub", 0)); }
                | expression '/' expression {  machine_code.push_back(make_pair("div", 0)); }
                | expression '=' expression {  machine_code.push_back(make_pair("eq", 0)); }
                | expression LT expression  {  machine_code.push_back(make_pair("lt", 0)); }
                | expression GT expression  {  machine_code.push_back(make_pair("gt", 0)); }
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
    ofstream out("machinecode.txt");

    cout << "\nMACHINE CODE \n============= \n";
    cout << "Line \t OpCode \tOperand\n----- \t ------ \t-------\n";
    vector< pair<string, int> >::iterator it ;
    int count = 0;

    for(it = machine_code.begin(); it != machine_code.end(); it++)
    {
        pair<string, int> p = (*it);
        if(p.first[0] == 'l' && p.first[1] == 'o')
        {
            cout << count++ << " \t " << p.first << " \t" << p.second << endl;
        }
        else
        {
            cout << count++ << " \t " << p.first << " \t \t" << p.second << endl;
        }

        out << p.first << " " << p.second << endl;
    }
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