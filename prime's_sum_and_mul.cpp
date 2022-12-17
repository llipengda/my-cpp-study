#include <bits/stdc++.h>
using namespace std;
bool isprime(int);
int main()
{
    int input;
    cin >> input;
    int a, b, mul = 0;
    for (int i = 1; i <= input / 2; i++) {
        a = i;
        b = input - i;
        if (isprime(a) && isprime(b))
            mul = mul > a * b ? mul : a * b;
    }
    cout << mul;
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