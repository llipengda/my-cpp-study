#include <bits/stdc++.h>

int main() {
    std::int64_t n{}, k{}, T{};
    std::cin >> n >> k >> T;
    std::vector<std::int64_t> s(n);
    for (auto& i : s) {
        std::cin >> i;
    }

    std::vector<std::int64_t> vec(n);
    std::vector<std::int64_t> pre(n);
    std::vector<std::int64_t> pre2(n);

    auto check = [&](int v) {
        vec = s;
        std::sort(vec.begin(), vec.begin() + v);
        pre[0] = vec[0];
        pre2[0] = vec[0] * vec[0];
        for (int i = 1; i < v; i++) {
            pre[i] = pre[i - 1] + vec[i];
            pre2[i] = pre2[i - 1] + vec[i] * vec[i];
        }
        double min = 1e10;
        for (int i = k - 1; i < v; i++) {
            double sum2 = pre2[i] - (i - k < 0 ? 0 : pre2[i - k]);
            double sum = pre[i] - (i - k < 0 ? 0 : pre[i - k]);
            double sigma = sum2 / k - (sum * sum) / (k * k);
            min = std::min(sigma, min);
        }
        return min < T;
    };

    int ans = -1;
    int l = k;
    int r = n;
    while (l <= r) {
        auto mid = (l + r) / 2;
        if (check(mid)) {
            r = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }

    std::cout << ans << '\n';
}
