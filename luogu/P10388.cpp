#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

ull rolling_hash(ull last, ull cur, ull base = 127) {
    return (last * base + cur);
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> v1(n + 1), v2(m + 1);
    // vector<int> vis1(n + 1, 0), vis2(m + 1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> v1[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> v2[i];
    }

    vector<vector<int>> t1(n + 1, vector<int>()), t2(m + 1, vector<int>());

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        t1[a].push_back(b);
        t1[b].push_back(a);
    }

    for (int i = 0; i < m - 1; i++) {
        int a, b;
        cin >> a >> b;
        t2[a].push_back(b);
        t2[b].push_back(a);
    }

    set<ull> paths;
    function<void(int, int, int, ull)> dfs1 = [&](int c, int p, int d, ull path) {
        // vis1[c] = 1;
        paths.insert(path);
        for (auto next : t1[c]) {
            if (next != p) {
                dfs1(next, c, d + 1, rolling_hash(path, v1[next]));
            }
        }
    };

    int mx = 0;
    function<void(int, int, int, ull)> dfs2 = [&](int c, int p, int d, ull path) {
        // vis2[c] = 1;
        if (paths.count(path)) {
            mx = max(mx, d);
        }
        for (auto next : t2[c]) {
            if (next != p) {
                dfs2(next, c, d + 1, rolling_hash(path, v2[next]));
            }
        }
    };

    dfs1(1, 0, 1, v1[1]);

    dfs2(1, 0, 1, v2[1]);

    cout << mx;
}