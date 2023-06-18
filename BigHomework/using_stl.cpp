#include <bits/stdc++.h>
#define endl '\n'
#define IO ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
using namespace std;
using ll = long long;

struct restaurant {
    string name;
    int x;
    int y;
    double dis = 0;
};
int main() {
    IO;
    auto clk = clock();
    int m, n;
    cin >> m >> n;
    unordered_map<string, vector<restaurant>> mp;
    while (m--) {
        string name, type;
        int x, y;
        cin >> name >> x >> y >> type;
        mp[type].emplace_back(std::move(restaurant{name, x, y}));
    }
    while (n--) {
        int x, y, k;
        string type;
        cin >> x >> y >> type >> k;
        for_each(mp[type].begin(), mp[type].end(), [&](restaurant& a) {
            a.dis = sqrt((ll)(x - a.x) * (x - a.x) + (ll)(y - a.y) * (y - a.y));
        });
        sort(mp[type].begin(), mp[type].end(), [&](restaurant& a, restaurant& b) {
            return tie(a.dis, a.name) < tie(b.dis, b.name);
        });
        int cnt = k;
        for (auto i : mp[type]) {
            if (--cnt < 0) {
                break;
            }
            cout << i.name << fixed << setprecision(3) << i.dis << endl;
        }
    }
#ifndef ONLINE_JUDGE
    cerr << "time : " << clock() - clk << "ms" << endl;
#endif
}