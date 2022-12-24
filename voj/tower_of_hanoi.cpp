// 汉诺塔问题
#include <bits/stdc++.h>
using namespace std;
long long times(int n)
{
    if (n == 1)
        return 1;
    else
        return 2 * times(n - 1) + 1;
}
long long HP(int n)
{
    if (n == 1)
        return n;
    else
        return 2 * HP(n - 1) + n;
}
int main()
{
    int n;
    cin >> n;
    cout << times(n) << ' ' << HP(n);
}