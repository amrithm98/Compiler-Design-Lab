/****
 * 
 * Author : Amrith M
 * Problem : Problems 1-4 In Cycle 1
 * Description : Converts an epsilon-nfa to a minimised dfa
 * 
 * Class ENFA represents objects of both epsilon-nfa and nfa 
 * Class DFA represents objects of both dfa and minimised dfa
 * 
 * Closure is found using Breadth First Search
 * After computing closure of every state, they're stored in closures vector
 * 
 * 
 * 
 * */

#include <bits/stdc++.h>
using namespace std;

//Must be declared First
class DFA
{
    public:
        int num_states, num_alphabets;
        vector< vector<int> > table;
        set<int> finalStates;

        DFA(int n_s,int n_a)
        {
            num_states = n_s;
            num_alphabets = n_a;
            table = vector< vector<int> >(n_s, vector<int>(n_a));
        }

        void printAutomaton()
        {
            printf("\nStates : %d, Alphabet : %d \n",num_states,num_alphabets-1);
            for(int i = 0; i < num_states; i++)
            {
                for(int j = 0; j < num_alphabets; j++)
                {
                    printf("\ndelta(%d,%d): %d ",i,j+1,table[i][j]);
                }
            }
            printf("\nFinal States : { ");
            for(auto it : finalStates)
                cout << it << " ";
            cout << "} \n";            
        }

        void minimizeDFA()
        {

        }

};

class ENFA
{
    public:
        int num_states, num_alphabets;
        set<int> finalStates;
        vector< vector< vector<int> > > table;
        vector< set<int> > closures;

        ENFA(int n_s, int n_a)
        {
            num_states = n_s;
            num_alphabets = n_a;
            table = vector< vector < vector<int> > >(n_s,vector< vector<int> >(n_a,vector<int>(0)));
        }

        /**
         * Reads only transitions that exist and has the format :
         * state symbol transitions
         * Eg : 0 1 1 2 3 => delta(0,1) = { 1 2 3}
         * 
         * */

        void get_automaton()
        {
            while(true)
            {
                string s;
                getline(cin,s);
                if(s[0] == 'x')
                    break;

                stringstream ss(s);
                vector<int> arr;

                while(ss)
                {
                    string temp;
                    if(getline(ss,temp,' '))
                    {
                        arr.push_back(stoi(temp));
                    }
                    else
                        break;
                }

                for(int i = 2; i < arr.size(); i++)
                {
                    (table[arr[0]][arr[1]]).push_back(arr[i]);
                }
            }

            int x;
            cin >> x;
            for(int i = 0; i < x; i++)
            {
                int a;
                cin >> a;
                finalStates.insert(a);
            }
        }

        /**
         * Prints the transition function of the automaton
         * 
         * 
         * */

        void printAutomaton()
        {
            printf("\nStates : %d, Alphabet : %d \n",num_states,num_alphabets-1);
            for(int i = 0; i < num_states; i++)
            {
                for(int j = 0; j < num_alphabets; j++)
                {
                    printf("\ndelta(%d,%d): { ",i,j);
                    for(int k = 0; k < table[i][j].size(); k++)
                        cout << table[i][j][k] << " ";
                    cout << "} " << endl;
                }
            }
            printf("\nFinal States : { ");
            for(auto it : finalStates)
                cout << it << " ";
            cout << "} \n";            
        }

        /***
         * 
         * Computes Closure using Breadth First Search
         * 
         * 
         * */

        set<int> compute_closure(int k)
        {
            set<int> closureSet;
            queue<int> pendingNodes;
            vector<bool> visited(num_states,false);

            pendingNodes.push(k);
            visited[k] = true;

            while(!pendingNodes.empty())
            {
                int node = pendingNodes.front();
                pendingNodes.pop();

                closureSet.insert(node);

                for(int i = 0; i < (table[node][0]).size(); i++)
                {
                    int x = table[node][0][i];
                    if(!visited[x])
                    {
                        pendingNodes.push(x);
                        closureSet.insert(x);
                    }
                }
            }

            return closureSet;
        }

        /****
         * 
         * Converts ENFA to NFA using the standard algorithm.Updates final states also.
         * returns and object of ENFA which represents the requied nfa.
         * */

        ENFA convert_to_nfa()
        {
            ENFA nfa(num_states,num_alphabets);
            nfa.finalStates = finalStates;

            for(int i = 0; i < num_states; i++)
            {
                set<int> closure = closures[i];
                for(int j = 1; j < num_alphabets; j++)
                {
                    vector<int> states;
                    for(auto it : closure)
                    {
                        states.insert(states.end(),table[it][j].begin(),table[it][j].end());
                    }

                    set<int> stateSet(states.begin(),states.end());
                    set<int> resultant;

                    //Computing e-closure of this set w.r.t ENFA this
                    for(auto it : stateSet)
                    {
                        resultant.insert(closures[it].begin(),closures[it].end());
                    }

                    vector<int> finalAns(resultant.begin(),resultant.end());

                    nfa.table[i][j] = finalAns;
                }
            }

            for(auto it : finalStates)
            {
                for(int i = 0; i < num_states; i++)
                {
                    if(closures[i].find(it) != closures[i].end())
                    {
                        nfa.finalStates.insert(i);
                    } 
                }
            }
            return nfa;
        }

        /**
         * 
         * Only objects of NFA format is allowed to invoke this function
         * 
         * */

        DFA convert_to_dfa()
        {
            DFA Ba(0,0);
            return Ba;
        }
};

int main()
{
    int n_s,n_a;
    cin >> n_s >> n_a;

    ENFA enfa(n_s,n_a + 1);
    enfa.get_automaton();

    cout << "\nProblem - 1 : Epsilon Closure of e-nfa\n========================================\n";

    for(int i = 0; i < enfa.num_states; i++)
    {
        set<int> res = enfa.compute_closure(i);
        printf("\n%d : { ",i+1);

        for(auto it : res)
            cout << it+1 << " ";
        cout << " }";
        enfa.closures.push_back(res);
    }

    cout << "\n\nProblem - 2 : Generating NFA  \n==============================\n";
    ENFA nfa = enfa.convert_to_nfa();
    nfa.printAutomaton();

    cout << "\n\nProblem - 3 : Generating DFA  \n==============================\n";
    DFA dfa = nfa.convert_to_dfa();


    return 0;
}

