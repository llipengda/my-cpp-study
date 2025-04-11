#include <bits/stdc++.h>
using namespace std;

template <class T>
struct segment_tree {
    int n;
    std::vector<T> tree;
    std::vector<T>* value;
    std::function<T(T, T)> fun;

    segment_tree() = delete;

    segment_tree(int n_, std::vector<T>& value_, std::function<T(T, T)> fun_) : n(n_), tree(4 * n), value(&value_), fun(fun_) {}

    void build(int l, int r, int p) {
        if (l == r) {
            tree[p] = (*value)[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, p * 2);
        build(mid + 1, r, p * 2 + 1);

        tree[p] = fun(tree[p * 2], tree[p * 2 + 1]);
    }

    void build() {
        build(1, n, 1);
    }

    T query(int il, int ir, int l, int r, int p) {
        if (il <= l && r <= ir) {
            return tree[p];
        }
        int m = (l + r) >> 1;
        T res{};
        if (il <= m) {
            res = fun(res, query(il, ir, l, m, p * 2));
        }
        if (ir > m) {
            res = fun(res, query(il, ir, m + 1, r, p * 2 + 1));
        }
        return res;
    }

    T query(int il, int ir) {
        return query(il, ir, 1, n, 1);
    }
};

int main() {
    int n, m, x;
    cin >> n >> m >> x;

    vector<int> v(n + 1);
    unordered_map<int, int> mp;

    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        v[i] = mp[t ^ x];
        mp[t] = i;
    }

    segment_tree<int> st(n, v, [](int a, int b) { return max(a, b); });

    st.build();

    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << ((st.query(l, r) >= l) ? "yes" : "no") << '\n';
    }
}