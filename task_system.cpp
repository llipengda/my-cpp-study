/*
描述
蒜头君设计了一个任务系统。这个系统是为了定时提醒蒜头君去完成一些事情。
系统大致如下，初始的时候，蒜头君可能会注册很多任务，每一个任务的注册如下:
Register Q_num Period
表示从系统启动开始，每过 Period 秒提醒蒜头君完成编号为 Qnum​的任务。
你能计算出蒜头君最先被提醒的 k 个任务吗？
输入描述
第一行输入n(0<n≤3000)，k(0<k≤10000)，其中 n 表示蒜头君注册的任务数量。
接下来 n 行，每行输入一条注册命令，其中 30000<qnum≤3000，0≤Period≤3000。
输出描述
顺序输出 k 行，表示依次提醒的任务的编号。如果同一时间有多个任务，最先提醒编号小的任务。
*/
#include <bits/stdc++.h>
using namespace std;
struct task {
    int num, next, period;
    bool operator<(const task& other) const
    {
        return (next > other.next) || (next == other.next && num > other.num);
    }
};
int main()
{
    int n, k;
    cin >> n >> k;
    string str;
    priority_queue<task> q;
    int num, period;
    while (n--)
    {
        cin >> str >> num >> period;
        task temp = { num, period, period};
        q.push(temp);
    }
    while (k--)
    {
        cout << q.top().num << endl;
        task temp = q.top();
        q.pop();
        temp.next += temp.period;
        q.push(temp);
    }
}