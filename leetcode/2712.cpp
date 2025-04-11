#include "../helper/helper.h"

class Solution {
public:
    long long minimumCost(string s) {
        int n = s.size();
        std::vector<long long> pre(n, 0);
        std::vector<long long> suf(n, 0);
        for (int i = 1; i < n; i++) {
            pre[i] = pre[i - 1] + (s[i] == s[i - 1] ? 0 : i);
        }
        for (int i = n - 2; i >= 0; i--) {
            suf[i] = suf[i + 1] + (s[i] == s[i + 1] ? 0 : (n - i - 1));
        }
        long long res = pre[0] + suf[0];
        for (int i = 1; i < n; i++) {
            res = std::min(res, pre[i] + suf[i]);
        }
        return res;
    }
};

int main() {
    std::string s;
    read(s);
    out(Solution().minimumCost(s));
}