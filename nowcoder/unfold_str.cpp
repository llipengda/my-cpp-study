/*
来源：牛客网
链接：https://ac.nowcoder.com/acm/problem/16644
HINT 题目描述
在初赛普及组的“阅读程序写结果”的问题中，我们曾给出一个字符串展开的例子：如果在输入的字符串中，含有类似于“d-h”或“4-8”的子串，我们就把它当作一种简写，输出时，用连续递增的字母或数字串替代其中的减号，即，将上面两个子串分别输出为“defgh”和“45678”。在本题中，我们通过增加一些参数的设置，使字符串的展开更为灵活。具体约定如下：
（1）遇到下面的情况需要做字符串的展开：在输入的字符串中，出现了减号“-”，减号两侧同为小写字母或同为数字，且按照ASCII码的顺序，减号右边的字符严格大于左边的字符。
（2）参数p1：展开方式。p1=1时，对于字母子串，填充小写字母；p1=2时，对于字母子串，填充大写字母。这两种情况下数字子串的填充方式相同。p1=3时，不论是字母子串还是数字子串，都用与要填充的字母个数相同的星号“*”来填充。
（3）参数p2：填充字符的重复个数。p2=k表示同一个字符要连续填充k个。例如，当p2=3时，子串“d-h”应扩展为“deeefffgggh”。减号两侧的字符不变。
（4）参数p3：是否改为逆序：p3=1表示维持原有顺序，p3=2表示采用逆序输出，注意这时仍然不包括减号两端的字符。例如当p1=1、p2=2、p3=2时，子串“d-h”应扩展为“dggffeeh”。
（5）如果减号右边的字符恰好是左边字符的后继，只删除中间的减号，例如：“d-e”应输出为“de”，“3-4”应输出为“34”。如果减号右边的字符按照ASCII码的顺序小于或等于左边字符，输出时，要保留中间的减号，例如：“d-d”应输出为“d-d”，“3-1”应输出为“3-1”。
HINT 输入描述:
第1行为用空格隔开的3个正整数，依次表示参数p1，p2，p3。
第2行为一行字符串，仅由数字、小写字母和减号“-”组成。行首和行末均无空格。
HINT 输出描述:
输出一行，为展开后的字符串。
*/

#include <bits/stdc++.h>
#define endl '\n'
#define IO ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
#define REP(i, a, b) for (int i = a; i <= b; i++)
#define PER(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
int main() {
    int p1, p2, p3;
    cin >> p1 >> p2 >> p3;
    string str, res = "";
    cin >> str;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '-') {
            if (i == 0 || i == str.size() - 1
                || str[i + 1] == '-' || str[i - 1] == '-'
                || (isalpha(str[i - 1]) && isdigit(str[i + 1]))
                || (isalpha(str[i + 1]) && isdigit(str[i - 1]))
                || str[i - 1] >= str[i + 1]) {
                res.push_back('-');
                continue;
            }
            int pos = res.size();
            if (p1 == 1 || p1 == 2) {
                for (char j = str[i - 1] + 1; j < str[i + 1]; j++) {
                    if (p1 == 2 && isalpha(j)) j = toupper(j);
                    REP(k, 1, p2) {
                        res.push_back(j);
                    }
                    if (p1 == 2 && isalpha(j)) j = tolower(j);
                }
            } else {
                REP(j, 1, (str[i + 1] - str[i - 1] - 1) * p2) {
                    res.push_back('*');
                }
            }
            if (p3 == 2) {
                string tmp = res.substr(pos, res.size() - pos);
                reverse(tmp.begin(), tmp.end());
                res.replace(pos, res.size() - pos, tmp);
            }
        } else {
            res.push_back(str[i]);
        }
    }
    cout << res << endl;
}