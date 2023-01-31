/*
链接：https://ac.nowcoder.com/acm/contest/46812/C
来源：牛客网
HINT 题目描述
现在清楚姐姐有N个蝴蝶结，第i个蝴蝶结的体积为wi，好看程度为vi​，她准备了一个容量大小为M的包包。
她可以从这N个蝴蝶结中任选若干个放入背包，但是所选蝴蝶结的体积总和不能大于背包的容量M，清楚姐姐想要让所选蝴蝶结的好看程度总和最大化。
她运用自己刚刚学会的01背包知识，快速算出了她能用她的包包装下蝴蝶结好看程度总和的最大值。
现在清楚姐姐有了一个新的问题，我们定义原问题的答案，即所选蝴蝶结好看程度总和的最大值为 Valmax
定义从这N个蝴蝶结中去掉第i个蝴蝶结后，从剩余N−1个蝴蝶结中任选若干个放入背包，所选蝴蝶结好看程度总和的最大值为Vali′
若Vali′<Valmax ，则称第i个蝴蝶结为一个“必选蝴蝶结”。
清楚姐姐现在获得了调整蝴蝶结好看程度的机会，她想要知道，对于第i个蝴蝶结，在它初始好看程度的基础上，再加上多少，该蝴蝶结就能够成为一个“必选蝴蝶结”。
HINT 输入描述:
第一行输入两个正整数 N,M (1≤N,M≤100(5000 in hard version))。
接下来N行，每行输入两个正整数 wi ,vi (1≤wi≤M,vi≤10^9)表示每个蝴蝶结的体积以及好看程度
HINT 输出描述:
输出N行，每行一个整数，第i行表示在它初始好看程度的基础上，再加上多少，该蝴蝶结就能够成为一个“必选蝴蝶结”。特别的，如果该蝴蝶结已经是一个“必选蝴蝶结”，则输出0。
*/
#include <bits/stdc++.h>
#define N 5010
typedef long long ll;
using namespace std;
ll dpz[N][N], dpf[N][N], w[N], v[N], maxz[N], maxf[N];
ll n, m;
void _dp(ll dp[][N])
{
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= m; j++)
            if (j - w[i] >= 0)
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
            else
                dp[i][j] = dp[i - 1][j];
}
int main()
{
    cin >> n >> m;
    for (ll i = 1; i <= n; i++)
        cin >> w[i] >> v[i];
    _dp(dpz);
    reverse(w + 1, w + n + 1);
    reverse(v + 1, v + n + 1);
    _dp(dpf);
    reverse(w + 1, w + n + 1);
    reverse(v + 1, v + n + 1);
    for (ll i = 1; i <= n; i++) {
        memset(maxz, 0, sizeof(maxz));
        memset(maxf, 0, sizeof(maxf));
        for (ll j = 1; j <= m; j++) {
            maxz[j] = max(maxz[j - 1], dpz[i - 1][j]);
            maxf[j] = max(maxf[j - 1], dpf[n - i][j]);
        }
        ll Vmx = 0, Vmxi = 0;
        for (ll j = 0; j <= m; j++) {
            Vmx = max(Vmx, maxz[j] + maxf[m - j]);
            if (m - j - w[i] >= 0) {
                Vmxi = max(Vmxi, maxz[j] + maxf[m - j - w[i]] + v[i]);
                Vmxi = max(Vmxi, maxf[j] + maxz[m - j - w[i]] + v[i]);
            }
        }
        cout << max(0ll, Vmx - Vmxi + 1ll) << endl;
    }
}