//比n小的质数
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
    int input, n = 0, count = 1, i = 3;
    cin >> input;
    if (input == 1)
        cout << "2" << endl;
    else {
        while (1) {
            for (int j = 2; j < i; j++) {
                if (!(i % j)) {
                    n++;
                    break;
                }
            }
            if (n == 0)
                count++;
            else
                n = 0;
            if (count == input) {
                cout << i << endl;
                break;
            }
            i += 2;
        }
    }
    return 0;
}