#include <bits/stdc++.h>
using namespace std;
long long res[100];
int main()
{
    res[1] = 1;
    res[2] = 2;
    res[3] = 4;
    for (int i = 4; i <= 71; i++)
        res[i] = res[i - 3] + res[i - 2] + res[i - 1];
    while (1) {
        int in;
        cin >> in;
        if (in == 0)
            break;
        cout << res[in] << '\n';
    }
}