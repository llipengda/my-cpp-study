#include <algorithm>
#include <stdexcept>

namespace pdli {
template <typename T>
class priority_queue {
public:
    typedef T* iterator;
    priority_queue();
    priority_queue(size_t size);
    priority_queue(const priority_queue& other);
    priority_queue& operator=(const priority_queue& other);
    ~priority_queue() noexcept;
    void pop();
    void push(const T& item);
    void just_push(const T& item);
    void clear();
    bool empty() const;
    iterator begin() const;
    iterator end() const;
    T& top() const;
    size_t size() const;
    void build_heap();

protected:
    T* entry;
    size_t count;
    size_t _size;

private:
    void _M_fit();
    void _M_insert_heap_head(const T& item);
    void _M_build_heap();
    void _M_insert_heap(const T& item, size_t l, size_t r);
};

template <typename T>
priority_queue<T>::priority_queue() {
    count = 0;
    _size = 100;
    entry = new T[_size + 1];
}

template <typename T>
priority_queue<T>::priority_queue(size_t size) {
    count = 0;
    _size = size;
    entry = new T[_size + 1];
}

template <typename T>
priority_queue<T>::~priority_queue() noexcept {
    delete[] entry;
}

template <typename T>
void priority_queue<T>::pop() {
    if (count == 0) throw std::underflow_error("underflow");
    T _last = entry[count - 1];
    _M_insert_heap_head(_last);
    count--;
}

template <typename T>
void priority_queue<T>::push(const T& item) {
    if (count >= _size) {
        _M_fit();
    }
    entry[count] = item;
    T cur = count;
    T parent = (cur - 1) / 2;
    while (cur > 0 && entry[parent] < item) {
        entry[cur] = entry[parent];
        cur = parent;
        parent = (cur - 1) / 2;
    }
    entry[cur] = item;
    ++count;
}

template <typename T>
void priority_queue<T>::just_push(const T& item) {
    if (count >= _size) {
        _M_fit();
    }
    entry[count++] = item;
}

template <typename T>
T& priority_queue<T>::top() const {
    if (count == 0) throw std::underflow_error("underflow");
    return entry[0];
}

template <typename T>
bool priority_queue<T>::empty() const {
    return count == 0;
}

template <typename T>
void priority_queue<T>::clear() {
    count = 0;
}

template <typename T>
size_t priority_queue<T>::size() const {
    return count;
}

template <typename T>
void priority_queue<T>::_M_fit() {
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
typename priority_queue<T>::iterator priority_queue<T>::begin() const {
    return &entry[0];
}

template <typename T>
typename priority_queue<T>::iterator priority_queue<T>::end() const {
    return &entry[count];
}

template <typename T>
void priority_queue<T>::_M_insert_heap(const T& item, size_t l, size_t r) {
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
void priority_queue<T>::_M_insert_heap_head(const T& item) {
    _M_insert_heap(item, 0, count);
}

template <typename T>
void priority_queue<T>::build_heap() {
    for (int i = count / 2 - 1; i >= 0; i--) {
        T cur = entry[i];
        _M_insert_heap(cur, i, count);
    }
}
} // namespace pdli
