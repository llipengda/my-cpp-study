/*
http://code.mynereus.com/#/class/homework/practical/1
HINT 题目描述
(中序波兰式求解) 请编写程序求解中序波兰式的值。表达式中可能的运算符有+，-，*，/，（）。
HINT 【输入】
中序波兰式
HINT 【输出】
波兰式的值 //输出的数据类型符合C/C++对表达式求值的定义，即表达式的输出类型由高精度的运算数来决定。
浮点型保留小数点后的3位小数
例如：
【输入】2*(4+5)-12
【输出】6
【输入】2*2.5
【输出】5.000
备注：
（1）对于80%的测试数据运算数中仅仅包含正整数；
（2）对于10%的测试数据运算数中包含有浮点数；
（3）对于10%的测试数据运算数中包含有负数；
*/
#include <stdexcept>

const int maxstack = 10000;
template <typename T>
class MyStack {
public:
    MyStack();
    void pop();
    void push(const T& item);
    size_t size() const;
    void clear();
    bool full() const;
    bool empty() const;
    T top() const;

protected:
    T entry[maxstack];
    size_t count;
};

template <typename T>
MyStack<T>::MyStack() {
    count = 0;
}

template <typename T>
void MyStack<T>::pop() {
    if (count == 0) throw std::underflow_error("underflow");
    count--;
}

template <typename T>
void MyStack<T>::push(const T& item) {
    if (count >= maxstack) throw std::overflow_error("overflow");
    entry[count++] = item;
}

template <typename T>
T MyStack<T>::top() const {
    if (count == 0) throw std::underflow_error("underflow");
    return entry[count - 1];
}

template <typename T>
bool MyStack<T>::full() const {
    return count >= maxstack;
}

template <typename T>
bool MyStack<T>::empty() const {
    return count == 0;
}

template <typename T>
void MyStack<T>::clear() {
    count = 0;
}

template <typename T>
size_t MyStack<T>::size() const {
    return count;
}

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;
int main() {
    string str;
    cin >> str;
    if (isdigit(str[str.size() - 1])) str.push_back('#');
    MyStack<char> op;
    MyStack<string> num;
    int tmp = 0;
    char pre = 0;
    bool isDouble = false;
    int f = 1;
    bool existDouble = false;
    int decimalDigits = 0;
    for (auto i : str) {
        if (isdigit(i)) {
            tmp = tmp * 10 + i - '0';
            if (isDouble) decimalDigits++;
        } else if (i == '.') {
            isDouble = true;
            existDouble = true;
        } else if (i == '-' && pre != ')' && !isdigit(pre)) {
            f = -1;
        } else {
            if (isdigit(pre)) {
                if (isDouble) {
                    num.push(to_string(f * tmp / (double)pow(10, decimalDigits)));
                    isDouble = false;
                } else {
                    num.push(to_string(f * tmp));
                }
            }
            tmp = 0;
            decimalDigits = 0;
            f = 1;
            if (op.empty()) {
                op.push(i);
            } else {
                switch (i) {
                    case '+':
                    case '-':
                        if (op.top() == '(') {
                            op.push(i);
                        } else {
                            while (!op.empty() && op.top() != '(') {
                                num.push(string(1, op.top()));
                                op.pop();
                            }
                            op.push(i);
                        }
                        break;
                    case '*':
                    case '/':
                        if (op.top() != '*' && op.top() != '/') {
                            op.push(i);
                        } else {
                            while ((op.top() == '*' || op.top() == '/') && !op.empty()) {
                                num.push(string(1, op.top()));
                                op.pop();
                            }
                            op.push(i);
                        }
                        break;
                    case ')':
                        while (op.top() != '(') {
                            num.push(string(1, op.top()));
                            op.pop();
                        }
                        op.pop();
                        break;
                    case '(':
                        op.push(i);
                        break;
                    default:
                        break;
                }
            }
        }
        pre = i;
    }
    while (!op.empty()) {
        num.push(string(1, op.top()));
        op.pop();
    }
    MyStack<string> _num;
    while (!num.empty()) {
        _num.push(num.top());
        num.pop();
    }
    if (existDouble) {
        MyStack<double> number;
        while (!_num.empty()) {
            if (isdigit(_num.top()[0]) || _num.top().size() != 1) {
                number.push(stod(_num.top()));
            } else {
                double b = number.top();
                number.pop();
                double a = number.top();
                number.pop();
                switch (_num.top()[0]) {
                    case '+':
                        number.push(a + b);
                        break;
                    case '-':
                        number.push(a - b);
                        break;
                    case '*':
                        number.push(a * b);
                        break;
                    case '/':
                        if (b == 0) throw runtime_error("devision by zero");
                        number.push(a / b);
                        break;
                    default:
                        break;
                }
            }
            _num.pop();
        }
        cout << fixed << setprecision(3) << number.top() << endl;
    } else {
        MyStack<int> number;
        while (!_num.empty()) {
            if (isdigit(_num.top()[0]) || _num.top().size() != 1) {
                number.push(stoi(_num.top()));
            } else {
                int b = number.top();
                number.pop();
                int a = number.top();
                number.pop();
                switch (_num.top()[0]) {
                    case '+':
                        number.push(a + b);
                        break;
                    case '-':
                        number.push(a - b);
                        break;
                    case '*':
                        number.push(a * b);
                        break;
                    case '/':
                        if (b == 0) throw runtime_error("devision by zero");
                        number.push(a / b);
                        break;
                    default:
                        break;
                }
            }
            _num.pop();
        }
        cout << number.top() << endl;
    }
}