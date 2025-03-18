#include "../helper/helper.h"

using std::vector;

class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        std::sort(ages.begin(), ages.end());

        int cnt = 0;

        for (int i = 0; i < ages.size(); i++) {
            auto x = ages[i];
            auto l = std::upper_bound(ages.begin(), ages.end(), 0.5 * x + 7);
            auto r = std::upper_bound(ages.begin(), ages.end(), x);
            if (x < 100) {
                auto nr = std::upper_bound(ages.begin(), ages.end(), 100);
                r = std::min(r, nr);
            }
            if (r > l) {
                cnt += r - l;
                if (i >= l - ages.begin() && i < r - ages.begin()) {
                    cnt -= 1;
                }
            }
        }

        return cnt;
    }
};

int main() {
    auto v = read_v_unknown();
    std::cout << Solution().numFriendRequests(v);
}