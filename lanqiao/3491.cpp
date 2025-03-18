#include <bits/stdc++.h>

std::array<std::array<int, 4 * 9 + 5>, 5> table{};

auto calc(int n) {
    int cnt{}, sum{};
    while (n) {
        cnt++;
        sum += n % 10;
        n /= 10;
    }
    table[cnt][sum]++;
}

int main() {
    for (int i = 1; i < 10000; i++) {
        calc(i);
    }
    int ans{};
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 9 * i; j++) {
            for (int k = 1; k <= i; k++) {
                ans += table[i][j] * table[k][j]; 
            }
        }
    }
    std::cout << ans;
}