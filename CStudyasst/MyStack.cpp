#include <stdexcept>

const int maxstack = 100;
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

private:
    T entry[maxstack];
    size_t count;
};

template <typename T>
MyStack<T>::MyStack() {
    count = 0;
    for (int i = 0; i < maxstack; i++) {
        entry[i] = 0;
    }
}

template <typename T>
void MyStack<T>::pop() {
    if (count == 0) throw std::underflow_error("underflow");
    entry[count - 1] = 0;
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
    for (size_t i = 0; i < count; i++) {
        entry[i] = 0;
    }
    count = 0;
}

template <typename T>
size_t MyStack<T>::size() const {
    return count;
}