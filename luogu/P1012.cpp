#include <bits/stdc++.h>
#define endl '\n'
#define IO std::ios::sync_with_stdio(false), std::cin.tie(nullptr)
using ll = long long;
using pii = std::pair<int, int>;
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<string> v(n);
    for (auto& i : v) {
        cin >> i;
    }
    sort(begin(v), end(v), [](const string& a, const string& b) {
        return a + b > b + a;
    });

    for (auto i : v) {
        cout << i;
    }
}