/*
链接：https://ac.nowcoder.com/acm/contest/46812/E
来源：牛客网
HINT 题目描述
清楚姐姐玩游戏打怪升级，一共有N只怪物，第i只怪物的生命值上限为 hi​ ，生命恢复速度为 vi​ ，清楚姐姐的攻击间隔为t，攻击力为a。
在每个时刻初，若怪物的生命值不满，则恢复 vi​ 点生命值，但是不能超过生命值上限 hi​ 。
在第 1,1+t,1+2⋅t,1+3⋅t,...,1+k⋅t 个时刻末，清楚姐姐可以选择一只怪物造成a点伤害，若此时怪物的生命值小于等于0，则该怪物死亡。
清楚姐姐想要知道自己至少在第几个时刻末可以杀死所有怪物，或者清楚姐姐永远也无法杀死所有怪物，则输出−1。
HINT 输入描述:
第一行输入三个整数 N,t,a (1≤N≤10^5, 1≤t≤10^6, 0≤a≤10^6)，分别表示怪物的数目，清楚姐姐的攻击间隔和攻击力。
接下来N行，每行输入两个整数 hi​,vi​ (1≤hi​≤10^6, 0≤vi​≤10^6)，分别表示每只怪物的生命值上限和生命恢复速度。
HINT 输出描述:
仅一个整数，表示清楚姐姐至少在第几个时刻末可以杀死所有怪物，
或者清楚姐姐永远也无法杀死所有怪物，则输出−1。
*/
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int main()
{
    ll N, t, a, time = 0;
    cin >> N >> t >> a;
    for (ll i = 1; i <= N; i++) {
        ll h, v;
        cin >> h >> v;
        if (h <= a)
            time += (i == 1 ? 1 : t);
        else if (t * v >= a) {
            cout << -1;
            exit(0);
        } else
            time += ((i == 1 ? 1 : t) + t * ((a - h) / (t * v - a) + ((a - h) % (t * v - a) != 0)));
            //~ 注意：这里使用 ceil() 函数会导致出错！！
    }
    cout << time;
}