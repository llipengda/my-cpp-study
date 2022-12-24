#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
int main()
{
    string s1, s2;
    int count = 0, address = 0;
    bool flag = false;
    cin >> s1;
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    while (1) {
        cin >> s2;
        transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
        if (!s1.compare(s2)) {
            count++;
            flag = true;
        }
        if (!flag)
            address = address + s2.size() + 1;
        char ch = getchar();
        if (ch == '\n' || ch == EOF)
            break;
    }
    if (!flag)
        cout << "-1";
    else
        cout << count << " " << address;
}