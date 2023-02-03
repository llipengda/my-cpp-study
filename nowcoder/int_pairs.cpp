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
int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> num(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> num[i];
    sort(num.begin() + 1, num.end());
    vector<ll> mul(2 * k + 1, 0);
    int j = 1;
    for (int i = 1; i < n; i += 2) {
        if (num[i] <= 0 && num[i + 1] <= 0)
            mul[j++] = num[i] * num[i + 1];
        if (j == k)
            break;
    }
    int tmp = (j - 1) * 2 + 1;
    for (int i = n; i > 1; i -= 2) {
        if (num[i] && num[i - 1] > 0)
            mul[j++] = num[i] * num[i - 1];
        if (j == 2 * k)
            break;
    }
    ll ans = 0;
    if (j < k + 1)
        ans += num[tmp] * num[tmp + 1];
    sort(mul.begin() + 1, mul.end(), greater<ll>());
    for (int i = 1; i <= k; i++)
        ans += mul[i];
    cout << ans << endl;
}