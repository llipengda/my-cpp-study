#include "../helper/debug.hpp"
#include <bits/stdc++.h>

using std::vector;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        auto res = std::vector<int>(m + n);
        int j = 0, k = 0;
        if (nums1.size() == 0) {
            nums1 = std::move(nums2);
            return;
        }
        if (nums2.size() == 0) {
            return;
        }
        for (int i = 0; i < m + n; i++) {
            if (k >= n || (j < m && nums1[j] < nums2[k])) {
                res[i] = nums1[j++];
            } else {
                res[i] = nums2[k++];
            }
        }
        nums1 = std::move(res);
    }
};

int main() {
    auto nums1 = std::vector<int>{2, 0};
    auto nums2 = std::vector<int>{1};
    Solution().merge(nums1, nums1.size() - nums2.size(), nums2, nums2.size());
    debug_out(nums1);
}