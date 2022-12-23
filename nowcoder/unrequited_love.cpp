/*
链接：https://ac.nowcoder.com/acm/contest/18839/1047
来源：牛客网
HINT 题目描述 
Chranos 是个数学天才。
一天，有一个可爱的小女孩追求 Chranos，他知道 Chranos 最喜欢当且仅当总质量为K克的时候的番茄炒蛋了。她希望通过美食俘获 Chranos 的胃，这样就一定可以和他在一起了吧！虽然小女孩有无限数量的食材，但是数学王国的番茄和蛋非常特殊，他们的质量分别为 N 克和 M 克。为了表现一颗完整的心、表达充足的爱意，所有的食材必须被用完。N 和 M 都是正整数且互素，制作过程中既不会凭空增加质量，也不会凭空消失质量。
Chranos 不希望小女孩打扰他学数学。他发现，并不是所有番茄炒蛋都是可以被制作出来的。他想找出最大的不可以被制作出的总质量 K 来拒绝小女孩，这样 Chranos 就可以永远和数学在一起了！
HINT 输入描述:
第一行为正整数 N 和 M (2 ≤ N ,M ≤ 50000).
HINT 输出描述:
输出最大的不可以被制作出的总质量 K。
*/
// HINT: [塞瓦维斯特定理]
// HINT: 对于 a,b > 0, 且 gcd(a,b) = 1, 使得方程 ax + by = c 无整数解的 c 的最大值为 a×b-a-b.
#include <bits/stdc++.h>
using namespace std;
int main()
{
    long long N, M;
    cin >> N >> M;
    cout << N * M - N - M;
}