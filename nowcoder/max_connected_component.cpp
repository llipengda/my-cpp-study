/*
链接：https://ac.nowcoder.com/acm/contest/45670/E
来源：牛客网
HINT 题目描述
妈妈发现小竹逃走了，非常的气愤，她决定出去寻找小竹！和小竹不同的是，妈妈是道路上行走。
妈妈和小竹所在的城市有 n 个路口，n-1 条道路，并且保证任意两个路口互相联通。每个路口根据妈妈审美的不同都有一个优雅值，而如果两个相邻的路口的优雅值存在至少两个共同的质因子 p和 q (p != q) 则这两个相邻的路口就是共同优雅的。
妈妈将共同优雅联通块定义为：在城市中选取若干个路口，若这些路口们两两互相联通，且每两个相邻的路口都是共同优雅的，则该联通块称为共同优雅联通块。
注意：单独的一个路口也符合共同优雅联通块的定义。
妈妈想知道，整个城市的最大优雅联通块包含多少个路口。
HINT 输入描述
第一行一个正整数 n(1 ≤ n ≤ 10^6) 表示有 n 个路口。
第二行 n 个整数，第 i 个整数为 a_i(1≤ a_i≤ 5*10^6) 表示该路口的优雅值。
接下来 n-1 行，每行两个整数 x,y(1 ≤ x,y ≤ n) 表示 x 路口到 y 路口有一条道路。
HINT 输出描述
一行一个整数，表示最大优雅联通块包含多少个路口。
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
const int N = 1e6 + 5;
int pri[N * 5], npri[N * 5], d[N], a[N];
vector<int> road[N];
bool check(int t) {
    int cnt = 0;
    while (t != 1) {
        int mnp = npri[t];
        while (t % mnp == 0)     t /= mnp;
        cnt++;
    }
    return cnt >= 2;
}
void init_pri() {
    int cnt = 0;
    REP(i, 2, N * 5) {
        if (!npri[i]) {
            pri[++cnt] = i;
            npri[i] = i;
        }
        REP(j, 1, cnt) {
            if (i * pri[j] > 5 * N)   break;
            npri[i * pri[j]] = pri[j];
            if (i % pri[j] == 0)    break;
        }
    }
}
void dfs(int now, int father) {
    d[now] = 1;
    for (auto to : road[now]) {
        if (to == father)   continue;
        dfs(to, now);
        int t = __gcd(a[now], a[to]);
        if (check(t))
            d[now] += d[to];
    }
}
int main()
{
    init_pri();
    int n;
    cin >> n;
    REP(i, 1, n)  cin >> a[i];
    int x, y;
    REP(i, 1, n - 1) {
        cin >> x >> y;
        road[x].push_back(y);
        road[y].push_back(x);
    }
    dfs(1, -1);
    int ans = 0;
    REP(i, 1, n)
        ans = max(ans, d[i]);
    cout << ans;
}