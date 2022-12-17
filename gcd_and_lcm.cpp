/*--------------------------------------------------------
注意：仅在标有"Program"和"End"的注释行之间补充填写代码。
      请勿改动主函数main和其它任何已有内容。
---------------------------------------------------------*/

#include <fstream>
#include <iostream>
using namespace std;

// 计算a和b的最大公约数
int gcd(int a, int b)
{
    /**********Program**********/
    if (a < b) {
        int t = a;
        a = b;
        b = t;
    }
    int r;
    while (r = a % b) {
        a = b;
        b = r;
    }
    return b;
    /**********  End  **********/
}

// 计算a和b的最小公倍数
int lcm(int a, int b)
{
    /**********Program**********/
    return a * b / gcd(a, b);
    /**********  End  **********/
}

int main(int argc, char** argv)
{
    int u, v;
    cin >> u >> v;
    cout << "最大公约数：" << gcd(u, v) << endl;
    cout << "最小公倍数：" << lcm(u, v) << endl;
    return 0;
}
