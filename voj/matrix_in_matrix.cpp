/*
描述
Y 是一个非常注重外表的人，当他检阅一个军训方阵时，他只会关注到方阵里“美丽值”最大的同学。
现在给定一个 n×m 的军训方阵中每个同学的美丽值 aij，请求出每个 l×l 子矩阵中的最大美丽值。
输入描述
第一行三个整数 n,m,l 用空格隔开，意义如题目所示。
接下来 n 行，每行 m 个整数表示该位置同学的美丽值。
输出描述
输出一个 (n−l+1)×(m−l+1) 的矩阵 B。矩阵 B 中的元素 bij表示以 (i,j) 为最左上角元素的 l×l 的子矩阵中的美丽值最大值。
*/
// BUG: test with TLE
#include <bits/stdc++.h>
using namespace std;
int matrix[2050][2050];
int st[2050][2050][11];
int n, m, l;
void init_st()
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            st[i][j][0] = matrix[i][j];
    for (int k = 1; (1 << k) <= n; k++)
        for (int i = 1; i + (1 << k) - 1 <= n; i++)
            for (int j = 1; j <= m; j++)
                st[i][j][k] = max(st[i][j][k - 1], st[i + (1 << (k - 1))][j][k - 1]);
}
int most_beautiful(int a, int b, int l)
{
    int k = log2(l);
    int result = 0;
    for (int i = b; i <= b + l - 1; i++)
        result = max(result, max(st[a][i][k], st[a + l - (1 << k)][i][k]));
    return result;
}
int main()
{
    scanf("%d %d %d", &n, &m, &l);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &matrix[i][j]);
    init_st();
    for (int i = 1; i <= n - l + 1; i++) {
        for (int j = 1; j <= m - l + 1; j++)
            printf("%d ", most_beautiful(i, j, l));
        putchar('\n');
    }
}