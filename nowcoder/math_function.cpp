/*
HINT题目描述
Tokitsukaze 有一个函数
f(x)= floor(n/x)+x-1
她想在区间 [L,R] 中找到一个**最小**的整数 t，使函数 f(t) 的值最小。
HINT输入描述:
第一行包含一个整数 T (1 ≤ T ≤ 2·10^5)，表示测试数据组数。
每组测试数据包含三个整数 n, L, R (1 ≤ n ≤ 10^18; 1 ≤ L ≤ R ≤ 10^18)。
HINT输出描述:
对于每组测试数据，输出最小的 t (L ≤ t ≤ R)，使 f(t) 的值最小。
*/
#include <bits/stdc++.h>
#define endl '\n'
#define IO ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
#define REP(i, a, b) for (int i = a; i <= b; i++)
#define PER(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
void solve() {
    ll n, l, r;
    cin >> n >> l >> r;
    ll pos = l;
    ll minn = n / l + l - 1;
    if (n / r + r - 1 < minn) {
        pos = r;
        minn = n / r + r - 1;
    }
    ll x = sqrt(n);
    if (l <= x && x <= r && n / x + x - 1 < minn) {
        pos = x;
        minn = n / x + x - 1;
    }
    x++;
    if (l <= x && x <= r && n / x + x - 1 < minn) {
        pos = x;
        minn = n / x + x - 1;
    }
    while (l < pos) {
        ll mid = (l + pos) / 2;
        if (n / mid + mid - 1 == minn) {
            pos = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << pos << endl;
}
int main()
{
    IO;
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}