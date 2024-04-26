#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    using pii = pair<int, int>;
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> vis(m, vector<int>(n, 0));
        const int dx[] = {0, 0, -1, 1};
        const int dy[] = {-1, 1, 0, 0};
        auto bfs = [&](pii p) {
            queue<pii> q;
            q.push(p);
            vis[p.first][p.second] = 1;
            while (!q.empty()) {
                auto [tx, ty] = q.front();
                q.pop();
                for (int i = 0; i < 4; i++) {
                    int x = tx + dx[i];
                    int y = ty + dy[i];
                    if (x < 0 || y < 0 || x >= m || y >= n || vis[x][y] || grid[x][y] != '1') {
                        continue;
                    }
                    vis[x][y] = 1;
                    q.push({x, y});
                }
            }
        };
        int cnt = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1' && !vis[i][j]) {
                    cnt++;
                    bfs({i, j});
                }
            }
        }
        return cnt;
    }
};

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<char>> grid(m, vector<char>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    cout << Solution().numIslands(grid) << '\n';
}