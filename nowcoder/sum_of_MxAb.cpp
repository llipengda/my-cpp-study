/*
链接：https://ac.nowcoder.com/acm/contest/46810/J
来源：牛客网
HINT 题目描述
Tokitsukaze 最近对最大值与绝对值有了兴趣。
她有一个长度为 n 的序列 a。
定义 MxAb(i,j)=max(∣a_i​ −a_j​∣,∣a_i​ +a_j​∣)
Tokitsukaze 想知道对于所有的 i,j (1 ≤ i,j ≤ n)，MxAb(i,j)的和为多少。
即求下列式子 ∑_{i=1}^n​ ∑_{j=1}^n​ MxAb(i,j)
HINT 输入描述:
第一行包含一个整数 T (1 ≤ T ≤ 10)，表示 T 组测试数据。
对于每组测试数据：第一行包含一个整数 n (1 ≤ n ≤ 10^5)。第二行包含 n 个整数 a_1​ ,a_2​ ,…,a_n​  (−10^5 ≤ a_i​ ≤ 10^5)。
HINT 输出描述:
对于每组测试数据，输出一个整数表示答案。
*/
//~ 分情况考虑 MxAb 的值
//~ a_i,a_j > 0 时，MxAb(i,j) = a_i + a_j = |a_i|+|a_j|;
//~ a_i,a_j < 0 时，MxAb(i,j) = |a_i + a_j| = |a_i|+|a_j|;
//~ a_i > 0 , a_j < 0 （或 a_i < 0, a_j > 0）时，MxAb(i,j) = |a_i - a_j|(或 |a_j - a_i|) = |a_i|+|a_j|.
//~ 因此， ∑_{i=1}^n​ ∑_{j=1}^n​ MxAb(i,j) = 2n * ∑_{i=1}^n |a_i|. 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        ll ans = 0;
        for (int i = 0; i < n;i++){
            int t;
            cin >> t;
            ans += abs(t);
        }
        ans *= 2*n;
        cout << ans << endl;
    }
}