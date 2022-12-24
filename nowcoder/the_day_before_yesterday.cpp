/*
链接：https://ac.nowcoder.com/acm/contest/19304/Q
来源：牛客网
HINT 题目描述
给定公元2000年到公元3000年之间的某一天，请你给出该天的前天是哪一天.
HINT 输入描述:
输入在一个日期，格式如"yyyy-mm-dd"，题目保证所有输入日期为合法日期。
HINT 输出描述:
在一行中输出日期，格式如"yyyy-mm-dd"。
*/
#include <bits/stdc++.h>
using namespace std;
bool isLeap(int n)
{
    if (n % 100 != 0 && n % 4 == 0)
        return true;
    else if (n % 400 == 0)
        return true;
    else
        return false;
}
int main()
{
    const int daysInMonth[] = { 29, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int y, m, d;
    int _y, _m, _d;
    scanf("%d-%d-%d", &y, &m, &d);
    if (d - 2 > 0) {
        _y = y;
        _m = m;
        _d = d - 2;
    } else if (d - 2 <= 0 && m - 1 > 0) {
        _y = y;
        _m = m - 1;
        _d = daysInMonth[(_m == 2 ? (isLeap(y) ? 0 : 2) : _m)] + (d - 2);
    } else {
        _y = y - 1;
        _m = 12;
        _d = 31 + (d - 2);
    }
    printf("%04d-%02d-%02d", _y, _m, _d);
}