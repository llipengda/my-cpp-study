/*
链接：https://ac.nowcoder.com/acm/contest/46811/C
来源：牛客网
HINT 题目描述
小红希望你构造一个长度为 n 的排列，满足对于每个 a_i​ ，有 2≤∣a_i​−i∣≤3.
你能帮帮她吗？
注：数组下标从 1 到 n。排列是指长度为 n 的数组，1 到 n 每个正整数恰好出现一次。
HINT 输入描述:
一个正整数 n (1≤n≤10^5)
HINT 输出描述:
如果无解，请输出-1。否则输出任意合法解即可。
*/
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int a[100005], s[] = { -3, -2, 2, 3 }, ans[100005];
vector<int> avaible[100005];
bool flag = false;
void dfs(int now, int n)
{
    for (auto i : avaible[now]) {
        if (now > n || flag == true)
            return;
        if (a[i] == 0) {
            a[i] = now;
            ans[i] = now;
            if (now == n)
                flag = true;
            dfs(now + 1, n);
            a[i] = 0;
        }
    }
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 4; j++)
            if (i + s[j] > 0 && i + s[j] <= n)
                avaible[i].push_back(i + s[j]);
    dfs(1, n);
    if (flag == true)
        for (int i = 1; i <= n; i++)
            cout << ans[i] << ' ';
    else
        cout << "-1";
}