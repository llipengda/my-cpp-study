/*
HINT 题目描述 
Tokitsukaze 有一个长度为 n 的序列 a 和一个正整数 p 。 
 对于所有 x=0 ... p-1，Tokitsukaze 想知道三元组 [i,j,k] 的数量，满足： 
 • i != j and i != k and j != k 
 • (a_i · a_j + a_k) ≡ x (mod p)
HINT 输入描述: 
第一行包含两个整数 n, p (3 ≤n ≤5000; 1 ≤p ≤5000)。 
第二行包含 n 个整数 a_1,a_2, ..., a_n (0 ≤a_i ≤10^9)。
HINT 输出描述: 
输出一行 p 个整数，第 d 个整数表示 x=d 时的答案 (0 ≤d ≤p-1)。 
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
int main() {
    int n, p;
    cin >> n >> p;
    vector<int> a(n + 1);
    REP(i, 1, n) {
        cin >> a[i];
        a[i] %= p;
    }
    vector<int> cnt(p, 0);
    // cnt[x]: a[i] * a[j] % p = x
    vector<vector<int>> del(n + 1, vector<int>(p, 0));
    // del[k][x]: a[i] * a[k] % p = x
    REP(i, 1, n) {
        REP(j, 1, n) {
            if (i == j) continue;
            cnt[a[i] * a[j] % p]++;
            del[i][a[i] * a[j] % p] += 2; // i, j 都有可能与 k 相等
        }
    }
    REP(x, 0, p - 1) {
        ll ans = 0;
        REP(k, 1, n) {
            int tar = (x - a[k] + p) % p;
            ans += cnt[tar] - del[k][tar];
        }
        cout << ans << ' ';
    }
}