/*
HINT 题目描述 
注：在本题中，我们会做一些与游戏本身不完全相同的设定，玩过游戏与否对理解题目没有影响。 
小橙汁和朋友们正在玩《球球大作战》，在这个游戏中有 n 个玩家，每个玩家将操作一个球，且初始时第 i 个玩家的球的大小为 a_i
n 个玩家之间将进行 n-1 次碰撞，每次碰撞发生在两个未淘汰的玩家之间： 
 1. 玩家 A 的球大小为 a_1，玩家 B 的球大小为 a_2。 
 2. 若玩家 A 的球的大小大于玩家 B 的球的大小，则玩家 B 被淘汰，且玩家 A 的球的大小变为 floor((a_1+a_2)/2)。反之亦然。
 3. 若两名玩家的球的大小相同，游戏系统将随机判定其中一名玩家被淘汰，另一名玩家的球的大小保持不变。 
这样，最终仅剩余一名玩家未淘汰，成为胜利者。 
对于每个玩家 1 ≤ i ≤ n ，询问是否存在一种碰撞顺序，使得该名玩家可以成为最终的胜利者。
HINT 输入描述: 
第一行输入一个正整数 2 ≤ n ≤ 10^5，表示玩家的数量。 
第二行输入 n 个正整数，第 i 个正整数 1≤ a_i ≤ 10^9 表示初始化时第 i 个玩家的球的大小。
HINT 输出描述: 
输出一个长度为 n 的仅有 '0' 和 '1' 组成的字符串，字符串的第 i 位为 1 当且仅当存在一种碰撞顺序，使得第 i 名玩家可以成为最终的胜利者。 
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
int n;
pii si[100005];
bool check(int pos) {
    priority_queue<int> q;
    REP(i, 1, n) {
        if (i != pos) {
            q.push(si[i].first);
        }
    }
    while (true) {
        int a = q.top();
        q.pop();
        if (q.empty())
            return a <= si[pos].first;
        int b = q.top();
        q.pop();
        q.push((a + b) / 2);
    }
}
int main()
{
    cin >> n;
    REP(i, 1, n) {
        cin >> si[i].first;
        si[i].second = i;
    }
    sort(si + 1, si + n + 1);
    int l = 1, r = n;
    while (l != r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    vector<int> ans(n + 1);
    REP(i, 1, n) {
        ans[si[i].second] = (i >= l ? 1 : 0);
    }
    REP(i, 1, n) {
        cout << ans[i];
    }
}