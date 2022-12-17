#include <bits/stdc++.h>
using namespace std;
int main()
{
    list<char> str;
    char ch;
    auto t = str.begin();
    while (~(ch = getchar())) {
        if (ch == '\n'){
            for(auto i : str)
                cout << i;
            cout << '\n';
            str.clear();
            t = str.begin();
        }
        else if (ch == '[')
            t = str.begin();
        else if (ch == ']')
            t = str.end();
        else
            str.insert(t, ch);
    }
}