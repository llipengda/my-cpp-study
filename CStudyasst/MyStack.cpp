#include <algorithm>
#include <iostream>
#include <stdexcept>


const int maxstack = 500;
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
    void quick_sort();
    void print() const;

protected:
    T entry[maxstack];
    size_t count;

private:
    void _M_quick_sort(int l, int r);
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

template <typename T>
void MyStack<T>::_M_quick_sort(int l, int r) {
    static int i = 0;
    ++i;
    if (l >= r) return;
    std::swap(entry[l], entry[r - 1]);
    int pos = l;
    int pivot = entry[l];
    for (int i = l + 1; i < r; i++) {
        if (entry[i] < pivot) {
            pos++;
            std::swap(entry[pos], entry[i]);
        }
    }
    std::swap(entry[l], entry[pos]);
    if (i == 1) {
        print();
    }
    _M_quick_sort(l, pos);
    _M_quick_sort(pos + 1, r);
}

template <typename T>
void MyStack<T>::quick_sort() {
    _M_quick_sort(0, count);
}

template <typename T>
void MyStack<T>::print() const {
    for (int i = 0; i < count; i++) {
        std::cout << entry[i] << " \n"[i == count - 1];
    }
}

int main() {
    MyStack<int> s;
    int n;
    std::cin >> n;
    while (n--) {
        int t;
        std::cin >> t;
        s.push(t);
    }
    s.quick_sort();
    s.print();
}