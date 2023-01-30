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
第一行输入两个正整数N,M(1≤N,M≤100)。
接下来
N行，每行输入两个正整数 wi ,vi (1≤wi≤M,vi≤10^9)表示每个蝴蝶结的体积以及好看程度
HINT 输出描述:
输出N行，每行一个整数，第i行表示在它初始好看程度的基础上，再加上多少，该蝴蝶结就能够成为一个“必选蝴蝶结”。特别的，如果该蝴蝶结已经是一个“必选蝴蝶结”，则输出0。
*/
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll dp[105][105], v[105], b[105], mb[105], res[105];
ll N, M;
ll sum(ll i)
{
    ll ans = 0;
    for (int j = 1; j <= N; j++)
        if (j != i)
            ans += b[j];
    return ans;
}
void _dp()
{
    //~ dp
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            if (j >= v[i])
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - v[i]] + b[i]);
            else
                dp[i][j] = dp[i - 1][j];
}
int main()
{
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
        cin >> v[i] >> b[i];
    _dp();
    mb[0] = dp[N][M];
    for (int k = 1; k <= N; k++) {
        v[102] = v[k];
        b[102] = b[k];
        v[k] = b[k] = 0;
        _dp();
        mb[k] = dp[N][M];
        v[k] = v[102];
        b[k] = b[102];
    }
    for (int l = 1; l <= N; l++) {
        if (mb[0] > mb[l])
            cout << 0 << endl;
        else {
            b[103] = b[l];
            mb[103] = mb[0];
            //~ 二分查找
            ll left = b[l], right = sum(l) + 1;
            while (left < right) {
                ll mid = left + (right - left) / 2;
                b[l] = mid;
                _dp();
                if (dp[N][M] <= mb[l])
                    left = mid + 1;
                else
                    right = mid;
            }
            cout << left - b[103] << endl;
            b[l] = b[103];
            mb[0] = mb[103];
        }
    }
}