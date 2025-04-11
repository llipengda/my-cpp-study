#include <bits/stdc++.h>
using namespace std;
int main() {
    long long l, r;
    cin >> l >> r;

    auto c = [](long long n) {
        return n <= 1 ? 0 : ((n - 2) / 4 + 1);
    };

    cout << r - l + 1 - (c(r) - c(l - 1));
}