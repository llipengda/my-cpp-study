#include <bits/stdc++.h>
using std::vector;

class Solution {
public:
    int sumOfBeauties(vector<int>& nums) {
        std::vector<int> beautiful(nums.size(), 0);
        auto max = *nums.begin();

        for(int i = 0; i < nums.size(); i++) {
            if (nums[i] > max) {
                beautiful[i] = 1;
                max = nums[i];
            }
        }

        auto min = *nums.rbegin();

        for (int i = nums.size() - 1; i >= 0; i--) {
            if (nums[i] < min) {
                beautiful[i] &= 1;
                min = nums[i];
            } else {
                beautiful[i] = 0;
            }
        }

        int cnt = 0;

        for (int i = 1; i <= nums.size() - 2; i++) {
            int l = nums[i - 1];
            int r = nums[i + 1];
            int c = nums[i];
            if (!(l < c && r > c)) {
                continue;
            }
            cnt += beautiful[i] + 1;
        }

        return cnt;
    }
};

int main() {
    int n;
    std::cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        std::cin >> v[i];
    }
    std::cout << Solution().sumOfBeauties(v);
}