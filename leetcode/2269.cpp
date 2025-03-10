#include <bits/stdc++.h>
// #include "../template/debug.hpp"

class Solution {
public:
    int divisorSubstrings(int num, int k) {
        auto str_num = std::to_string(num);
        auto cnt = 0;
        for (int start = 0; start <= str_num.length() - k; start++) {
            auto sub = str_num.substr(start, k);
            auto sub_num = atoi(sub.c_str());
            // debug(sub_num);
            if (sub_num != 0 && num % sub_num == 0) {
                cnt++;
            }
        }
        return cnt;
    }
};

int main() {
    int num, k;
    std::cin >> num >> k;
    std::cout << Solution().divisorSubstrings(num, k);
}