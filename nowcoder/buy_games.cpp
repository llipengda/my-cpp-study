/*
链接：https://ac.nowcoder.com/acm/contest/45670/D
来源：牛客网
HINT 题目描述
小竹成功从家里逃了出来，他决定去小胖家避一避。但是小胖要求小竹带一个刺激度大于
x 的游戏才能去他家。
为了防止被妈妈或她的朋友发现，小竹不会在道路上行走，而是在建筑物与建筑物之间穿行。
街道表现为一个 n×m 的网格，网格上只有两种建筑:
商店和住宅。商店可以通过而住宅无法通过。
小竹每次从当前所在网格可以行走到上下左右的网格中，但不能移动到网格的边界之外和别人的家中。
正式的说，如果他在坐标为 (i,j) 的网格里，他可以选择
(i+1,j),(i,j+1),(i−1,j),(i,j−1) 四个方向行走。 在位置 (i,j)
上的商店有一个刺激度为
w_i,j的游戏，小竹可以购买他所经过的商店中的游戏并带走。若 w_i,j 为 −1
则代表这个位置是个住宅，无法通过。 注意：小胖家以及小竹家均可以被通过。
假设相邻的建筑物的距离均为 1，小竹想知道带一个刺激度高于 x
的游戏去小胖家需要的最短距离是多少？ 如果这是不可能实现的，请输出 −1。 HINT
输入描述: 第一行三个整数 n,m,x(1≤n,m≤2000,1≤x≤10^9)。
第二行四个整数sx,sy,ex,ey(1≤sx,ex≤n,1≤sy,ey≤m)
表示起点与终点的坐标，w_sx,sy,w_ex,ey均为0。 接下来 n 行，每行 m 个整数，第
i行第 j个整数 w_i,j(−1≤w_i,j≤10^9)，其中所有商店的 w_i,j≥1 。 HINT 输出描述:
一行一个整数，表示最短距离，若无法携带一个刺激度大于 x 的游戏到小胖家，输出-1。
*/
#include <bits/stdc++.h>
#define endl '\n'
#define IO ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
int w[2005][2005], visf[2005][2005], visb[2005][2005], disf[2005][2005], disb[2005][2005];
int dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };
int n, m, x;
void bfs(pii s, int w[][2005], int vis[][2005], int d[][2005])
{
    queue<pii> q;
    q.push(s);
    vis[s.first][s.second] = 1;
    d[s.first][s.second] = 0;
    while (!q.empty()) {
        pii u = q.front();
        q.pop();
        for (int i : { 0, 1, 2, 3 }) {
            int x = dx[i], y = dy[i];
            int nx = u.first + x, ny = u.second + y;
            if (!vis[nx][ny] && w[nx][ny] >= 0 && nx > 0 && nx <= n && ny > 0 && ny <= m) {
                q.push({ nx, ny });
                vis[nx][ny] = 1;
                d[nx][ny] = d[u.first][u.second] + 1;
            }
        }
    }
}
int main()
{
    memset(disf, 0x3f, sizeof(disf));
    memset(disb, 0x3f, sizeof(disb));
    cin >> n >> m >> x;
    int sx, sy, ex, ey;
    cin >> sx >> sy >> ex >> ey;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> w[i][j];
    bfs({ sx, sy }, w, visf, disf);
    bfs({ ex, ey }, w, visb, disb);
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (w[i][j] > x) {
                ans = min(ans, disf[i][j] + disb[i][j]);
            }
        }
    }
    if (ans == 0x3f3f3f3f)
        ans = -1;
    cout << ans;
}