#include <bits/stdc++.h>
using namespace std;
int main()
{
    string key, in, out, _key;
    cin >> key >> in;
    for (int i = 0; i < in.size() / key.size(); i++)
        _key += key;
    _key.append(key.begin(), key.begin() + (in.size() - _key.size()));
    for (auto&& i : _key)
        if (isupper(i))
            i = tolower(i);
    for (int i = 0; i < in.size(); i++) {
        bool _isupper = false;
        if (isupper(in[i])) {
            in[i] = tolower(in[i]);
            _isupper = true;
        }
        char ch = ((in[i] - _key[i] + 'a') < 'a') ? (in[i] - _key[i] + 'a' + ('z' - 'a' + 1)) : (in[i] - _key[i] + 'a');
        if (_isupper)
            ch = toupper(ch);
        out.append(1, ch);
    }
    cout << out;
}