/*
链接：https://ac.nowcoder.com/acm/contest/46814/F
来源：牛客网
HINT 题目描述 
阿宁有一个长度为n的数组a，下标从1开始。
定义f(x)是x在二进制表示下1的个数。例如 5的二进制是101，因此f(5)=2。
阿宁有q次询问，每次询问后数组恢复原样。
在一次询问中，给出k。在一次操作中，可以选择一个数i(1≤i≤n)，将ai修改为f(ai)。
请你恰好进行k次操作，要求整个数组的最大值最小，这个最大值是多少?
HINT 输入描述:
第一行两个整数n,q。
第二行n个整数ai。
接下来q行，每行一个整数k。
1≤n,q≤2×10^5
1≤ai,k≤10^9
HINT 输出描述:
输出q行，每行一个整数，表示每次询问的答案。
*/
#include <bits/stdc++.h>
#define endl '\n'
#define IO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
int count(int n)
{
    int cnt = 0;
    while (n) {
        n &= (n - 1);
        cnt++;
    }
    return cnt;
}
struct number {
    int num;
    bool operator<(const number& a) const
    {
        return a.num > num;
    }
};
int main()
{
    int n, q, k, t;
    cin >> n >> q;
    priority_queue<number> _num;
    while (n--) {
        cin >> t;
        _num.push({ t });
    }
    while (q--) {
        priority_queue<number> num = _num;
        cin >> k;
        while (k--) {
            number tmp = { count(num.top().num) };
            num.pop();
            num.push(tmp);
        }
        int ans = 0;
        while (!num.empty()) {
            ans = max(ans, num.top().num);
            num.pop();
        }
        cout << ans << endl;
    }
}