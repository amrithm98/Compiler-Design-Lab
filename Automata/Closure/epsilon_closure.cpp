#include <bits/stdc++.h>
using namespace std;

class ENFA
{
    public:
        int num_states,num_alphabets;
        vector<int> finalStates;
        vector< vector< vector<int> > > table;
        vector< set<int> > closures;

        ENFA(int n_s, int n_a)
        {
            num_states = n_s;
            num_alphabets = n_a + 1;
            table = vector< vector < vector<int> > >(n_s,vector< vector<int> >(n_a+1,vector<int>(0)));
        }

        void get_nfa()
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
                finalStates.push_back(a);
            }
        }

        void printENFA()
        {
            cout << num_states << " " << num_alphabets << endl;
            for(int i = 0; i < num_states; i++)
            {
                for(int j = 0; j < num_alphabets; j++)
                {
                    cout << i <<  " " << j << " ";
                    for(int k = 0; k < table[i][j].size(); k++)
                        cout << table[i][j][k] << " ";
                    cout << endl;
                }
            }
        }

        set<int> compute_closure(int k)
        {
            set<int> closureSet;
            queue<int> pendingNodes;
            vector<bool> visited(num_states,false);

            pendingNodes.push(k);
            visited[k] = true;
            ofstream fout("out.txt");

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
};

int main()
{
    int n_s,n_a;
    cout << "\nEnter Number of States and alphabets: ";
    cin >> n_s >> n_a;

    ENFA enfa(n_s,n_a);
    enfa.get_nfa();

    for(int i = 0; i < enfa.num_states; i++)
    {
        set<int> res = enfa.compute_closure(i);
        printf("\n%d : ",i+1);

        for(auto it : res)
            cout << it+1 << " ";
        
        enfa.closures.push_back(res);
    }

    return 0;
}

