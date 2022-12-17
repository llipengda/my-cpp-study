/*--------------------------------------------------
注意：部分源程序给出如下。请勿改动主函数main和其它
      函数中的任何内容，仅在函数的花括号中填入所编
      写的若干语句。
--------------------------------------------------*/
#include <iostream>
using namespace std;
int days(struct date day);
struct date {
    int year;
    int month;
    int day;
};

int main()
{
    struct date today, term;
    int yearday, year, day;

    cin >> today.year >> today.month >> today.day;

    term.month = 12; /*设置变量的初始值：月*/
    term.day = 31; /*设置变量的初始值：日*/
    yearday = 0;

    /**********Program**********/
    for (int i = 1990; i < today.year; i++) {
        term.year = i;
        yearday += days(term);
    }
    yearday += days(today);
    /**********  End  **********/

    day = yearday % 5; /*求余数*/
    if (day > 0 && day < 4) {
        cout << "他在打鱼" << endl; /*打印结果*/
    } else {
        cout << "他在晒网" << endl;
    }
    return 0;
}

int days(struct date day) // 返回本年中自一月一日起的天数
{
    static int day_tab[2][13] = {
        {
            0,
            31,
            28,
            31,
            30,
            31,
            30,
            31,
            31,
            30,
            31,
            30,
            31,
        }, /*平均每月的天数*/
        {
            0,
            31,
            29,
            31,
            30,
            31,
            30,
            31,
            31,
            30,
            31,
            30,
            31,
        },
    };
    int i, lp;

    lp = (day.year % 4 == 0 && day.year % 100 != 0 || day.year % 400 == 0); /*判定year为闰年还是平年，lp=0为平年，非0为闰年*/
    for (i = 1; i < day.month; i++) //计算本年中自1月1日起的天数*/
        day.day += day_tab[lp][i];
    return day.day;
}