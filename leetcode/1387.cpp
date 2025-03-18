#include "../helper/helper.h"

class Solution {
public:
    int getKth(int lo, int hi, int k) {
        std::unordered_map<int, int> v{};
        v[1] = 0;
        v[2] = 1;
        std::function<int(int)> calc = [&](int n) {
            if (v[n] > 0 || n == 1) {
                return v[n];
            } else if (n % 2 == 0) {
                return v[n] = calc(n / 2) + 1;
            } else {
                return v[n] = calc(3 * n + 1) + 1;
            }
        };
        for (int i = 2; i <= 1000; i++) {
            calc(i);
        }
        auto n = hi - lo + 1;
        auto nums = std::vector<int>(n, 0);
        for (int i = 0; i < n; i++) {
            nums[i] = lo + i;
        }
        std::sort(nums.begin(), nums.end(), [&](int a, int b) {
            int va = calc(a), vb = calc(b);
            return std::tie(va, a) < std::tie(vb, b);
        });
        return nums[k - 1];
    }
};

int main() {
    int low, high, k;
    read(low, high, k);
    std::cout << Solution().getKth(low, high, k);
}