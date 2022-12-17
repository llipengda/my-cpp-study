#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int flag = 0;
    for (int x = 0;; x++) {
        for (int y = 0; y < x; y++) {
            if (x * (x + 1) / 2 - 2 * y == n) {
                cout << y <<" "<< x;
                flag = 1;
                break;
            }
        }
        if (flag == 1)
            break;
    }
}