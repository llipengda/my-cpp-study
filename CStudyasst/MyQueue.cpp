#include <stdexcept>

const int maxqueue = 5;
template <typename T>
class MyQueue {
public:
    MyQueue();
    void push(const T& item);
    void pop();
    T front() const;
    bool empty() const;
    bool full() const;

protected:
    size_t count;
    size_t _front;
    size_t _rear;
    T entry[maxqueue];
};

template <typename T>
MyQueue<T>::MyQueue() {
    count = 0;
    _front = 0;
    _rear = -1;
}

template <typename T>
void MyQueue<T>::push(const T& item) {
    if (count >= maxqueue) throw std::overflow_error("owerflow");
    _rear = (_rear + 1) % maxqueue;
    entry[_rear] = item;
    count++;
}

template <typename T>
void MyQueue<T>::pop() {
    if (count <= 0) throw std::underflow_error("underflow");
    _front = (_front + 1) % maxqueue;
    count--;
}

template <typename T>
T MyQueue<T>::front() const {
    if (count <= 0) throw std::underflow_error("underflow");
    return entry[_front];
}

template <typename T>
bool MyQueue<T>::full() const {
    return count >= maxqueue;
}

template <typename T>
bool MyQueue<T>::empty() const {
    return count == 0;
}