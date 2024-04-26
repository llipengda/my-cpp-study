#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> findColumnWidth(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> max_w(n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                max_w[j] = max((int)to_string(grid[i][j]).length(), max_w[j]);
            }
        }
        return max_w;
    }
};