// 走迷宫问题
#include <bits/stdc++.h>
using namespace std;
char map_in[15][15]; // 存储地图
int direction[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } }; // 可以走的方向（右上左下）
int cnt; // 路径数量
int m, n; // 地图边界
int startx, starty; //(startx,starty)为起点的坐标
void dfs(int x, int y)
{
    if (map_in[x][y] == 'T') {
        cnt++;
        return;
    }
    map_in[x][y] = '#'; // 标记为已访问
    for (int i = 0; i < 4; i++) { // 向四周探索
        int tx = x + direction[i][0];
        int ty = y + direction[i][1];
        if ((tx < m && ty < n && tx >= 0 && ty >= 0) && map_in[tx][ty] != '#') // 可访问且不越界
            dfs(tx, ty);
    }
    map_in[x][y] = '.';
}
int main()
{
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map_in[i][j];
            if (map_in[i][j] == 'S') {
                startx = i;
                starty = j;
                map_in[i][j] = '.';
            }
        }
    }
    dfs(startx, starty);
    cout << cnt;
}