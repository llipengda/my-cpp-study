/*
来源：https://ac.nowcoder.com/acm/contest/46810/H
TIME LIMIT: 2s
HINT 题目描述
Tokitsukaze 有一个长度为 n 的序列 a，她想把这个序列划分成 k 个 非空子序列 。定义序列的值为这个序列中 只出现一次 的数字的个数。
 对于 k=1 ... n，Tokitsukaze 想知道把序列 a 划分成 k 个 非空子序列 后，所有子序列的值的和最大是多少。
 请注意，子序列不一定是连续的。 
HINT 输入描述:
第一行包含一个正整数 T (1 ≤ T ≤ 10)，表示测试数据的组数。
对于每组测试数据：
第一行包含一个整数 n (1 ≤ n ≤ 10^5)。
第二行包含 n 个整数 a_1, a_2, ..., a_n (1 ≤ a_i ≤ 10^5)。
HINT 输出描述:
对于每组数据，输出 n 个整数，第 i (1 ≤ i ≤ n) 个整数表示 k=i 时的答案。
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
const int N = 1e5 + 5;
void solve() {
    int n;
    cin >> n;
    vector<int> cnt(N, 0);
    REP(i, 1, n) {
        int tmp;
        cin >> tmp;
        cnt[tmp]++;
    }
    multiset<int> st;
    REP(i, 1, N - 1) {
        st.insert(cnt[i]);
    }
    ll lesum = 0, gecnt = st.size();
    REP(k, 1, n) {
        while (*st.begin() <= k && !st.empty()) {
            lesum += (ll)*st.begin();
            st.erase(st.begin());
            gecnt--;
        }
        cout << lesum + gecnt * (k - 1) << endl;
    }
}
int main() {
    IO;
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}