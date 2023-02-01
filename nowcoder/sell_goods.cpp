/*
链接：https://ac.nowcoder.com/acm/contest/46813/A
来源：牛客网
HINT 题目描述
小沙非常好客，小沙有一家超市，超市里面有为 n 件商品，小沙有 Q 个问题，
小沙想问问你，如果小沙想要让你挑选最多 k 个价值不大于 x 的商品，请问你能挑选的价值和最大为多少。
HINT 输入描述:
第一行输入两个整数 n,Q 1≤n≤10^5, 1≤Q≤10^5, 代表商品的个数以及询问的次数。
第二行输入 n 个数字，代表商品价格序列 a, 1≤a_i​≤10^9 。
随后 Q 行，每行两个正整数 k,x 1≤k≤n, 1≤x≤10^9 。
HINT 输出描述:
每次询问输出一行整数代表答案，共 Q 行。
*/
#include <bits/stdc++.h>
#define endl '\n'
#define IO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
ll n, q, k, x, ans;
ll item[100005];
int find(ll arr[], int n, int x)
{
    int left = 0, right = n - 1;
    int result = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > x) {
            result = mid;
            right = mid - 1;
        } else
            left = mid + 1;
    }
    return result;
}
int main()
{
    IO;
    cin >> n >> q;
    for (ll i = 0; i < n; i++)
        cin >> item[i];
    sort(item, item + n);
    while (q--) {
        ans = 0;
        cin >> k >> x;
        for (ll i = find(item, n, x); i >= 0; i--) {
            if (item[i] <= x && k > 0) {
                ans += item[i];
                k--;
            }
            if (k == 0)
                break;
        }
        cout << ans << endl;
    }
}