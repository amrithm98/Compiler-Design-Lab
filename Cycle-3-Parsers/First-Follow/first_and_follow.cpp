#include<bits/stdc++.h>
using namespace std;

set<char> terminals, nonTerminals;
map<char,set<string>> productions;
map<char,set<char>> first;
map<char,set<char>> follow;

void showDetails()
{
    cout << "\nProductions : \n";
    for(auto it : productions)
    {
        for(auto it1 : it.second)
            cout << it.first << " : " << it1 << endl;
    }
    
    cout << "\nSet of Terminals : ";
    for(auto it : terminals)
        cout << it << " ";

    cout << "\nSet of Non Terminals : ";
    for(auto it : nonTerminals)
        cout << it << " ";

    cout << "\nFIRST : \n";
    for(auto it : first)
    {
        cout << it.first << " : ";
        for(auto it1 : it.second)
            cout << it1 << " ";

        cout << endl;
    }

    cout << "\n\n";
}

void findFirst(char c)
{
    for(auto it : productions[c])
    {
        if(terminals.find(it[0]) == terminals.end())
        {
            findFirst(it[0]);
            first[c] = first[it[0]];
        }
        else
        {
            first[c].insert(it[0]);
        }
    }
}

void findFollow()
{
    
}

int main()
{
    ifstream infile("productions.txt");

    string temp;

    while(getline(infile,temp))
    {
        stringstream ss(temp);
        string prods;

        vector<string> lhs_rhs;
        while(getline(ss,prods,'='))
        {
            lhs_rhs.push_back(prods);
        }

        productions[lhs_rhs[0][0]].insert(lhs_rhs[1]);

        for(int i = 0 ; i < temp.size(); i++)
        {
            if(isalpha(temp[i]) && temp[i] >= 65 && temp[i] <= 91)
                nonTerminals.insert(temp[i]);
            else
                terminals.insert(temp[i]);
        }
    }


    for(auto it : productions)
    {
        findFirst(it.first);
    }

    showDetails();

    return 0;
}