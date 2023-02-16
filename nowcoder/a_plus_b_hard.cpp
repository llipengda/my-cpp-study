/*
HINT 题目描述
Tokitsukaze 有一个整数 n， 以及 m 个区间 [L,R]。
 她想知道有多少种选法，满足：从 m 个区间中选择两个区间 [L_i,R_i], [L_j,R_j] (i != j)，并从第一个区间选择一个整数 a (L_i ≤ a ≤ R_i)，从第二个区间选择一个整数 b (L_j ≤ b ≤ R_j)，使得 a+b=n。
 对于两种选法，若 i, j, a, b 中有任意一个数不同，则算作不同的选法。
 由于答案可能很大，请输出对 998244353 取模后的结果。
HINT 输入描述:
第一行包含两个整数 n, m (2 ≤ n,m ≤ 4 \cdot 10^5)。
接下来 m 行，每行包含两个整数 L, R (1 ≤ L ≤ R ≤ 2 \cdot 10^5)。
HINT 输出描述:
输出一个整数表示答案对 998244353 取模后的结果。
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
constexpr int mod = 998244353;
const int N = 4e5 + 5;
int main() {
    int n, m;
    cin >> n >> m;
    vector<int> num(N, 0);
    vector<ll> c(N, 0);
    int l, r;
    ll del = 0;
    while (m--) {
        cin >> l >> r;
        num[l]++;
        num[r + 1]--;
        del += max(0ll, min(r, n - l) - max(l, n - r) + 1ll);
        del %= mod;
    }
    REP(i, 1, N) {
        c[i] = (c[i - 1] % mod + num[i] % mod) % mod;
    }
    ll ans = 0ll;
    REP(i, 1, n) {
        ans += 1ll * c[i] % mod * c[n - i] % mod;
        ans %= mod;
    }
    ans -= del;
    while (ans < 0) ans = (ans + mod) % mod;
    cout << ans << endl;
}