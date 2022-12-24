#include <bits/stdc++.h>
using namespace std;
int alpha[26];
int main()
{
    char ch;
    while (iswalpha(ch = getchar()))
        alpha[ch - 97]++;
    int max_num = *max_element(alpha, alpha + 26);
    for (int i = 0; i < 26; i++)
        if (alpha[i] == max_num){
            cout << (char)(i + 97) << ' ' << alpha[i] << endl;
            break;
        }
}