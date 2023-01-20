/*
链接：https://ac.nowcoder.com/acm/contest/46810/D
来源：牛客网
HINT 题目描述
Tokitsukaze 有 n 个节点的有根能量树，根为 1。最开始，树上每个节点的能量都是 0。
现在 Tokitsukaze 有 n 个能量球，第 i 个能量球拥有 v_i 能量。她想把这 n 个能量球分别放置在能量树的每个节点上，使能量树的每个节点都恰好有一个能量球。
Tokitsukaze 每次只能放置一个能量球，所以她将进行 n 次操作。每一次操作，她会选择一个能量球，再选择一个没有能量球的能量树节点 x，把刚刚选择的能量球放置在节点 x 上。在这之后，Tokitsukaze 能获得以 x 为根的子树中的所有能量球的能量 (包括节点 x 的能量球能量)。
在放置完所有能量球后，Tokitsukaze 可能获得的总能量最多是多少？
HINT 输入描述:
第一行包含一个整数 n (1 ≤ n ≤ 2⋅10^5)
第二行包含 n−1 个整数 f_2,f_3,…,f_n (1 ≤ f_i ≤i−1)，表示节点 i 的父亲是 f_i。
第三行包含 n 个整数 v_1,v_2,…,v_n (1 ≤ v_i ≤10^5)，分别表示能量球的能量。
HINT 输出描述:
输出一个整数，表示 Tokitsukaze 可能获得的最多总能量。
*/
//~ 获得的总能量相当于对每个节点的深度和该节点上能量的乘积求和
//~ 经典结论：若两个向量内部允许任意重排，则点积最大的方法为均升序排列
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
vector<int> tree[200005];
ll dep[200005], energy[200005];
void dfs(int now, int depth)
{
    dep[now] = depth;
    for (auto i : tree[now])
        dfs(i, depth + 1);
}
int main()
{
    int n;
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int t;
        cin >> t;
        tree[t].push_back(i);
    }
    for (int i = 1; i <= n; i++)
        cin >> energy[i];
    dfs(1, 1);
    sort(energy + 1, energy + n + 1);
    sort(dep + 1, dep + 1 + n);
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        ans += dep[i] * energy[i];
    cout << ans;
}