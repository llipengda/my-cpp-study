#include <cmath>
#include <iostream>
using namespace std;
bool isprime(int);
int main()
{
    int n;
    bool flag;
    cin >> n;
    for (int i = 1; i < n - 1; i++) {
        if (isprime(i) && isprime(i + 2)) {
            cout << i << " " << i + 2 << endl;
            flag = true;
        }
    }
    if (flag == false)
        cout << "empty";
}
bool isprime(int n)
{
    if (n == 1)
        return false;
    else {
        for (int i = 2; i <= sqrt(n); i++)
            if (n % i == 0)
                return false;
    }
    return true;
}