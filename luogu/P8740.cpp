#include <bits/stdc++.h>
#define endl '\n'
#define IO std::ios::sync_with_stdio(false), std::cin.tie(nullptr)
using namespace std;
using ll = long long;

#if 0
// E
vector<int> mp[22];
ll memo[22][1 << 22];
int n = 21;

ll dfs(int i, int j) {
    if (j == (1 << (n + 1)) - 2) return 1; 
    if (memo[i][j] != -1) return memo[i][j];

    ll res = 0;
    for (int nx : mp[i]) {
        if (!(j & (1 << nx))) { 
            res += dfs(nx, j | (1 << nx));
        }
    }
    return memo[i][j] = res;
}

int main() {
    IO;

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (__gcd(i, j) == 1) {
                mp[i].push_back(j);
                mp[j].push_back(i);
            }
        }
    }

    memset(memo, -1, sizeof(memo));

    ll ans = 0;
    ans = dfs(1, 1 << 1);
    cout << ans << endl;
    // 881012367360

    return 0;
}
#endif

#if 0
// D
struct edge {
    int v, w;
};

vector<edge> g[2022];
bool vis[2022];
int dis[2022];

int lcm(int a, int b) {
    return a * b / __gcd(a, b);
}

void dijkstr() {
    memset(dis, 0x3f, 2022 * sizeof(int));
    dis[1] = 0;

    for (int i = 1; i < 2022; i++) {
        int u = 0;
        int mind = 0x3f3f3f3f;
        for (int j = 1; j < 2022; j++) {
            if (!vis[j] && dis[j] < mind) {
                u = j;
                mind = dis[j];
                vis[u] = true;
            }
        }
        for (auto e : g[u]) {
            dis[e.v] = min(dis[e.v], dis[u] + e.w);
        }
    }
}

int main() {
    for (int i = 1; i <= 2021; i++) {
        for (int j = 1; j <= 2021; j++) {
            if (j != i && abs(i - j) <= 21) {
                int w = lcm(i, j);
                g[i].push_back({j, w});
                g[j].push_back({i, w});
            }
        }
    }

    dijkstr();

    cout << dis[2021];
    // 10266837
}
#endif

#if 0
// C
constexpr ll n = 2021041820210418;

int main() {
    unordered_set<ll> v;

    for (ll i = 1; i * i < n; i++) {
        if (n % i == 0) {
            v.insert(i);
            v.insert(n / i);
        }
    }

    ll ans{};
    for (ll i : v) {
        for (ll j : v) {
            for (ll k: v) {
                if (i * j * k == n) {
                    ans++;
                }
            }
        }
    }

    cout << ans;
    // 2430
}
#endif

#if 0
// A
int m[10];

int main() {
    for (int& i : m) {
        i = 2021;
    }

    for (int i = 1; ;i++) {
        string s = to_string(i);

        for (auto c : s) {
            int cc = c - '0';
            if (m[cc] == 0) {
                cout << i - 1;
                return 0;
            }
            m[cc]--;
        }
    }
    // 3181
}
#endif

#if 0
// B
using pii = pair<int, int>;
struct frac {
    int a, b;
    frac() = delete;
    frac(int _a, int _b) {
        int c = __gcd(_a, _b);
        a = _a / c;
        b = _b / c;
        if (b < 0) {
            a = -a;
            b = -b;
        }
    }
};

int main() {
    set<pair<pii, pii>> st;

    for (int x1 = 0; x1 < 20; x1++) {
        for (int y1 = 0; y1 < 21; y1++) {
            for (int x2 = 0; x2 < 20; x2++) {
                for (int y2 = 0; y2 < 21; y2++) {
                    if (x1 == x2 || y1 == y2) {
                        continue;
                    }
                    frac k(y1 - y2, x1 - x2);
                    frac b(x1 * y2 - x2 * y1, x1 - x2);
                    st.insert({{k.a, k.b}, {b.a, b.b}});
                }
            }
        }
    }

    cout << st.size() + 20 + 21;
}
#endif

int main() {
    string ans[] = {
        "3181",
        "40257",
        "2430",
        "10266837",
        "881012367360"};
    char T;
    cin >> T;
    cout << ans[T - 'A'] << endl;
    return 0;
}