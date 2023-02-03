/*
链接：https://ac.nowcoder.com/acm/contest/46814/G
来源：牛客网
HINT 题目描述 
阿宁有一个长度为n的整数数组a，阿宁想要在其中选出恰好k对整数，使得每对整数相乘并求和尽可能大。
阿宁想知道最终得到的值是多少？
HINT 输入描述:
第一行两个整数 n,k。
第二行 n个整数 a_i。
2≤n≤2×10^5
1≤k≤⌊n/2⌋
−100≤a_i≤100 
HINT 输出描述:
输出一个整数，表示答案。
*/
#include <bits/stdc++.h>
#define endl '\n'
#define IO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
ll mul(vector<ll> num)
{
    if (num.size() >= 2)
        return num[0] * num[1];
    else
        return (ll)-10E17;
}
int main()
{
    int n, k, t;
    cin >> n >> k;
    vector<ll> po, ne, zero;
    while (n--) {
        cin >> t;
        if (t > 0)
            po.push_back(t);
        else if (t == 0)
            zero.push_back(t);
        else
            ne.push_back(t);
    }
    sort(po.begin(), po.end(), greater<ll>());
    sort(ne.begin(), ne.end());
    ll ans = 0;
    while (k--) {
        ll a = mul(po), b = mul(ne);
        if (a >= b && a > 0) {
            ans += a;
            po.erase(po.begin());
            po.erase(po.begin());
        } else if (a < b) {
            ans += b;
            ne.erase(ne.begin());
            ne.erase(ne.begin());
        } else {
            if (!zero.empty())
                zero.erase(zero.begin());
            else
                ans += *(po.begin()) * (*(ne.begin()));
        }
        cerr << a << ' ' << b << ' ' << ans << endl;
    }
    cout << ans;
}