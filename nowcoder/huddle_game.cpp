/*
链接：https://ac.nowcoder.com/acm/contest/46813/L
来源：牛客网
HINT 题目描述
小沙在玩一个抱团游戏，最开始有 n 个人，每次小沙有 m 条指令可以下达，对于第 i 条指令可以花费 b_i​ 的代价，要求以 x_i​ 人为单位抱团，每个人只能在一个团里，若一个人不属于某一个恰好 x_i​ 个人的团则将被淘汰，抱团需要所有参与抱团的人全部同意。
假设参加游戏的人都足够聪明，都希望自己不被淘汰。
如果你是小沙，你最少需要花费多少的代价才能使得剩余的人数最少。
每个指令都可以重复使用。
每次要求拥抱人数不能超过当前人数。
例：剩余 5 人时不能要求 6 个人拥抱在一起。
HINT 输入描述:
第一行输入二个整数 n, m, 代表人数以及指令个数，1≤n≤10^5, 1≤m≤500。
随后 m 行，每行两个整数 b_i​, x_i​, 分别代表代价以及指令的内容，1≤b_i​≤10^5, 2≤x_i​≤10^5 。
HINT 输出描述:
输出一个整数代表小沙最少花费的代价。
*/
#include <bits/stdc++.h>
#define endl '\n'
#define IO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
int n, m, b[100005], x[100005], dp[505];
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> b[i] >> x[i];
    memset(dp, 0x3f3f3f3f, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        bool flag = true;
        for (int j = 1; j <= m; j++) {
            if (x[j] < i) {
                int k = i - i % x[j];
                dp[i] = min(dp[i], dp[k] + b[j]);
                flag = false;
            }
        }
        if (flag)
            dp[i] = 0;
    }
    cout << dp[n] << endl;
}