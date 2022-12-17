#include <bits/stdc++.h>
using namespace std;
bool check(const vector<int>& person);
int main()
{
    int n, m, count = 0;
    cin >> n >> m;
    vector<int> person(n, 1);
    vector<int> out;
    while (!check(person)) {
        for (int i = 0; i < n; i++) {
            if (person[i]) {
                count++;
                if (count == m) {
                    count = 0;
                    out.push_back(i + 1);
                    person[i] = 0;
                }
            }
        }
    }
    for (auto&& i : out)
        cout << i << " ";
}
bool check(const vector<int>& person)
{
    bool iszero = true;
    for (auto&& i : person) {
        if (i) {
            iszero = false;
            break;
        }
    }
    return iszero;
}