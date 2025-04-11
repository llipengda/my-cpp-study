#include <bits/stdc++.h>

int main() {
    std::string s{};
    std::cin >> s;

    int n = s.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

    for (int len = 1; len < n; len++) {
        for (int i = 0; i < n - 1; i++) {
            int j = i + len;
            if (j >= n) {
                continue;
            }
            if (s[i] > s[j]) {
                dp[i][j] = 1;
            } else if (s[i] < s[j]) {
                dp[i][j] = -1;
            } else {
                dp[i][j] = dp[i + 1][j - 1];
            }
        }
    }

    int cnt{};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cnt += dp[i][j] == 1;
        }
    }

    std::cout << cnt << '\n';
}