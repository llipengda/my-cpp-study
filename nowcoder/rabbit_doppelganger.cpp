/*
链接：https://ac.nowcoder.com/acm/contest/18839/1040
来源：牛客网
HINT 题目描述
白兔学会了分身术。
一开始有一只白兔，接下来会进行 k 轮操作，每一轮中每一只白兔都会变成 p 只白兔。
要求 k 轮后白兔的总数恰好为 n。
要求找到两个正整数 p, k, 最大化 p+k
HINT 输入描述:
输入一个正整数n(2<=n<=1018)
HINT 输出描述:
输出一个整数，p+k的最大值
*/
// HINT: p^k = n, 要使 p+k 最大，则 k = 1.
#include <bits/stdc++.h>
using namespace std;
int main()
{
    long long n;
    cin >> n;
    cout << n + 1;
}