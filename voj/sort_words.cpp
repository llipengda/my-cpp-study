#include <bits/stdc++.h>
using namespace std;
vector<string> words;
int main()
{
    string tmp;
    while(cin>>tmp)
        words.push_back(tmp);
    sort(words.begin(),words.end());
    words.erase(unique(words.begin(),words.end()),words.end());
    for (auto i:words)
        cout<<i<<endl;
}