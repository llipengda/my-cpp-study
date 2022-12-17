//买书问题
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll book[35];
ll m, n, k; // m元 n本书 买k本
int flag;
// sum总价格 cnt买书数量 book_i正在考虑的书
int dfs(ll sum, ll cnt, int book_i)
{
    if (sum == m && cnt == k)
        return flag=1;
    if (sum > m || cnt > k || book_i > n)
        return 0;
    if (sum + book[book_i] <= m) {
        dfs(sum + book[book_i], cnt + 1, book_i + 1);
        dfs(sum, cnt, book_i + 1);
    } else
        dfs(sum, cnt, book_i + 1);
    return flag;
}
int main()
{
    cin >> m >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> book[i];
    if (dfs(0, 0, 0))
        cout << "Yes";
    else
        cout << "No";
}