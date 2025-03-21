#include "../helper/helper.h"

using std::vector;

class Solution {
public:
    vector<int> minReverseOperations(int n, int p, vector<int>& banned, int k) {
        std::vector<int> ans(n, -1);
        std::vector<int> vis(n, 0);
        std::set<int> sets[2];
        for (int i = 0; i < n; i++) {
            sets[i % 2].insert(i);
        }
        for (auto i : banned) {
            // vis[i] = 1;
            sets[i % 2].erase(i);
        }
        ans[p] = 0;
        sets[p % 2].erase(p);
        std::queue<int> q{};
        q.push(p);
        // auto in = [n](int x) {
        //     return x >= 0 && x < n;
        // };
        while (!q.empty()) {
            auto v = q.front();
            q.pop();
            // vis[v] = 1;
            // std::vector<int> m{};
            auto l = std::max(k - v - 1, v - k + 1);
            auto r = std::min(v + k - 1, 2 * n - v - k - 1);
            auto& s = sets[l % 2];
            auto it = s.lower_bound(l);
            while (it != s.end() && *it <= r) {
                ans[*it] = ans[v] + 1;
                q.push(*it);
                it = s.erase(it);
            }
            // for (int l = std::max(0, v - k + 1); l <= std::min(v, n - 1); l++) {
            //     if (!in(l + k - 1)) {
            //         continue;
            //     }
            //     auto f = 2 * l + k - v - 1;
            //     if (in(f) && !vis[f]) {
            //         debug(v);
            //         debug(l);
            //         debug(f);
            //         m.push_back(f);
            //     }
            // }
            // debug(m);
            // for (auto i : m) {
            //     q.push(i);
            //     ans[i] = ans[i] != -1 ? std::min(ans[v] + 1, ans[i]) : ans[v] + 1;
            // }
        }
        return ans;
    }
};

int main() {
    int n, p, k;
    std::vector<int> b;
    read(n, p, k, b);
    auto res = Solution().minReverseOperations(n, p, b, k);
    out(res);
}