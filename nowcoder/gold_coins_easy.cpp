/*
HINT 题目描述
easy 与 hard 的唯一区别是输出内容。
 Tokitsukaze 喜欢 Rune Factory 系列。
 在游戏中有一个 n * 3 的迷宫，迷宫的起点是 (1,1)，迷宫的终点是 (n,3)，每个格子都有一条向下和一条向右的**单向**道路，也就是说如果你当前站在 (x,y)，你只能前往 (x+1,y) 或者 (x,y+1)。
 在迷宫的起点设有离开迷宫的出口，玩家可以通过出口安全的离开迷宫。
 在迷宫的终点处设有一个传送门，玩家通过传送门回到迷宫的起点，玩家可以选择继续探索迷宫，也可以选择从迷宫入口退出迷宫。作为探索迷宫的奖励，在这个迷宫中除了迷宫起点 (1,1) ，每个格子都存在 1 金币，但某些格子存在守护金币的怪物，若玩家被怪物打败，玩家会被强制结束探索，接着被送进医院并且会支付 10^9 金币的医疗费。请注意，玩家通过传送门多次探索迷宫，每个格子的金币也只能获取一次。
 现在 Tokitsukaze 正在迷宫的起点准备探索迷宫。她会拿走她经过的所有格子上的金币（如果金币存在）。但是她目前的战斗力打不过迷宫中的任何怪物，因此她不会进入存在怪物的格子。为了使探索收益最大化，她会多次探索迷宫，在不被怪物打死的情况下，获取尽可能多的收集金币。
 Tokitsukaze 注意到她只能在迷宫的起点处离开迷宫，一旦探索开始离开迷宫起点，直到下一次回到迷宫的起点处之前都**不能离开迷宫**。
 根据游戏机制，迷宫会有 k 次变化。最开始迷宫中没有怪物，第 i 次变化将会改变格子 (x_i,y_i) 的怪物状态。即若 (x_i,y_i) 中没有怪物，则怪物会出现，否则怪物会消失。保证起点和终点不会出现怪物。
 Tokitsukaze 将会在第 k 次变化之后进入迷宫，她想知道她能获得的金币数量最大是多少。
HINT 输入描述:
第一行包含一个正整数 T (1 ≤T ≤5·10^5)，表示测试数据的组数。
对于每组测试数据：
第一行包含两个正整数 n, k (1 ≤n,k ≤5·10^5)，表示迷宫的大小是 n * 3，变化的次数为 k 次。
接下来 k 行，每行两个正整数 x_i, y_i (1 ≤x_i ≤n; 1 ≤y_i ≤3)，若 (x_i,y_i) 中没有怪物，则怪物出现，否则怪物消失。保证没有 (x_i,y_i) 与 (1,1) 或者 (n,3) 相同。
保证 ∑ n 和 ∑ k 都不超过 5·10^5。
HINT 输出描述:
对于每组数据，输出一个整数，表示 Tokitsukaze 在第 k 次变化之后进入迷宫，能获得的金币最大数量。
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
const int N = 5e5 + 5;
int n, k;
pii dxb[] = { {1,0} ,{0,1} };
pii dxf[] = { {-1,0} ,{0,-1} };
void bfs(vector<vector<int>>& m, pii start, vector<vector<int>>& vis, pii dx[]) {
    queue<pii> q;
    q.push(start);
    vis[start.first][start.second] = 1;
    while (!q.empty()) {
        pii tmp = q.front();
        q.pop();
        REP(i, 0, 1) {
            int x = tmp.first + dx[i].first, y = tmp.second + dx[i].second;
            if (x > 0 && x <= n && y > 0 && y <= 3 && !vis[x][y] && !m[x][y]) {
                q.push({ x,y });
                vis[x][y] = 1;
            }
        }
    }
}
void solve() {
    cin >> n >> k;
    vector<vector<int>> m(n + 1, vector<int>(4, 0));
    vector<vector<int>> visb(n + 1, vector<int>(4, 0));
    vector<vector<int>> visf(n + 1, vector<int>(4, 0));
    while (k--) {
        int xi, yi;
        cin >> xi >> yi;
        m[xi][yi] = !m[xi][yi];
    }
    bfs(m, { 1,1 }, visb, dxb);
    bfs(m, { n,3 }, visf, dxf);
    int ans = 0;
    REP(i, 1, n) {
        REP(j, 1, 3) {
            ans += (visb[i][j] && visf[i][j]);
        }
    }
    ans--;
    if (ans < 0) ans = 0;
    cout << ans<< endl;
}
int main()
{
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}