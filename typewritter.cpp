/*
描述
你的键盘出现了奇妙的故障，虽然所有的键都可以正常工作，但是键盘上的 “Home” 或 “End” 键有时候会莫名其妙地自动按下。但是盲打很熟练的你一般习惯关闭显示器打字，因为这样很酷。
现在你正在打一段文本，假设你已经知道这段文本以及 “Home” 和 “End” 键会什么时候出现故障自行按下。请你编写一个程序，求出你最后打出的文本。
输入描述
输入数据有多组。
每组数据为一行一个字符串，其中包含字母、数字、下划线和两个特别的标点 “[” 和 “]”。
其中 “[” 代表输入到此时 “Home” 键会被按下，而 “]” 则代表输入到此时 “End” 键会被按下。
输出描述
对于每组数据，请在一行之内输出最后你打出的文本。
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    list<char> str;
    char ch;
    auto t = str.begin();
    while (~(ch = getchar())) {
        if (ch == '\n'){
            for(auto i : str)
                cout << i;
            cout << '\n';
            str.clear();
            t = str.begin();
        }
        else if (ch == '[')
            t = str.begin();
        else if (ch == ']')
            t = str.end();
        else
            str.insert(t, ch);
    }
}