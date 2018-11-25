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

#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <vector>
#include <fstream>
#include <algorithm>
#include <utility>
#include <string>
#include <sstream>
using namespace std;

//Must be declared First
class DFA
{
    public:
        int num_states, num_alphabets;
        vector< vector<int> > table;
        set<int> finalStates;

        DFA()
        {
            //Default Constructor
        }

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
                for(int j = 1; j < num_alphabets; j++)
                {   
                    printf("\ndelta(%d, %d): %d ",i+1,j,table[i][j]+1);
                }
            }

            printf("\nFinal States : { ");
            
            for(auto it : finalStates)
            {
                cout << it+1 << " ";
            }
            cout << "} \n";    
        }

        /***
         * 
         * Minimise DFA using Myhill-Nerode THeorem
         * 
         * */

        int find(vector<int> &parent, int x, set<int> &path)
        {
            path.insert(x);
            if(x != parent[x])
            {
                return find(parent,parent[x],path);
            }
            else 
            {
                return x;
            }
        }

        int find(int x,vector<int> &parent)
        {
            if(x == parent[x])
            {
                return x;
            }
            else
            {
                parent[x] = find(parent[x],parent);
                return parent[x];
            }
        }

        DFA minimizeDFA()
        {
            DFA minDfa(0,num_alphabets);
            vector< vector<int> > m(num_states, vector<int> (num_states,0));

            bool f = 1;
            for(int i = 0; i < num_states; i++)
            {
                for(int j = i + 1 ; j < num_states; j++)
                {
                    if(finalStates.find(i) != finalStates.end() && finalStates.find(j) == finalStates.end())
                    {
                        m[i][j] = 1;
                    }
                    
                    if(finalStates.find(j) != finalStates.end() && finalStates.find(i) == finalStates.end())
                    {
                        m[i][j] = 1;
                    }
                }
            }

            cout << "\nM-N Table(Initial) : \n";
            for(int i = 0; i < num_states; i++)
            {
                for(int j = i + 1 ; j < num_states; j++)
                    cout << m[i][j] << " ";
                cout << endl; 
            }


            while(f)
            {
                f = 0;

                for(int i = 0; i < num_states; i++)
                {
                    for(int j = i + 1; j < num_states; j++)
                    {
                        for(int u = 1; u < num_alphabets; u++)
                        {
                            int i_u = table[i][u];
                            int j_u = table[j][u];

                            if(i_u > j_u)   
                                swap(i_u,j_u);

                            if(m[i][j] == 0 && m[i_u][j_u] == 1)
                            {
                                m[i][j] = 1;
                                f = 1;
                                break;
                            }
                        }
                    }
                }
            }

            cout << "\nM-N Table : \n";
            for(int i = 0; i < num_states; i++)
            {
                for(int j = i + 1 ; j < num_states; j++)
                    cout << m[i][j] << " ";
                cout << endl; 
            }

            set<int> visited, unvisited;
            set<int> fs;

            vector<int> parent(num_states);
            for(int i = 0; i < num_states; i++)
            {
                parent[i] = i;
            }

            for(int i = 0; i < num_states; i++)
            {
                for(int j = i+1 ; j < num_states; j++)
                {
                    if(m[i][j] == 0)
                    {
                        parent[j] = i;
                    }
                }
            }
            
            map<int, set<int> > mappings;

            for(int i = 0; i < num_states; i++)
            {
                set<int> path;
                int x = find(parent,i,path);
                mappings[x] = path;
            }
            
            cout << "\nEquivalent States : \n";
            for(auto it : mappings)
            {
                cout << it.first << " : ";
                for(auto it1 : it.second)
                    cout << it1 << " ";
                cout << endl;
            }

            minDfa.num_states = mappings.size();
            minDfa.table = vector<vector<int>>(num_states,vector<int>(num_alphabets));

            map<int,int> numberMap;
            int index = 0;

            for(auto it : mappings)
            {
                numberMap[it.first] = index++;
            }

            for(auto it : mappings)
            {
                for(int j = 1; j < num_alphabets; j++)
                {
                    int start = *(it.second.begin());
                    int end = table[start][j];
                    int parent_element = find(end,parent);

                    minDfa.table[numberMap[it.first]][j] = numberMap[parent_element];
                }
            }

            for(auto it : finalStates)
            {
                minDfa.finalStates.insert(numberMap[find(it,parent)]);
            }
                        
            return minDfa;
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
                    if(table[i][j].size() != 0)
                    {
                        printf("\ndelta(%d,%d): { ",i,j);
                        for(int k = 0; k < table[i][j].size(); k++)
                            cout << table[i][j][k] << " ";
                        cout << "} ";
                    }
                    
                }
            }
            printf("\nFinal States : { ");
            for(auto it : finalStates)
                cout << it << " ";
            cout << "}";            
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
         * 
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
         * Gets a set of states corresponing to a dfa state
         * 
         * */

        set<int> nfa_state(int st)
        {
            st++;
            set<int> states;
            int i = 31;

            while(i >= 0)
            {
                if(st & (1 << i))
                    states.insert(i);
                i--;
            }                
            return states;
        }

        /**
         * Gets an integer that represents a set of states of an nfa
         * */

        int dfa_state(set<int> states)
        {

            int reqState = 0;
            for(auto it : states)
            {
                reqState += (int)pow(2,it);
            }

            return reqState - 1;
        }

        /**
         * 
         * Only objects of NFA format is allowed to invoke this function
         * SUBSET CONSTRUCTION O(n.2^n)
         * 
         * */

        DFA convert_to_dfa()
        {   
            int dfa_states = (int)pow(2,num_states);
            DFA dfa(dfa_states, num_alphabets);

            for(int i = 0; i < dfa_states-1; i++)
            {
                set<int> states_in_nfa = nfa_state(i);
                    
                for(int j = 1; j < num_alphabets; j++)
                {
                    vector<int> states;
                    for(auto it : states_in_nfa)
                    {
                        states.insert(states.end(),table[it][j].begin(),table[it][j].end());
                    }

                    set<int> f(states.begin(),states.end());
                    if(f.empty())
                        dfa.table[i][j] = dfa_states - 1;
                    else
                    {
                        dfa.table[i][j] = dfa_state(f);
                    }
                }   
            }

            //Dead State Config
            for(int j = 1; j < num_alphabets; j++)
                dfa.table[(1 << num_states) - 1][j] = (1 << num_states) - 1;


            /***
             * Generate Final states
             * Get all subsets that contain any of the final states of the nfa
             * 
             * */
            
            set<int> actualFinal;
            for(int i = 0; i < dfa_states-1; i++)
            {
                set<int> fs = nfa_state(i);
                for(auto it : finalStates)
                {
                    if(fs.find(it) != fs.end())
                    {
                        actualFinal.insert(i);
                    }
                }
            }

            dfa.finalStates = actualFinal;

            //dfa.printAutomaton();

            /**
             * Doing BFS To optimse state Count
             * Collecting all states that has a path from the start state and mapping them from 0 to size
             * 
             * */

            queue<int> q;
            vector<bool> visited(dfa_states,0);

            q.push(0);
            visited[0] = 1;

            vector< int > req_states;
            int new_state_count = 0;

            while(!q.empty())
            {
                int curr = q.front();
                q.pop(); 

                req_states.push_back(curr);

                new_state_count++;

                for(int i = 1; i < num_alphabets; i++)
                {
                    int next = dfa.table[curr][i];
                    if(!visited[next])
                    {
                        visited[next] = 1;
                        q.push(next);

                    }
                }
            }

            printf("\nNumber of States in BFS Optimised DFA is : %d \n",new_state_count);

            //Mapping Arbitrary states to 0 - n
            
            unordered_map<int,int> mappings;
            int index = 0;
            for(auto it : req_states)
            {
                if(mappings.find(it) == mappings.end())
                {
                    mappings[it] = index++;
                }
            }

            DFA optimised(index,num_alphabets);

            for(auto it : req_states)
            {
                for(int i = 1; i < num_alphabets; i++)
                {
                    optimised.table[mappings[it]][i] = mappings[dfa.table[it][i]];
                }
            }

            for(auto it : dfa.finalStates)
            {
                if(mappings.find(it) != mappings.end())
                    (optimised.finalStates).insert(mappings[it]);
            }


            /**
             * 
             * Print Without Mapping. (states will get weird numbers)
             * 
             * */

            /*

            for(auto it : req_states)
            {
                for(int i = 1; i < num_alphabets; i++)
                {
                    printf("\ndelta(%d,%d): %d ",it,i,dfa.table[it][i]);
                }
            }
            cout << "\nFinal : ";
            for(auto it : req_states)
                if(dfa.finalStates.find(it) != dfa.finalStates.end())
                    cout << it << " ";

            cout << endl;

            */

            return optimised;
        }

        /***
         * 
         * Converts NFA to DFA using Lazy Construction
         * Creates a new state only if there is a path to it
         * 
         * */

        DFA convert_to_dfa_lazy()
        {
            DFA dfa(0, num_alphabets);

            vector < set<int> > lazySet;

            int i = 0;

            lazySet.push_back({0});

            dfa.table.push_back(vector<int>(num_alphabets,-1));
            
            if(finalStates.find(0) != finalStates.end())
                dfa.finalStates.insert(0);

            while(i < lazySet.size())
            {
                for(int j = 1; j < num_alphabets; j++)
                {
                    int new_state = -1;

                    set<int> reachable;
                    for(auto it : lazySet[i])
                    {
                        reachable.insert(table[it][j].begin(),table[it][j].end());
                    }

                    
                    for(int x = 0; x < lazySet.size(); x++)
                    {
                        if(reachable == lazySet[x])
                        {
                            new_state = x;
                            break;
                        }
                    }

                    if(new_state == -1)
                    {
                        new_state = lazySet.size();
                        lazySet.push_back(reachable);

                        for(auto it : reachable)
                        {
                            if(finalStates.find(it) != finalStates.end())
                            {
                                dfa.finalStates.insert(new_state);
                                break;
                            }
                        }

                        dfa.table.push_back(vector<int>(num_alphabets,-1));

                    }

                    dfa.table[i][j] = new_state;
                }

                i++;
            }

            dfa.num_states = dfa.table.size();
            return dfa;
        }

};



int main()
{
    int n_s,n_a;
    cin >> n_s >> n_a;

    ENFA enfa(n_s,n_a + 1);
    enfa.get_automaton();

    cout << "\n\nProblem - 1 : Epsilon Closure of e-nfa\n========================================\n";

    for(int i = 0; i < enfa.num_states; i++)
    {
        set<int> res = enfa.compute_closure(i);
        printf("\n%d : { ",i);

        for(auto it : res)
            cout << it << " ";
        cout << " }";

        enfa.closures.push_back(res);
    }

    cout << "\n\nProblem - 2 : Generating NFA  \n==============================\n";
    ENFA nfa = enfa.convert_to_nfa();
    nfa.printAutomaton();

    cout << "\n\nProblem - 3 : Generating DFA  \n==============================\n";
    DFA dfa = nfa.convert_to_dfa_lazy();
    dfa.printAutomaton();

    cout << "\n\nProblem - 4 : Generating Minimised DFA  \n========================================\n";
    DFA min_dfa = dfa.minimizeDFA();
    min_dfa.printAutomaton();

    return 0;
}