/*
HINT 描述
你需要开发一种仅适用于正确括号序列（缩写为 CBS）的文本编辑器。
众所周知，一个括号序列如果是合法的，则序列任意位置之前左括号数量大等于右括号数量。
例如，序列 “(())()”、“()” 和 “(())” 是合法的括号序列，而 “(”、“(()” 和 “(()))(” 是不合法的。
在 CBS 的括号序列中，左括号和右括号互为配对的条件是左括号和右括号之间的子序列也是合法的括号序列。
例如，在 “(()(()))” 中：
第一个括号与第八个括号配对；
第二个括号与第三个括号配对；
第四个括号与第七个括号配对；
第五个括号与第六个括号配对。
你的的编辑器在使用 CBS 期间其光标占据其中一个括号的整个位置（而不是括号之间的位置！），且仅支持三种操作：
«L» - 将光标向左移动一个位置；
«R» - 将光标向右移动一个位置；
«D» - 删除光标所在的括号，删除与其配对的括号以及它们之间的所有括号（即，删除光标所在的括号和与其配对的括号之间的子字符串）。
操作 “D” 后，光标移动到还未删除的右侧的括号。如果没有这样的括号（即后面已经没有括号了），则光标移动到左侧的括号。
你的编辑器不支持所有不正确的操作（如将光标移到 CBS 的末尾，删除整个 CBS 等）。
HINT 输入描述
第一行包含三个正整数 n、m 和 p。分别表示括号数、操作数和光标的初始位置。括号序列从 1 到 n 编号。保证 n 是偶数。
第二行是包含 n 个字符的字符串，表示初始的括号序列。
第三行包含由 m 个字符 “L”、“R” 和 “D” 组成的字符串，表示操作序列。可以保证给定的操作不会将光标移到括号序列之外，并且在所有操作之后，括号序列将是非空的。
HINT 输出描述
输出经过所有操作之后剩下的括号序列。
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m, p;
    cin >> n >> m >> p;
    list<char> parentheses;
    parentheses.push_back('#');
    while (n--) {
        char ch;
        cin >> ch;
        parentheses.push_back(ch);
    }
    parentheses.push_back('#');
    auto it = parentheses.begin();
    while (p--)
        it++;
    while (m--) {
        char ch;
        cin >> ch;
        if (ch == 'L')
            it--;
        else if (ch == 'R')
            it++;
        else if (ch == 'D') {
            if (*it == ')') {
                parentheses.erase(it);
                it--;
                int leftp = 1;
                while (leftp) {
                    if (*it == '(')
                        leftp--;
                    else if (*it == ')')
                        leftp++;
                    parentheses.erase(it);
                    it--;
                }
                it++;
            } else if (*it == '(') {
                parentheses.erase(it);
                int rightp = 1;
                while (rightp) {
                    if (*it == '(')
                        rightp++;
                    else if (*it == ')')
                        rightp--;
                    parentheses.erase(it);
                }
            }
            if (*it == '#')
                it--;
        }
    }
    it = parentheses.begin();
    it++;
    for (; *it != '#'; it++)
        cout << *it;
}