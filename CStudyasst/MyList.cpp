#include <stdexcept>

namespace pdli {
template <typename T>
class list {
    struct list_node {
        T entry;
        list_node* next;
        list_node() : next(nullptr) {}
        list_node(const T& item, list_node* add_on = nullptr) : entry(item), next(add_on) {}
        friend bool operator==(const list_node& lhs, const list_node& rhs) {
            return lhs.entry == rhs.entry && lhs.next == rhs.next;
        }
    };
    class list_iterator {
    public:
        list_node* _M_node;
        list_iterator() = default;
        ~list_iterator() noexcept = default;
        list_iterator(list_node* node) : _M_node(node) {}
        list_iterator(const list_iterator& other) { _M_node = other._M_node; }
        T& operator*() const { return _M_node->entry; }
        T* operator->() const { return static_cast<T*>(&(_M_node->entry)); }
        list_iterator operator++(int) {
            list_iterator tmp = *this;
            _M_node = _M_node->next;
            return tmp;
        }
        list_iterator operator++() {
            _M_node = _M_node->next;
            return *this;
        }
        friend bool operator==(const list_iterator& lhs, const list_iterator& rhs) {
            return lhs._M_node == rhs._M_node;
        }
        friend bool operator!=(const list_iterator& lhs, const list_iterator& rhs) {
            return !(lhs == rhs);
        }
        friend list_iterator& operator+(const list_iterator& lhs, const size_t& rhs) {
            list_iterator* ans = lhs;
            for (size_t i = 0; i < rhs; i++) {
                (*ans)++;
            }
            return *ans;
        }
    };

public:
    typedef list::list_iterator iterator;
    typedef list::list_node node;
    list() : head(nullptr) {}
    list(const list& other);
    list(const std::initializer_list<T>& list);
    ~list() noexcept;
    size_t size() const;
    bool empty() const;
    void push_back(const T& item);
    void push_front(const T& item);
    void pop_back();
    void pop_front();
    void clear();
    void reverse();
    void insert(iterator pos, const T& item);
    void insert(size_t pos, const T& item);
    void remove(const T& value);
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);
    void erase(size_t pos);
    void erase(size_t first, size_t last);
    iterator begin() const;
    iterator end() const;
    T& back() const;
    T& front() const;
    list& operator=(const list& other);
    void insertion_sort();
    void merge_sort();

protected:
    node* head = nullptr;

private:
    void _M_merge_sort(node*& list);
};

template <typename T>
list<T>::list(const list& other) {
    if (other.head == nullptr) return;
    node *cur, *pre;
    node* _head = other.head;
    cur = new node(other.head->entry);
    head = cur;
    while (_head->next != nullptr) {
        _head = _head->next;
        cur->next = new node(_head->entry, _head->next);
        pre = cur;
        cur = cur->next;
    }
}

template <typename T>
list<T>::list(const std::initializer_list<T>& list) {
    node* cur;
    for (const auto& i : list) {
        if (head == nullptr) {
            head = new node(i);
            cur = head;
        } else {
            cur->next = new node(i);
            cur = cur->next;
        }
    }
}

template <typename T>
bool list<T>::empty() const {
    return head == nullptr;
}

template <typename T>
size_t list<T>::size() const {
    size_t cnt = 0;
    for (node* cur = head; cur != nullptr; cur = cur->next) cnt++;
    return cnt;
}

template <typename T>
void list<T>::push_back(const T& item) {
    node *cur, *pre;
    if (head == nullptr) {
        cur = new node(item);
        head = pre = cur;
        return;
    }
    for (cur = head; cur->next != nullptr; cur = cur->next)
        ;
    node* new_node = new node(item);
    cur->next = new_node;
}

template <typename T>
void list<T>::pop_back() {
    node *cur, *pre;
    for (cur = head; cur->next != nullptr; cur = cur->next)
        ;
    if (cur == head) {
        delete cur;
        head = cur = pre = nullptr;
        return;
    }
    for (pre = head; pre->next != cur; pre = pre->next)
        ;
    if (cur == nullptr) throw std::underflow_error("underflow");
    delete cur;
    pre->next = nullptr;
    cur = pre;
    for (pre = head; pre->next != cur && pre->next != nullptr; pre = pre->next)
        ;
}

template <typename T>
T& list<T>::back() const {
    node* cur;
    for (cur = head; cur->next != nullptr; cur = cur->next)
        ;
    if (cur == nullptr) throw std::underflow_error("underflow");
    return cur->entry;
}

template <typename T>
void list<T>::clear() {
    node *cur, *pre;
    if (head == nullptr) return;
    pre = head;
    cur = head->next;
    while (cur != nullptr) {
        delete pre;
        pre = cur;
        cur = cur->next;
    }
    delete pre;
    pre = head = cur = nullptr;
}

template <typename T>
list<T>::~list() noexcept {
    node *cur, *pre;
    if (head == nullptr) return;
    pre = head;
    cur = head->next;
    while (cur != nullptr) {
        delete pre;
        pre = cur;
        cur = cur->next;
    }
    delete pre;
}

template <typename T>
typename list<T>::iterator list<T>::begin() const {
    return iterator(head);
}

template <typename T>
typename list<T>::iterator list<T>::end() const {
    return iterator(nullptr);
}

template <typename T>
void list<T>::insert(iterator pos, const T& item) {
    node *cur, *pre;
    if (pos._M_node == head) {
        head = new node(item, head);
        return;
    }
    for (pre = head; pre->next != pos._M_node; pre = pre->next)
        ;
    cur = pre->next;
    pre->next = new node(item, cur);
}

template <typename T>
void list<T>::insert(size_t pos, const T& item) {
    insert(begin() + pos, item);
}

template <typename T>
typename list<T>::iterator list<T>::erase(iterator pos) {
    node *cur, *pre;
    iterator res(pos._M_node->next);
    if (pos._M_node == head) {
        node* temp = head;
        head = temp->next;
        delete temp;
        return res;
    }
    for (pre = head; pre->next != pos._M_node; pre = pre->next)
        ;
    cur = pre->next;
    pre->next = cur->next;
    if (cur == nullptr) throw std::underflow_error("underflow");
    delete cur;
    return res;
}

template <typename T>
void list<T>::erase(size_t pos) {
    erase(begin() + pos);
}

template <typename T>
void list<T>::erase(size_t first, size_t last) {
    erase(begin() + first, begin() + last);
}

template <typename T>
void list<T>::reverse() {
    list<T> temp(*this);
    clear();
    while (!temp.empty()) {
        push_back(temp.back());
        temp.pop_back();
    }
}

template <typename T>
list<T>& list<T>::operator=(const list<T>& other) {
    node *cur, *pre;
    node* _head = other.head;
    cur = new node(other.head->entry);
    head = cur;
    while (_head->next != nullptr) {
        _head = _head->next;
        cur->next = new node(_head->entry, _head->next);
        pre = cur;
        cur = cur->next;
    }
    return *this;
}

template <typename T>
typename list<T>::iterator list<T>::erase(iterator first, iterator last) {
    for (auto it = first; it != last; it = erase(it))
        ;
    return last;
}

template <typename T>
void list<T>::push_front(const T& item) {
    insert(begin(), item);
}

template <typename T>
void list<T>::pop_front() {
    erase(begin());
}

template <typename T>
T& list<T>::front() const {
    if (head == nullptr) throw std::underflow_error("underflow");
    return head->entry;
}

template <typename T>
void list<T>::remove(const T& value) {
    for (auto it = begin(); it != end();) {
        if (*it == value) {
            it = erase(it);
        } else {
            it++;
        }
    }
}

template <typename T>
void list<T>::insertion_sort() {
    node *last_sorted, *first_unsorted;
    if (head == nullptr) return;
    last_sorted = head;
    while (last_sorted->next != nullptr) {
        first_unsorted = last_sorted->next;
        node* pre = head;
        bool flag = false;
        for (node* cur = head; cur != first_unsorted; cur = cur->next) {
            if (cur == head) {
                if (first_unsorted->entry <= cur->entry) {
                    last_sorted->next = first_unsorted->next;
                    first_unsorted->next = cur;
                    head = first_unsorted;
                    flag = true;
                    break;
                }
            } else {
                if (first_unsorted->entry > pre->entry
                    && first_unsorted->entry <= cur->entry) {
                    last_sorted->next = first_unsorted->next;
                    pre->next = first_unsorted;
                    first_unsorted->next = cur;
                    flag = true;
                    break;
                }
            }
            pre = cur;
        }
        if (!flag) last_sorted = last_sorted->next;
    }
}

template <typename T>
void list<T>::merge_sort() {
    _M_merge_sort(head);
}

template <typename T>
void list<T>::_M_merge_sort(node*& list) {
    if (list == nullptr || list->next == nullptr) return;
    // divide
    node *mid = list, *sec = list, *pos = list;
    while (pos != nullptr && pos->next != nullptr) {
        mid = sec;
        sec = sec->next;
        pos = pos->next->next;
    }
    mid->next = nullptr;
    // sort
    _M_merge_sort(list);
    _M_merge_sort(sec);
    // merge
    node new_head;
    node* cur = &new_head;
    node* fst = list;
    while (fst != nullptr && sec != nullptr) {
        if (fst->entry < sec->entry) {
            cur->next = fst;
            fst = fst->next;
            cur = cur->next;
        } else {
            cur->next = sec;
            sec = sec->next;
            cur = cur->next;
        }
    }
    if (fst == nullptr) {
        cur->next = sec;
    } else {
        cur->next = fst;
    }
    list = new_head.next;
}
} // namespace pdli