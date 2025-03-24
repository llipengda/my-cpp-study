#include "../helper/helper.h"

class Solution {
public:
    vector<vector<int>> differenceOfDistinctValues(vector<vector<int>>& grid) {
        int m = grid.size(); // auto -> usize!!!!!
        int n = grid[0].size();
        std::vector<std::unordered_set<int>> sets(n);
        std::vector<std::vector<int>> tl(m, std::vector<int>(n, 0));
        std::vector<std::vector<int>> br(m, std::vector<int>(n, 0));
        auto test_set = [&](int x, int y, auto&& vec, int v) {
            if (x >= 0 && x < m && y >= 0 && y < n) {
                vec[x][y] = v;
            }
        };
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                auto& st = sets[((j - i) % n + n) % n];
                if (!st.count(grid[i][j])) {
                    test_set(i + 1, j + 1, tl, tl[i][j] + 1);
                } else {
                    test_set(i + 1, j + 1, tl, tl[i][j]);
                }
                if (j == n - 1) {
                    st.clear();
                } else {
                    st.insert(grid[i][j]);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            sets[i].clear();
        }
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                auto& st = sets[(j + m - 1 - i) % n];
                if (!st.count(grid[i][j])) {
                    test_set(i - 1, j - 1, br, br[i][j] + 1);
                } else {
                    test_set(i - 1, j - 1, br, br[i][j]);
                }
                if (j == 0) {
                    st.clear();
                } else {
                    st.insert(grid[i][j]);
                }
            }
        }
        // debug(tl);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                tl[i][j] = std::abs(tl[i][j] - br[i][j]);
            }
        }
        return tl;
    }
};

int main() {
    auto v = read_v2();
    auto res = Solution().differenceOfDistinctValues(v);
    out(res);
}