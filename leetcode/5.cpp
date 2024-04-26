#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.size();
        vector<vector<int>> dp(len, vector<int>(len, 0));
        for (int i = 0; i < len; i++) {
            dp[i][i] = 1;
        }
        int ll = 0;
        int max_l = 1;
        for (int i = 0; i < len; i++) {
            for (int j = i + 1; j < len; j++) {
                if (j >= len) {
                    break;
                }
                if (j - i <= 1 && s[i] == s[j]) {
                    dp[i][j] = 1;
                } else if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1];
                }
                if (dp[i][j] && j - i + 1 > max_l) {
                    max_l = j - i + 1;
                    ll = i;
                }
            }
        }
        return s.substr(ll, max_l);
    }
};