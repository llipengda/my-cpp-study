/*
链接：https://ac.nowcoder.com/acm/contest/18839/1002
来源：牛客网
HINT 题目描述
　　7254是一个不寻常的数，因为它可以表示为7254 = 39 x 186，这个式子中1~9每个数字正好出现一次
　　输出所有这样的不同的式子（乘数交换被认为是相同的式子）
　　结果小的先输出；结果相同的，较小的乘数较小的先输出。
HINT 输出描述:
　　每一行输出一个式子，式子中的等号前后空格、乘号（用字母x代表）前后空格
    较小的乘数写在前面
*/
// HINT next_primutation
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int num[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    do {
        int a = num[0] * 1000 + num[1] * 100 + num[2] * 10 + num[3];
        int b1 = num[4] * 10 + num[5];
        int c1 = num[6] * 100 + num[7] * 10 + num[8];
        int b2 = num[4];
        int c2 = num[5] * 1000 + num[6] * 100 + num[7] * 10 + num[8];
        if (a == b1 * c1)
            cout << a << " = " << b1 << " x " << c1 << endl;
        else if (a == b2 * c2)
            cout << a << " = " << b2 << " x " << c2 << endl;
    } while (next_permutation(num, num + 9));
}