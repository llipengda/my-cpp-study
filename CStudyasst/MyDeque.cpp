#include <stdexcept>

const int maxqueue = 200;
template <typename T>
class MyDeque {
public:
    MyDeque();
    void push_back(const T& item);
    void push_front(const T& item);
    void pop_back();
    void pop_front();
    T front() const;
    T back() const;
    bool empty() const;
    bool full() const;
    size_t size() const;

protected:
    size_t count;
    size_t _front;
    size_t _rear;
    T entry[maxqueue];
};

template <typename T>
MyDeque<T>::MyDeque() {
    count = 0;
    _front = 0;
    _rear = -1;
}

template <typename T>
void MyDeque<T>::push_back(const T& item) {
    if (count >= maxqueue) throw std::overflow_error("owerflow");
    _rear = (_rear + 1) % maxqueue;
    entry[_rear] = item;
    count++;
}

template <typename T>
void MyDeque<T>::push_front(const T& item) {
    if (count >= maxqueue) throw std::overflow_error("owerflow");
    _front = (_front - 1 + maxqueue) % maxqueue;
    entry[_front] = item;
    count++;
}

template <typename T>
void MyDeque<T>::pop_front() {
    if (count <= 0) throw std::underflow_error("underflow");
    _front = (_front + 1) % maxqueue;
    count--;
}

template <typename T>
void MyDeque<T>::pop_back() {
    if (count <= 0) throw std::underflow_error("underflow");
    _rear = (_rear - 1 + maxqueue) % maxqueue;
    count--;
}

template <typename T>
T MyDeque<T>::front() const {
    if (count <= 0) throw std::underflow_error("underflow");
    return entry[_front];
}

template <typename T>
T MyDeque<T>::back() const {
    if (count <= 0) throw std::underflow_error("underflow");
    return entry[_rear];
}

template <typename T>
bool MyDeque<T>::full() const {
    return count >= maxqueue;
}

template <typename T>
bool MyDeque<T>::empty() const {
    return count == 0;
}

template <typename T>
size_t MyDeque<T>::size() const {
    return count;
}