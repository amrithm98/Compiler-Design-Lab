#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Stack
{
    public:
        vector<T> st;

        Stack()
        {

        }

        bool empty()
        {
            return st.size() == 0;
        }

        T top()
        {
            if(st.empty())
                return -1;
            else   
                return st[st.size()-1];
        }

        void pop()
        {
            if(st.empty())
            {
                return;
            }
            else
                st.pop_back();
        }

        void push(T data)
        {
            st.push_back(data);
        }

        void print()
        {
            for(int i = 0; i < st.size(); i++)
                cout << st[i] << " ";
        }
};