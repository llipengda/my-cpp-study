/*
链接：https://ac.nowcoder.com/acm/contest/45670/F
来源：牛客网
HINT 题目描述
小竹正在和小胖激烈的玩着游戏，突然砰砰砰的敲门声响起。
小竹走到猫眼面前一看，糟了！是妈妈。
可是小竹还没说话小胖已经开了门。
妈妈看着偷跑的小竹十分气愤，于是她请来了小竹最好的朋友工口发动机出一道题折磨小竹，题目如下：
定义关于一个排列 p 的函数 F(p,l,r,x) = ∑_{i=l}^{r}​ [p_x​≤p_i​]。
其中[x]的括号为艾弗森括号，若x表示的条件成立，则[x]=1，否则[x]=0。
定义函数 inv(p) 为排列 p 的逆序对数量。
定义一个排列的价值：H(p)=inv(p) ∑_{x=1}^{n} ​∑_{i=1}^{x}​ ∑_{j=x}^{n}​ F(p,i,j,x)
现在给出一个 n，求出所有长度为 n 的排列的价值之和。
即求出：∑_{p∈Sp}​ ​H(p)其中 Sp​ 表示所有长度为n的排列所组成的集合。
考虑到答案可能很大，请将答案对 10^9+7取模。
HINT 输入描述:
第一行一个正整数 t(1≤t≤10) 。
接下来 t 行，每行一个正整数 n(1≤n≤10 5 )。
HINT 输出描述:
t行，每行一个整数，为所求式子的值。
*/
#include <bits/stdc++.h>
#define endl '\n'
#define IO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define REP(i, a, b) for (int i = a; i <= b; i++)
#define PER(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
constexpr int mod = 1E9 + 7;
const int N = 1E5 + 5;
ll fac[N];
ll qpow(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b & 1)    ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}
ll inv(ll a) { return qpow(a, mod - 2); }
void init() {
    fac[0] = 1;
    REP(i, 1, N)
        fac[i] = (fac[i - 1] * i) % mod;
}
void solve(int n) {
    ll c1 = 1ll * (n + 3) % mod * (n + 2) % mod * (n + 1) % mod * n % mod * inv(24) % mod;
    ll c2 = 1ll * n * (n - 1) % mod * inv(4) % mod;
    ll ans = fac[n];
    ans = ans * c1 % mod * c2 % mod;
    cout << ans << endl;
}
int main()
{
    init();
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        solve(n);
    }
}