/*
HINT 题目描述
给定 n,m，请构造一个 n 点 m 边的 无向带权连通图，没有自环和重边，满足该图的最小生成树大小（生成树的边权和）等于节点 1 到节点 n 的最短路长度（路径的边权和）。
并限定所有边权是 1\to m 的排列。（即分配边权时 1\to m 中的每个数字只能用一次）
可以证明，对于任意满足本题数据范围的 n,m，均存在解。
HINT 输入描述:
多组数据，第一行输入一个正整数 1 ≤ T ≤ 10^5，表示数据的组数。
对于每组数据，一行输入两个整数 2 ≤ n ≤ 3•10^5, n-1 ≤ m ≤ min(n•(n-1)/2, 3•10^5)，以空格相隔。
对于 T 组数据，保证 ∑ n ≤ 3•10^5，∑ m ≤ 3•10^5。
HINT 输出描述:
对于每组数据：输出 m 行，第 i 行输出三个正整数 1 ≤ u_i ≤ n, 1 ≤ v_i ≤ n, 1 ≤ w_i ≤ m 以空格相隔，表示节点 u_i 与节点 v_i 存在一条边权为 w_i 的连边。
若有多组方案，输出任意一组方案。
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
    int n, m;
    cin >> n >> m;
    int cnt = 0;
    REP(j, 1, n - 1) {
        if (!m) break;
        REP(i, 1, n - 1) {
            if (!m) break;
            if (i + j > n)  break;
            cout << i << ' ' << i + j << ' ' << ++cnt << endl;
            m--;
        }
    }
}
int main()
{
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}