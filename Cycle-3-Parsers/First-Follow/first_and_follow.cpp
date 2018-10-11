#include<bits/stdc++.h>
using namespace std;

set<char> terminals, nonTerminals;
map<char,set<string>> productions;
map<char,set<char>> first;
map<char,set<char>> follow;

set<string> visitedProductions;
set<char> visitedFollow;

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

    cout << "\nFollow : \n";
    for(auto it : follow)
    {
        cout << it.first << " : ";
        for(auto it1 : it.second)
        {
            if(it1 != '#')
                cout << it1 << " ";
        }
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

void findFollow(char c)
{
    // if(visitedFollow.find(c) != visitedFollow.end())
    //     return;
    
    cout << "\nFOllow of : " << c << endl;
    for(auto sets : productions)
    {
        for(auto it2 : sets.second)
        {
            if(visitedProductions.find(it2) == visitedProductions.end())
            {
                visitedProductions.insert(it2);
                for(int i = 0; i < it2.size(); i++)
                {
                    if(it2[i] == c)
                    {
                        if(i == it2.size()-1)
                        {
                            printf("\nFollow of %c is FOLLOW of %c",c,sets.first);
                            if(sets.first != c)
                            {
                                findFollow(sets.first);
                                follow[c].insert(follow[sets.first].begin(), follow[sets.first].end());
                            }
                        }
                        else if(i < it2.size()-1 && terminals.find(it2[i+1]) != terminals.end())
                        {
                            printf("\nFollow of %c Contains %c",c,it2[i+1]);
                            if(it2[i+1] != '#')
                                follow[c].insert(it2[i+1]);
                        }
                        else
                        {                            
                            printf("\nFollow of %c is FIRST of %c",c,it2[i+1]);
                            follow[c].insert(first[it2[i+1]].begin(), first[it2[i+1]].end());

                            //If First of It Contains Epsilon, find First of the next symbol
                            if(first[it2[i+1]].find('#') != first[it2[i+1]].end())
                            {
                                if(i < it2.size() - 2)
                                {
                                    follow[c].insert(first[it2[i+2]].begin(), first[it2[i+2]].end());
                                }
                                else //If i+2th symbol didn't exist, find follow of LHS
                                {
                                    findFollow(it2[i+1]);
                                    follow[c].insert(follow[it2[i+1]].begin(), follow[it2[i+1]].end());
                                }
                            }
                        }
                    }
                }
                visitedProductions.erase(it2);
            }
        }
    }

    // visitedFollow.insert(c);
}

int main()
{
    ifstream infile("productions.txt");

    string temp;

    // char start;
    // infile >> start;

    follow['E'].insert('$');

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

    for(auto it : nonTerminals)
    {
        findFollow(it);
    }

    for(auto it : follow)
    {
        if(it.second.find('#') != it.second.end())
            it.second.erase('#');
    }

    showDetails();

    return 0;
}