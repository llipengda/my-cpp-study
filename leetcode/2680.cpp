#include "../helper/helper.h"
#include <algorithm>
#include <vector>

using std::vector;

class Solution {
public:
    long long maximumOr(vector<int>& nums, int k) {
        std::vector<int> c(64, 0);
        auto max_bit = [&c](int v) {
            int res{};
            for (int i = 31; i >= 0; i--) {
                if (v & (1 << i)) {
                    c[i]++;
                    if (!res) {
                        res = i;
                    }
                }
            }
            return res;
        };
        auto calc = [&c, k](long long v) {
            for (int i = 31; i >= 0; i--) {
                if (v & (1 << i)) {
                    c[i]--;
                }
            }
            long long r = 0;
            for (int i = 0; i < 64; i++) {
                if (c[i]) {
                    r |= (1 << i);
                }
            }
            for (int i = 31; i >= 0; i--) {
                if (v & (1 << i)) {
                    c[i]++;
                }
            }
            return (v << k) | r;
        };
        auto n = nums.size();
        std::vector<std::pair<long long, int>> numsp(n);
        for (int i = 0; i < n; i++) {
            numsp[i] = {nums[i], max_bit(nums[i])};
        }
        std::sort(numsp.begin(), numsp.end(), [&](auto a, auto b) {
            return a.second > b.second;
        });

        auto end = std::upper_bound(numsp.begin(), numsp.end(), numsp[0], [](auto a, auto b) {
            return a.second > b.second;
        });

        auto it = std::max_element(numsp.begin(), end, [&](auto a, auto b) {
            return calc(a.first) < calc(b.first);
        });

        it->first <<= k;

        long long ans = 0;
        for (auto [v, _] : numsp) {
            ans |= v;
        }
        return ans;
    }
};

int main() {
    int k{};
    std::vector<int> v{};
    read(k, v);
    out(Solution().maximumOr(v, k));
}