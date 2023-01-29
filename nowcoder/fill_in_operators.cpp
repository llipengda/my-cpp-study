/*
链接：https://ac.nowcoder.com/acm/contest/46811/G
来源：牛客网
HINT 题目描述
小红拿到了一个运算式，其中有一些地方可以填入'+'、'-'、'#'（不允许添加括号）。问最终是否可以使得等式成立。若可以，输出任意合法解。否则输出-1。
其中'+'和'-'代表四则运算的加法或者减法，'#'符号是小红发明的新运算符号：
a#b为a的a次方对b取模。例如 3#5 = 3^3 mod 5 = 2。
'#'符号的运算优先级和加减法是相同的（从左到右进行运算）。
在本题中，我们定义a#b当且仅当a和b都是正整数时是有意义的。
HINT 输入描述:
一个字符串，该字符串仅包含阿拉伯数字和问号、等号的字符串。保证字符串满足以下性质：
1.字符串仅由阿拉伯数字、'?'和'='组成，第一个字符保证是阿拉伯数字，不存在两个相邻的'?'字符。
2.保证有且仅有一个'='字符，'='字符保证不是字符串最后一个字符，'='的左边相邻和右边相邻的一定是阿拉伯数字，且'='右边所有字符均为阿拉伯数字。
3.所有阿拉伯数字表示的数均为不超过10^9的非负整数，若该数为正整数，则保证不包含前导零。
4.'?'的数量不超过12个。
HINT 输出描述:
如果存在合法解，请输出一个字符串，代表最终的运算式。否则输出-1。
请务必保证，你输出的字符串将所有的'?'修改成了'+'、'-'或者'#'，且未修改阿拉伯数字和等号。不得添加或删除新字符。
*/
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll num[20], ans, n;
char opr[20] /*operator*/;
ll pound(ll a, ll b, ll c) //~ 快速幂，计算 a^b mod c
{
    ll res = 1;
    a %= c;
    while (b) {
        if (b & 1 /* b % 2 == 1 */)
            res = res * a % c;
        b >>= 1 /* b /= 2 */;
        a = a * a % c;
    }
    return res;
}
void dfs(ll step, ll nans /*now_answer*/)
{
    if (step == n) {
        if (nans == ans) {
            for (int i = 1; i <= n - 1; i++)
                cout << num[i] << opr[i];
            cout << num[n] << '=' << ans;
            exit(0);
        }
        return;
    }
    opr[step] = '+';
    dfs(step + 1, nans + num[step + 1]);
    opr[step] = '-';
    dfs(step + 1, nans - num[step + 1]);
    if (nans > 0 && num[step + 1] > 0) {
        opr[step] = '#';
        dfs(step + 1, pound(nans, nans, num[step + 1]));
    }
}
int main()
{
    n = 0;
    while (++n) { //~ 从1开始
        cin >> num[n];
        char tmp = cin.get(); //~ 算式中一定是一个数字一个符号
        if (tmp == '=') {
            cin >> ans;
            break;
        }
    }
    dfs(1, num[1]);
    cout << "-1" << endl;
}