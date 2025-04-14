#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct stree {
    vector<ll> v, tag;
    int n;
    stree(int n) : v(4 * n + 1), tag(4 * n + 1), n(n) {}

    void build(int l, int r, int c, const vector<ll>& d) {
        if (l == r) {
            v[c] = d[l];
            return;
        }
        ll mid = (l + r) >> 1;
        build(l, mid, c * 2, d);
        build(mid + 1, r, c * 2 + 1, d);
        v[c] = v[c * 2] + v[c * 2 + 1];
    }

    void build(const vector<ll>& d) {
        build(1, n, 1, d);
    }

    ll query(int s, int t, int l, int r, int c) {
        if (s <= l && t >= r) {
            return v[c];
        }
        ll mid = (l + r) >> 1;
        if (tag[c] && l != r) {
            v[c * 2] += (mid - l + 1) * tag[c];
            v[c * 2 + 1] += (r - mid) * tag[c];
            tag[c * 2] += tag[c];
            tag[c * 2 + 1] += tag[c];
            tag[c] = 0;
        }
        ll ans = 0;
        if (mid >= s) {
            ans += query(s, t, l, mid, c * 2);
        }
        if (mid + 1 <= t) {
            ans += query(s, t, mid + 1, r, c * 2 + 1);
        }
        return ans;
    }

    ll query(int s, int t) {
        return query(s, t, 1, n, 1);
    }

    void update(int s, int t, int l, int r, int c, ll m) {
        if (s <= l && t >= r) {
            v[c] += m * (r - l + 1);
            tag[c] += m;
            return;
        }
        ll mid = (l + r) >> 1;
        if (tag[c] && l != r) {
            v[c * 2] += (mid - l + 1) * tag[c];
            v[c * 2 + 1] += (r - mid) * tag[c];
            tag[c * 2] += tag[c];
            tag[c * 2 + 1] += tag[c];
            tag[c] = 0;
        }
        if (mid >= s) {
            update(s, t, l, mid, c * 2, m);
        }
        if (mid + 1 <= t) {
            update(s, t, mid + 1, r, c * 2 + 1, m);
        }
        v[c] = v[c * 2] + v[c * 2 + 1];
    }

    void update(int s, int t, ll m) {
        update(s, t, 1, n, 1, m);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<ll> v(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    stree s(n);
    s.build(v);

    while (m--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            ll k;
            cin >> x >> y >> k;
            s.update(x, y, k);
        } else {
            int x, y;
            cin >> x >> y;
            cout << s.query(x, y) << '\n';
        }
    }
}