#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> v(n, vector<int>(n));
    vector<vector<int>> vis(n, vector<int>(n, 0));
    vector<vector<int>> dis(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> v[i][j];
        }
    }

    auto in = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < n;
    };

    queue<pii> q{};

    q.push({0, 0});
    dis[0][0] = 0;
    vis[0][0] = 1;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int ny = y + 1; ny < n; ny++) {
            if (v[x][ny] < v[x][ny - 1]) {
                if (!vis[x][ny]) {
                    q.push({x, ny});
                    vis[x][ny] = 1;
                    dis[x][ny] = dis[x][y] + 1;
                }
            } else {
                break;
            }
        }

        for (int ny = y - 1; ny >= 0; ny--) {
            if (v[x][ny] < v[x][ny + 1]) {
                if (!vis[x][ny]) {
                    q.push({x, ny});
                    vis[x][ny] = 1;
                    dis[x][ny] = dis[x][y] + 1;
                }
            } else {
                break;
            }
        }

        if (in(x + 1, y) && !vis[x + 1][y]) {
            q.push({x + 1, y});
            vis[x + 1][y] = 1;
            dis[x + 1][y] = dis[x][y] + 1;
        }

        if (in(x, y + 1) && !vis[x][y + 1]) {
            q.push({x, y + 1});
            vis[x][y + 1] = 1;
            dis[x][y + 1] = dis[x][y] + 1;
        }
    }

    cout << dis[n - 1][n - 1];
}