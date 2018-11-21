#include<iostream>
#include<map>
#include<set>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

map<char, vector<string>> productions;
set<char> terminals, non_terminals, all_symbols;

bool isTerminal(char c)
{
    if(terminals.find(c) == terminals.end())
        return false;

    return true;
}

bool isNonTerminal(char c)
{
    if(non_terminals.find(c) == non_terminals.end())
        return false;

    return true;
}

bool parse_input(int index , string &input, string production)
{

    // cout << input[index] << " " << production[0] << endl;

    if(production.size() > 0 && production[0] == '#')
        return parse_input(index, input, production.substr(1));


    if(production.size() == 0)
    {
        if(input[index] == '$')
            return true;

        return false;
    }

    if( isTerminal( production[0]) )
    {
        if(input[index] == production[0])
            return parse_input(index + 1, input, production.substr(1));
        else
            return false;
    }

    if( isNonTerminal(production[0]) )
    {
        char c = production[0];
        for(auto it : productions[c])
        {
            if(parse_input(index, input, it + production.substr(1)))
                return true;
        }
    }

    return false;

}

int main()
{
    fstream infile("grammar.txt");

    string start;
    getline(infile, start);

    string temp;

    while(getline(infile, temp))
    {
        productions[temp[0]].push_back(temp.substr(2));

        non_terminals.insert(temp[0]);

        all_symbols.insert(temp[0]);

        all_symbols.insert(temp.begin()+2, temp.end());
    }

    for(auto it : all_symbols)
    {
        if(non_terminals.find(it) == non_terminals.end())
            terminals.insert(it);
    }

    cout << "\nProductions \n=============\n";

    for(auto it : productions)
    {
        for(auto it1 : it.second)
            cout << it.first << " -> " << it1 << endl;
    }

    cout << "\nTerminals : ";
    for(auto it : terminals)
        cout << it << " ";

    cout << "\nNon Terminals : ";
    for(auto it : non_terminals)
        cout << it << " ";

    cout << "\nStart Symbol : " << start;

    string expression;

    cout << "\nEnter Expression : ";
    cin >> expression;

    expression.append("$");

    if(parse_input(0, expression, start))
        cout << "\nValid Expression\n";
    else
        cout << "\nInvalid Expression\n";

    return 0;
}