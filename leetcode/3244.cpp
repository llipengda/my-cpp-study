#include "../helper/helper.h"

using std::vector;

class Solution {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        std::vector<int> res{};
        std::vector<int> road(n + 1, 1);
        std::iota(road.begin(), road.end(), 1);
        int v = n - 1;
        for (auto&& q: queries) {
            auto l = q[0];
            auto r = q[1];
            if (road[l] != -1 && road[l] < r) {
                int d = road[l];
                int i = l;
                while(i < r) {
                    d = road[i];
                    road[i] = -1;
                    v--;
                    i = d;
                }
                road[l] = r;
                v++;
            }
            res.push_back(v);
        }
        return res;
    }
};

int main() {
    int n;
    read(n);
    auto q = std::vector<std::vector<int>>{};
    int a, b;
    while(std::cin >> a >> b) {
        q.push_back({a, b});
    }
    auto r = Solution().shortestDistanceAfterQueries(n, q);
    for (auto i: r) {
        std::cout << i << ' ';
    }
}