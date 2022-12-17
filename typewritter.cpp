#include <bits/stdc++.h>
using namespace std;
int main()
{
    string str = "";
    char ch;
    int t = 0;
    while (~(ch = getchar())) {
        t++;
        if (ch == '\n'){
            cout << str << endl;
            t = 0;
            str = "";
        }
        else if (ch == '[')
            t = 0;
        else if (ch == ']')
            t = str.length();
        else
            str.insert(str.begin() + t - 1, ch);
    }
}