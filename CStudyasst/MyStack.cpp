#include <algorithm>
#include <stdexcept>

template <typename T>
class MyStack {
public:
    typedef T* iterator;
    MyStack();
    MyStack(size_t size);
    MyStack(const MyStack& other);
    MyStack& operator=(const MyStack& other);
    ~MyStack() noexcept;
    void pop();
    void push(const T& item);
    void clear();
    bool empty() const;
    iterator begin() const;
    iterator end() const;
    T& top() const;
    size_t size() const;
    void quick_sort();
    void heap_sort();

protected:
    T* entry;
    size_t count;
    size_t _size;

private:
    void _M_quick_sort(int l, int r);
    void _M_fit();
    void _M_build_heap();
    void _M_insert_heap(const T& item, size_t l, size_t r);
};

template <typename T>
MyStack<T>::MyStack() {
    count = 0;
    _size = 100;
    entry = new T[_size + 1];
}

template <typename T>
MyStack<T>::MyStack(size_t size) {
    count = 0;
    _size = size;
    entry = new T[_size + 1];
}

template <typename T>
MyStack<T>::~MyStack() noexcept {
    delete[] entry;
}

template <typename T>
void MyStack<T>::pop() {
    if (count == 0) throw std::underflow_error("underflow");
    count--;
}

template <typename T>
void MyStack<T>::push(const T& item) {
    if (count >= _size) {
        _M_fit();
    }
    entry[count++] = item;
}

template <typename T>
T& MyStack<T>::top() const {
    if (count == 0) throw std::underflow_error("underflow");
    return entry[count - 1];
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
void MyStack<T>::_M_fit() {
    size_t new_size = _size * 2;
    T* new_entry = new T[new_size + 1];
    for (int i = 0; i < _size; i++) {
        new_entry[i] = entry[i];
    }
    delete[] entry;
    _size = new_size;
    entry = new_entry;
}

template <typename T>
typename MyStack<T>::iterator MyStack<T>::begin() const {
    return &entry[0];
}

template <typename T>
typename MyStack<T>::iterator MyStack<T>::end() const {
    return &entry[count];
}

template <typename T>
void MyStack<T>::_M_quick_sort(int l, int r) {
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
    _M_quick_sort(l, pos);
    _M_quick_sort(pos + 1, r);
}

template <typename T>
void MyStack<T>::quick_sort() {
    _M_quick_sort(0, count);
}

template <typename T>
void MyStack<T>::_M_build_heap() {
    for (int i = count / 2 - 1; i >= 0; i--) {
        T cur = entry[i];
        _M_insert_heap(cur, i, count);
    }
}

template <typename T>
void MyStack<T>::_M_insert_heap(const T& item, size_t l, size_t r) {
    size_t pos = 2 * l + 1;
    while (pos < r) {
        if (pos < r - 1 && entry[pos] < entry[pos + 1]) {
            ++pos;
        }
        if (item < entry[pos]) {
            entry[l] = entry[pos];
            l = pos;
            pos = 2 * l + 1;
        } else {
            break;
        }
    }
    entry[l] = item;
}

template <typename T>
void MyStack<T>::heap_sort() {
    _M_build_heap();
    for (int i = count - 1; i > 0; i--) {
        T tmp = entry[i];
        entry[i] = entry[0];
        _M_insert_heap(tmp, 0, i);
    }
}