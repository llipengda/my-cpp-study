#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
string str, t;
int ra, n;
vector<int> num;
vector<char> opr;
ll ans;
bool flag = false;
ll op(ll a, ll b, ll mod)
{
    ll res = 1;
    while (b > 0) {
        if (b % 2 == 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        b = b / 2;
    }
    return res;
}
void dfs(int now, int n)
{
    if (now > n || flag == true)
        return;
    ll ans1 = ans;
    ans = op(ans, ans, num[now]);
    opr.push_back('#');
    if (now == n && ans == ra) {
        flag = 1;
        return;
    }
    dfs(now + 1, n);
    if (now > n || flag == true)
        return;
    ans = ans1;
    opr.pop_back();
    ans += num[now];
    opr.push_back('+');
    if (now == n && ans == ra) {
        flag = true;
        return;
    }
    dfs(now + 1, n);
    if (now > n || flag == true)
        return;
    ans = ans1;
    opr.pop_back();
    ans -= num[now];
    opr.push_back('-');
    if (now == n && ans == ra) {
        flag = 1;
        return;
    }
    dfs(now + 1, n);
    if (now > n || flag == true)
        return;
    ans = ans1;
    opr.pop_back();
}
int main()
{
    getline(cin, str);
    str.find("=");
    istringstream iss(str);
    while (getline(iss, t, '?'))
        num.push_back(stoi(t));
    istringstream iss2(str);
    getline(iss2, t, '=');
    getline(iss2, t, '=');
    ra = stoi(t);
    n = num.size()-1;
    ans = num[0];
    dfs(1, n);
    if (flag) {
        cout << num[0];
        for (int i = 0; i < n; i++)
            cout << opr[i] << num[i + 1];
        cout << '=' << ra;
    } else
        cout << "-1";
}