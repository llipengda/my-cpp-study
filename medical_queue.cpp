/*
HINT 描述
ZZR 被分配了一个重要的任务，他要帮助医院协调医疗队列。
等待就诊的每个公民都将被分配一个唯一的数字，从 1 到 P (这里的 P 是当前的人口)。它们将被放入一个队列， 1 在 2 前面， 2 在 3 前面，以此类推。医院将从这个队列中逐一处理病人。一旦其中一个公民被服务，他们会立即从队伍的前面移到后面。
当然，有时会出现紧急情况——如果一个公民刚刚被一个蒸汽压路机碾过，你不能等到数十个公民去做常规检查后再接受治疗！因此，对于这些（希望是罕见的）情况，可以使用一个快速命令将一个人移到队列的前面。其他国家的相对秩序将保持不变。
给定处理命令和快速命令的顺序，输出当前服务的公民的编号。
HINT 输入描述
第一行两个数n,p，表示命令个数和公民个数。
接下来n行，每行为一个命令：
1：表示当前队列首部的公民被服务，被服务后自动放到队列末位。
2 x：表示将编号为x的公民移动到队列首部（不进行服务操作）。
3：询问当前队列首部的公民的编号（即下一个要被服务的公民编号）。
HINT 输出描述
对于每个3命令，输出一个数表示当前队列首部的公民的编号。
*/
// BUG: test with TLE
#include <bits/stdc++.h>
using namespace std;
int main()
{
    list<int> person;
    int n, p;
    cin >> n >> p;
    for (int i = 1; i <= p; i++)
        person.push_back(i);
    while (n--) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            int temp = person.front();
            person.pop_front();
            person.push_back(temp);
        } else if (cmd == 3) {
            cout << person.front() << endl;
        } else if (cmd == 2) {
            int m;
            cin >> m;
            person.remove(m);
            person.push_front(m);
        }
    }
}