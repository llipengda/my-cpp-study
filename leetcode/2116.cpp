#include "../helper/helper.h"

class Solution {
public:
    bool canBeValid(string s, string locked) {
        auto n = s.size();
        if (n & 1) {
            return false;
        }
        int mx{};
        int mn{};
        for (int i = 0; i < n; i++) {
            if (locked[i] == '1') {
                mx += s[i] == '(' ? 1 : -1;
                mn += s[i] == '(' ? 1 : -1;
            } else {
                mx++;
                mn--;
            }
            if (mx < 0) {
                return false;
            }
            if (mn < 0) {
                assert(i & 1);
                mn = 1;
            }
        }
        return mn == 0;
    }
};