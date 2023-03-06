/*
HINT 题目描述
有 n 种面额不同的邮票，面额分别为 C1,C2,C3…..Cn。面额 Ci 的邮票最多可以取 Mi 张。请问，用这些邮票，可以贴出多少面额不同的邮资 (包括 0)。贴邮票时，邮票不必全部使用。
HINT 输入格式
本题有多组数据，第一行为一个整数 t，表示有 t 组测试数据。
每组测试数据的第一行为一个整数 n，表示有多少种不同面额的邮票。(1<=N<=10)
第二行有 n 个整数，分别表示第 C1,C2….Cn 种不同面额。(1<=Ci<=20)
第三行有 n 个整数，分别表示面额为 Ci 的邮票有 Mi 张。(1<=Mi<=20)
HINT 输出格式
每组数据输出一行，每行一个整数，表示可以贴出多少种不同的面额。
*/
#include <bits/stdc++.h>
#define endl '\n'
#define IO ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
#define REP(i, a, b) for (int i = a; i <= b; i++)
#define PER(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
const int N = 5010;
void solve() {
    int n;
    cin >> n;
    vector<int> v(n + 1, 0), c(n + 1, 0);
    vector<int> dp(N, 0);
    REP(i, 1, n) {
        cin >> v[i];
    }
    REP(i, 1, n) {
        cin >> c[i];
    }
    REP(i, 0, c[1]) {
        dp[i * v[1]] = 1;
    }
    REP(i, 2, n) {
        REP(j, 1, c[i]) {
            PER(k, N, 0) {
                if (k + v[i] < N && dp[k]) dp[k + v[i]] = 1;
            }
        }
    }
    int ans = 0;
    REP(i, 1, N) {
        if (dp[i]) ans++;
    }
    cout << ans << endl;
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}