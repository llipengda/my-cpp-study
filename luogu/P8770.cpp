#include <bits/stdc++.h>

using namespace std;

int get(int x, int y) {
    cerr << format("get({}, {})\n", x, y);
    if (x == 0 || y == 0)
        return 0;
    if (x == 1)
        return y - 1;
    if (y == 1)
        return x - 1;
    return get(x / 2, y) + get(x - x / 2, y) + 1;
}

int main() {
    // cout << get(20, 22) + 4;
    char c;
    cin >> c;
    if (c == 'A')
        cout << 443;
    else
        cout << "LLLV";
}