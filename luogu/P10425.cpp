#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string d;
    cin >> n >> d;
    vector<int> v(1500, 0);
    int k = 0;
    int pos = 0;
    for (int i = d.size() - 1; i >= 0; i--) {
        if (d[i] != '.') {
            v[k++] = d[i] - '0';
        } else {
            pos = k;
        }
    }
    auto mul = [&]() {
        for (int i = 0; i < k; i++) {
            v[i] *= 2;
        }
        for (int i = 0; i < k; i++) {
            v[i + 1] += v[i] / 10;
            v[i] %= 10;
        }
        if (v[k] != 0) {
            k++;
        }
    };
    while (n--) {
        mul();
    }
    if (pos != 0 && v[pos - 1] >= 5) {
        v[pos]++;
        for (int i = pos; i < k; i++) {
            v[i + 1] += v[i] / 10;
            v[i] %= 10;
        }
        if (v[k] != 0) {
            k++;
        }
    }
    for (int i = k - 1; i >= pos; i--) {
        if (i == pos - 1) {
            cout << ".";
        }
        cout << v[i];
    }
}