/*
https://acm.ecnu.edu.cn/problem/3024/
HINT 题目描述
写一个程序将 0 与 1 (不包括 0 和 1) 之间的八进制数转化为等价的十进制数。
例如，八进制数 0.75 就是十进制数 0.953125 (8 ^ -1 * 7 + 8 ^ -2 * 5)
小数点右边有 n 位的所有八进制数都可以转化为小数点右边至多有 3 * n 位的十进制数。
HINT 输入格式
第 1 行：一个整数 T (1 ≤ T ≤ 10) 为问题数。
接下来有 T 行，对应每个问题有 1 行，每行有一个八进制，该八进制数的形式为 0.d1d2d3...dk，
其中 di 是八进制数码（0~7），。
HINT 输出格式
对于每个问题，输出一行问题的编号（0 开始编号，格式：case #0: 等）。
然后对应每个问题在一行中输出转化后的等价十进制数。注意尾部不要输出多余的 0。
*/
#include <bits/stdc++.h>
#define endl '\n'
#define IO ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
#define REP(i, a, b) for (int i = a; i <= b; i++)
#define PER(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
string add(string _a, string _b) {
    if (_a.size() > _b.size()) swap(_a, _b);
    vector<int> a(_b.size(), 0), b(_b.size(), 0);
    vector<int> ans(_b.size() + 1, 0);
    for (int i = 0; i < _a.size(); i++) {
        a[i] = _a[i] - '0';
    }
    for (int i = 0; i < b.size(); i++) {
        b[i] = _b[i] - '0';
    }
    for (int i = ans.size() - 1; i > 0; i--) {
        ans[i] += a[i - 1] + b[i - 1];
        if (ans[i] >= 10) {
            ans[i] %= 10;
            ans[i - 1]++;
        }
    }
    string _ans(ans.size() - 1, '0');
    for (int i = 1; i < ans.size(); i++) {
        _ans[i - 1] = ans[i] + '0';
    }
    return _ans;
}
string mul(string a, int b) {
    vector<int> num(a.size() + 2);
    for (int i = 2; i < num.size(); i++) {
        num[i] = a[i - 2] - '0';
    }
    for (int i = num.size() - 1; i > 0; i--) {
        num[i] = num[i] * b;
    }
    for (int i = num.size() - 1; i > 0; i--) {
        if (num[i] / 10) {
            num[i - 1] += num[i] / 10;
            num[i] %= 10;
        }
    }
    string ans(num.size(), '0');
    for (int i = 0; i < num.size(); i++) {
        ans[i] = num[i] + '0';
    }
    return ans;
}
string power(int k) {
    // 8 ^ (-k)
    string ans(k, '0');
    int size = ans.size() - 1;
    ans[size] = '1';
    while (k--) {
        ans = mul(ans, 125);
    }
    return ans;
}
void solve() {
    string _octnum;
    cin >> _octnum;
    string octnum = _octnum.substr(2);
    string ans = "0";
    for (int i = 0; i < octnum.size(); i++) {
        string tmp = mul(power(i + 1), (octnum[i] - '0'));
        tmp = tmp.substr(tmp.size() - 3 * (i + 1));
        ans = add(ans, tmp);
    }
    int cnt = 0;
    string _ans = ans.substr(ans.size() - (3 * octnum.size()));
    for (auto it = _ans.rbegin(); *it == '0'; it++) {
        cnt++;
    }
    cout << "0.";
    for (int i = 0; i < _ans.size() - cnt; i++) {
        cout << _ans[i];
    }
    cout << endl;
}
int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cout << "case #" << i << ":\n";
        solve();
    }
}