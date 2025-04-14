#include <bits/stdc++.h>
using namespace std;

struct dsu {
    vector<int> p, siz;
    dsu(int n) : p(n + 1), siz(n + 1, 1) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        return x == p[x] ? x : p[x] = find(p[x]);
    }
    bool merge(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) {
            return false;
        }
        if (siz[px] > siz[py]) {
            siz[px] += siz[py];
            p[py] = px;
        } else {
            siz[py] += siz[px];
            p[px] = py;
        }
        return true;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int size(int x) {
        return siz[find(x)];
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    dsu d(n);
    while (m--) {
        int z, x, y;
        cin >> z >> x >> y;
        if (z == 1) {
            d.merge(x, y);
        } else {
            cout << (d.same(x, y) ? "Y" : "N") << '\n';
        }
    }
}