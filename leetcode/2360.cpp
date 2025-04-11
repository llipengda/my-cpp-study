#include "../helper/helper.h"

class Solution {
public:
    int longestCycle(vector<int>& edges) {
        int n = edges.size();
        std::vector<int> vis(n, 0);
        int res = -1;
        int ts = 1;
        for (int i = 0; i < n; i++) {
            int cur = i;
            while (cur != -1 && !vis[cur]) {
                vis[cur] = ts++;
                cur = edges[cur];
                if (cur != -1 && vis[cur] != 0 && vis[cur] >= vis[i]) {
                    res = std::max(res, ts - vis[cur]);
                }
            }
        }
        return res;
    }
};

int main() {
    std::vector<int> edges;
    read(edges);
    out(Solution().longestCycle(edges));
}