#include <bits/stdc++.h>

struct soldier {
    int p;
    int c;

    bool operator<(const soldier& o) const {
        return c < o.c;
    }

    // auto to_string() {
    //     return "{p = " + std::to_string(p) + ", c = " + std::to_string(c) + "}";
    // }
};

int main() {
    long long n{}, s{};
    std::cin >> n >> s;
    std::vector<soldier> v(n);

    long long total{};
    for (int i = 0; i < n; i++) {
        std::cin >> v[i].p >> v[i].c;
        total += v[i].p;
    }
    std::sort(v.begin(), v.end());

    long long cnt{};
    long long res{};
    for (int i = 0; i < n; i++) {
        auto so = v[i];
        if (cnt >= so.c) {
            total -= so.p;
            continue;
        }
        if (total > s) {
            res += s * (so.c - cnt);
            cnt += so.c - cnt;
        } else {
            res += so.p * (so.c - cnt);
        }
        total -= so.p;
    }

    std::cout << res << '\n';
}