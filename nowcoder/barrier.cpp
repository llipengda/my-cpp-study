/*
HINT 题目描述 
在数轴上的 [0,n] 区间，有 m 个障碍位于区间内的若干个整点坐标，将 [0, n] 区间分隔成了若干段。 
![](https://uploadfiles.nowcoder.com/images/20230203/0_1675429070571/3854A6D25CF13831EB05E50C37402FB3)
如上图所示，红色表示障碍，[0,10] 区间被三个障碍分隔形成了四段：[0,3],[3,6],[6,9],[9,10]，它们的长度分别为：3,3,3,1。 
现在可以从中移除任意多个障碍，称移除的障碍数量为 x，并称此时区间 [0,n] 内最长段的长度为 L。 
请最大化 L-x^2 的值，输出这个值。 
HINT 输入描述: 
第一行输入两个正整数 1 ≤ n ≤ 2 * 10^5,1 ≤ m≤min(n+1,10^5)，分别表示区间的右端点和障碍的数量。 
第二行输入 m 个互不相同的正整数 0≤ a_i ≤ n 以空格相隔，第 i 个正整数 a_i 表示第 i 个障碍的位置。
HINT 输出描述: 
第一行输出一个整数，表示答案。 
*/
#include <bits/stdc++.h>
#define endl '\n'
#define IO ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
#define REP(i, a, b) for (int i = a; i <= b; i++)
#define PER(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> barrier(m + 2);
    barrier[0] = 0, barrier[m + 1] = n;
    REP(i, 1, m)    cin >> barrier[i];
    int len, res = 0;
    REP(i, 0, m) {
        REP(j, 0, 500) {
            if (i + j > m)  break;
            len = barrier[i + j + 1] - barrier[i];
            res = max(res, len - j * j);
        }
    }
    cout << res << endl;
}