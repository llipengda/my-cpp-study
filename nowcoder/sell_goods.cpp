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
ll item[100005], sum[100005];
int main()
{
    IO;
    cin >> n >> q;
    for (ll i = 0; i < n; i++)
        cin >> item[i];
    sort(item, item + n);
    sum[0] = item[0];
    for (ll i = 1; i < n; i++)
        sum[i] = sum[i - 1] + item[i];
    //~ 使用前缀和进行预处理来提高效率！！
    while (q--) {
        cin >> k >> x;
        ll t = upper_bound(item, item + n, x) - item - 1;
        //~ 使用 upper_bound() 函数二分查找数组中大于 x的第一个元素，该函数返回一个指向该元素的指针，- item后为该元素的下标，-1后为小于等于 x的最后一个元素
        //~ 相似地，可以使用 lower_bound() 函数二分查找数组中大于等于 x的第一个元素
        cout << sum[t] - ((t - k) >= 0 ? sum[t - k] : 0) << endl; 
        //~ [a,b]的和使用前缀和的求法: sum[b] - sum[a - 1]，注意此时 b为 t - k + 1.
    }
}