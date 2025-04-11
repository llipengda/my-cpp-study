#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n + 1);
    vector<long long> pre(n + 1);

    pre[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        pre[i] = v[i] + pre[i - 1];
    }

    long long ans = 0;
    for (int i = 2; i <= n; i++) {
        ans += v[i] * pre[i - 1];
    }

    cout << ans;
}