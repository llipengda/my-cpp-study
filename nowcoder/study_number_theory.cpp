/*
链接：https://ac.nowcoder.com/acm/contest/46812/B
来源：牛客网
HINT 题目描述
请确保在尝试本题时了解数论中同余等式的相关内容。
如不了解同余以及同余等式的相关性质，可以到oiwiki进行学习了解后再尝试本题。
同余：https://oi-wiki.org//math/number-theory/basic/#%E5%90%8C%E4%BD%99
清楚姐姐最近在学习构造类问题，她现在遇到这样一个题目：
给定一个长度为N的数组c和一个质数m，请你构造另外两个数组 a,b满足：
    a_i​ ≡ a_N−1−i​ (modm)
    b_i​ ≡ −b_N−1−i​ (modm)
    c_i​ ≡ a_i​+b_i​ (modm)​
数组a,b,c的下标均从0开始计算。
如果可以构造出数组a,b，则首先输出Yes，然后输出任意一种解，否则只需输出一行一个字符串No。
'≡'为同余符号，它表示两个整数对m取余数的结果相同，对于负数取余数，若结果仍为负数，则需要加上m。
例如我们认为在模数m为77的情况下−12,−5,2同余，即−12≡−5≡2(mod7)。
HINT 输入描述:
第一行输入一个正整数和一个质数 N,m (1≤N≤10^5, 2≤m≤10^9+7)。
接下来一行输入N个非负整数 c_i​ (0≤c_i​<m) 表示数组c的值。
HINT 输出描述:
如果可以构造出这样的数组a和数组b，则首先输出Yes，
接下来输出两行，每行N个整数，用空格隔开,输出的整数范围应该在 [−2^31, 2^31)范围内，行末无需多余空格。
否则只需输出一行一个字符串No。
裁判程序将忽略大小写，你可以输出任意大小写的 ′YES′ 和 ′No′
*/
/**
 * ~ 设 j=n-i-1, 观察可知 ai=aj, bj=(-ai)
 * ~ 有 ai+bi≡ci (mod m)
 * ~   aj+bj=ai-bi (mod m) 
 * ~ 可解得 ai≡(ci+cj)/2 (mod m)
 * ~        bi≡(ci-cj)/2 (mod m)
 * ~ 在同余中，除以一个数相当于乘以它的乘法逆元
 * ~ 设 a mod m的乘法逆元为 b(当且仅当 a,m互质时 b存在)，则其满足 a*b≡1 (mod m)
 * ~ 对于 2和非 2质数 m，(m+1)/2 一定是它 mod m的一个乘法逆元
 * ~ 因此 m!=2时，可直接计算
 * ~ m=2 时，a,b中的值只能取 0,1，可直接进行枚举
**/
#include <bits/stdc++.h>
#define endl '\n'
#define IO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define N (ll)10e5 + 5ll
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
ll n, m;
ll a[N], b[N], c[N];
int main()
{
    cin >> n >> m;
    for (ll i = 0; i < n; i++)
        cin >> c[i];
    if (m == 2)
        for (ll i = 0; i < n / 2; i++) {
            ll j = n - 1 - i;
            bool flag = false;
            for (ll x = 0; x <= 1; x++) {
                for (ll y = 0; y <= 1; y++) {
                    if (c[i] == (x + y) % 2 && c[j] == (x - y + 2) % 2) {
                        a[i] = a[j] = x;
                        b[i] = y;
                        b[j] = (-y + 2) % 2;
                        flag = true;
                        break;
                    }
                    if (flag)
                        break;
                }
                if (flag)
                    break;
            }
            if (!flag) {
                cout << "NO";
                return 0;
            }
        }
    else {
        ll iv2 = (m + 1) / 2;
        for (ll i = 0; i < n / 2; i++) {
            ll j = n - 1 - i;
            a[i] = a[j] = (c[i] + c[j]) * iv2 % m;
            b[i] = ((c[i] - c[j]) % m + m) % m * iv2 % m;
            b[j] = (-b[i] % m + m) % m;
        }
    }
    if (n % 2) {
        a[n / 2] = c[n / 2];
        b[n / 2] = 0;
    }
    cout << "YES" << endl;
    for (int i = 0; i < n; i++)
        cout << a[i] << " \n"[i == n - 1];
    for (int i = 0; i < n; i++)
        cout << b[i] << " "[i == n - 1];
}