#include <iostream>
using namespace std;
int a[1000010];
int n, j, i;
int main()
{
    a[1] = 1;
    a[2] = 1;
    for (i = 3; i <= 1000000; i++)
        a[i] = (a[i - 1] + a[i - 2]) % 1000;
    cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> j;
        cout << a[j] << endl;
    }
    return 0;
}