#include <bits/stdc++.h>
using namespace std;
int daysInMonthInLeapYear[]={31,29,31,30,31,30,31,31,30,31,30,31};
int daysInMonthInCommonYear[]={31,28,31,30,31,30,31,31,30,31,30,31};
vector<string> week={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
int isLeap(int n)
{
    if(((n%100!=0)&&(n%4==0))||(n%400==0))
        return 1;
    else return 0;
}
int main()
{
    int y,m,d;
    cin>>y>>m>>d;
    int days=0;
    for(int i=1900;i<y;i++)
        if(isLeap(i))
            days+=366;
        else days+=365;
    if(isLeap(y))
        for(int i=0;i<m-1;i++)
            days+=daysInMonthInLeapYear[i];
    else
        for(int i=0;i<m-1;i++)
            days+=daysInMonthInCommonYear[i];
    days+=d;
    cout<<week[days%7];
}