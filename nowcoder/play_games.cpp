/*
链接：https://ac.nowcoder.com/acm/contest/46813/D
来源：牛客网
HINT 题目描述
小沙和小雅在一起打游戏，因为赌气，他们想要比比看谁打通的关卡数更多，
在游戏过程中，他们两个人都可以获得一些奇怪的道具来帮助他们通关，
假设小沙和小雅都从第一关开始，他们必须一关一关通，只有通过了第 x 关，第 x+1 关才会解锁。
每次同时卡关他们各自会获得了一个道具，第 i 个道具可以使他们通过 [li, ri] 之间的每一关，
在获得每个道具之后，小沙想询问你目前已有的道具游玩下去，谁会领先，领先多少。
HINT 输入描述:
第一行输入一个数 n，代表 n 个发放道具，1≤n≤10^5。
接下来 n 行，每行输入两个整数 l,r 1≤l≤r≤10^9，代表小沙获得的游戏道具能帮助他通过哪些关卡。
接下来 n 行，每行输入两个整数 l,r 1≤l≤r≤10^9，代表小雅获得的游戏道具能帮助他通过哪些关卡。
HINT 输出描述:
对于每一次获得道具后，目前的领先状况。
每次询问共输出两行
第一行输出一行字符串代表答案。
如果小沙通过的更多输出”sa_win!"(不包含引号);
如果小雅通过的更多输出”ya_win!"(不包含引号);
如果通过的一样多输出”win_win!"(不包含引号)。
第二行输出一个整数代表多通过的关卡数。
*/
#include <bits/stdc++.h>
#define endl '\n'
#define IO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
pii s_levels[100005], y_levels[100005];
int s_pass[100005], y_pass[100005], n;
void merge(pii levels[], int pass[])
{
    int l = 0, r = 0;
    set<pii> st; //~ 使用set对数据进行自动排序，保证先取到较小的值
    for (int i = 0; i <= n; i++) {
        st.insert(levels[i]);
        auto beg = (*st.begin());
        while (beg.first <= r + 1) { //~ 保证只对可合并的数据进行处理
            r = max(r, beg.second);
            st.erase(st.begin()); //~ 删掉用过的数据，减小运算量
            if (st.empty())
                break;
            else
                beg = (*st.begin());
        }
        pass[i] = r;
    }
}
int main()
{
    IO;
    int l, r;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> l >> r;
        s_levels[i] = { l, r };
    }
    for (int i = 0; i < n; i++) {
        cin >> l >> r;
        y_levels[i] = { l, r };
    }
    merge(s_levels, s_pass);
    merge(y_levels, y_pass);
    for (int i = 0; i < n; i++) {
        if (s_pass[i] > y_pass[i]) {
            cout << "sa_win!" << endl;
            cout << s_pass[i] - y_pass[i] << endl;
        } else if (y_pass[i] > s_pass[i]) {
            cout << "ya_win!" << endl;
            cout << y_pass[i] - s_pass[i] << endl;
        } else {
            cout << "win_win!" << endl;
            cout << 0 << endl;
        }
    }
}