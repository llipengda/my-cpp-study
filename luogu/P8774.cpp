#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll bpow(ll a, ll b, ll p) {
    a %= p;
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

constexpr int mod = 998244353;

int get_mod(int a, int b) {
    return (ll)a * bpow(b, mod - 2, mod) % mod;
}

int main() {
    int n;
    cin >> n;
    vector<ll> v(n + 1, 0);
    vector<ll> p(n + 1);

    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        p[i] = get_mod(a, b);
    }

    for (int i = 1; i <= n; i++) {
        v[i] = (v[i - 1] + 1) % mod * bpow((1 - p[i] + mod) % mod, mod - 2, mod) % mod;
    }

    cout << v[n];
}