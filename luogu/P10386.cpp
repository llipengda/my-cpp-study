#include <bits/stdc++.h>

int main() {
    constexpr int n = 5;
    std::vector<std::vector<int>> v(n, std::vector<int>(n, 0));
    int cnt{};
    auto check = [&]() {
        int c{};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (v[i][j] == 1) {
                    c++;
                }
            }
        }
        if (c != 13) {
            return false;
        }
        for (int i = 0; i < n; i++) {
            c = 0;
            for (int j = 0; j < n; j++) {
                c += (v[i][j] == v[i][0]);
            }
            if (c == 5) {
                return false;
            }
        }
        for (int i = 0; i < n; i++) {
            c = 0;
            for (int j = 0; j < n; j++) {
                c += (v[j][i] == v[0][i]);
            }
            if (c == 5) {
                return false;
            }
        }
        c = 0;
        for (int i = 0; i < n; i++) {
            c += (v[i][i] == v[0][0]);
        }
        if (c == 5) {
            return false;
        }
        c = 0;
        for (int i = 0; i < n; i++) {
            c += (v[i][n - i - 1] == v[0][4]);
        }
        if (c == 5) {
            return false;
        }
        return true;
    };
    std::function<void(int, int)> dfs = [&](int x, int y) {
        if (y == n) {
            dfs(x + 1, 0);
            return;
        }
        if (x == n) {
            if (check()) {
                cnt++;
            }
            return;
        }
        v[x][y] = 1;
        dfs(x, y + 1);
        v[x][y] = 2;
        dfs(x, y + 1);
        v[x][y] = 0;
    };
    
    // dfs(0, 0);
    cnt = 3126376;
    std::cout << cnt << '\n';
}