#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestPath(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> m(n);
        for (int i = 1; i < n; ++i) {
            m[parent[i]].push_back(i);
        }
        int res = 0;
        function<int(int)> dfs = [&](int u) {
            int max_len = 0;
            for (int v : m[u]) {
                int l = dfs(v) + 1;
                if (s[u] == s[v]) {
                    continue;
                }
                res = max(res, l + max_len);
                max_len = max(max_len, l);
            }
            return max_len;
        };
        dfs(0);
        return res + 1;
    }
};

int main() {
    Solution s;
    string str;
    cin >> str;
    vector<int> parent;
    int x;
    while (cin >> x) {
        parent.push_back(x);
    }
    std::cout << s.longestPath(parent, str) << endl;
    return 0;
}