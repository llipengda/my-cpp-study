#include "../helper/helper.h"

class Solution {
public:
    // BFS 不行
    double knightProbability(int n, int k, int row, int column) {
        constexpr int dx[] = {-1, -2, -2, -1, 1, 2, 2, 1};
        constexpr int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};
        auto check = [n](int x, int y) {
            return x >= 0 && x < n && y >= 0 && y < n;
        };
        std::vector<std::vector<std::vector<double>>> dp(k + 1, std::vector<std::vector<double>>(n, std::vector<double>(n, 0)));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[0][i][j] = 1;
            }
        }
        for (int d = 1; d <= k; d++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    for (int c = 0; c < 8; c++) {
                        int x = i + dx[c];
                        int y = j + dy[c];
                        if (check(x, y)) {
                            dp[d][i][j] += dp[d - 1][x][y] / 8;
                        }
                    }
                }
            }
        }
        return dp[k][row][column];
    }
};

int main() {
    int n, k, r, c;
    read(n, k, r, c);
    out(Solution().knightProbability(n, k, r, c));
}