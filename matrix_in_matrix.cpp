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
#include <bits/stdc++.h>
using namespace std;
int matrix[2050][2050];
int res[2050][2050];
int most_beautiful(int a, int b, int l)
{
    int result = matrix[a][b];
    for (int i = a; i < a + l; i++)
        for (int j = b; j < b + l; j++)
            result = result > matrix[i][j] ? result : matrix[i][j];
    return result;
}
int main()
{
    int n, m, l;
    cin >> n >> m >> l;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> matrix[i][j];
    for (int i = 0; i < n - l + 1; i++){
        for (int j = 0; j < m - l + 1; j++)
            cout << most_beautiful(i, j, l) << ' ';
        cout << '\n';
    }
}