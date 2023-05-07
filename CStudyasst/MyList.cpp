#include <stdexcept>

template <typename T>
class MyList {
    struct ListNode {
        T entry;
        ListNode* next;
        ListNode() : next(nullptr) {}
        ListNode(const T& item, ListNode* add_on = nullptr) : entry(item), next(add_on) {}
        friend bool operator==(const ListNode& lhs, const ListNode& rhs) {
            return lhs.entry == rhs.entry && lhs.next == rhs.next;
        }
    };
    class ListIterator {
    public:
        ListIterator() = default;
        ~ListIterator() = default;
        ListIterator(ListNode* node) : _Node(node) {}
        ListIterator(const ListIterator& other) { _Node = other._Node; }
        T& operator*() const { return _Node->entry; }
        T* operator->() const { return static_cast<T*>(&(_Node->entry)); }
        ListIterator& operator++(int) {
            ListIterator* tmp = new ListIterator(*this);
            _Node = _Node->next;
            return *tmp;
        }
        ListIterator operator++() {
            _Node = _Node->next;
            return *this;
        }
        friend bool operator==(const ListIterator& lhs, const ListIterator& rhs) {
            return lhs._Node == rhs._Node;
        }
        friend bool operator!=(const ListIterator& lhs, const ListIterator& rhs) {
            return !(lhs == rhs);
        }
        friend ListIterator& operator+(const ListIterator& lhs, const size_t& rhs) {
            ListIterator* ans = new ListIterator(lhs);
            for (size_t i = 0; i < rhs; i++) {
                (*ans)++;
            }
            return *ans;
        }
        ListNode* _Node;
    };

public:
    typedef MyList::ListIterator iterator;
    typedef MyList::ListNode node;
    MyList() : head(nullptr) {}
    MyList(const MyList& other);
    ~MyList();
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
    void insert(const T& item);
    void remove(const T& value);
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);
    void erase(size_t pos);
    void erase(size_t first, size_t last);
    iterator begin() const;
    iterator end() const;
    T& back() const;
    T& front() const;
    MyList& operator=(const MyList& other);
    void insertion_sort();

protected:
    node* head;
};

template <typename T>
MyList<T>::MyList(const MyList& other) {
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
bool MyList<T>::empty() const {
    return head == nullptr;
}

template <typename T>
size_t MyList<T>::size() const {
    size_t cnt = 0;
    for (node* cur = head; cur != nullptr; cur = cur->next) cnt++;
    return cnt;
}

template <typename T>
void MyList<T>::push_back(const T& item) {
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
void MyList<T>::insert(const T& item) {
    push_back(item);
}

template <typename T>
void MyList<T>::pop_back() {
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
T& MyList<T>::back() const {
    node* cur;
    for (cur = head; cur->next != nullptr; cur = cur->next)
        ;
    if (cur == nullptr) throw std::underflow_error("underflow");
    return cur->entry;
}

template <typename T>
void MyList<T>::clear() {
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
MyList<T>::~MyList() {
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
typename MyList<T>::iterator MyList<T>::begin() const {
    return iterator(head);
}

template <typename T>
typename MyList<T>::iterator MyList<T>::end() const {
    return iterator(nullptr);
}

template <typename T>
void MyList<T>::insert(iterator pos, const T& item) {
    node *cur, *pre;
    if (pos._Node == head) {
        head = new node(item, head);
        return;
    }
    for (pre = head; pre->next != pos._Node; pre = pre->next)
        ;
    cur = pre->next;
    pre->next = new node(item, cur);
}

template <typename T>
void MyList<T>::insert(size_t pos, const T& item) {
    insert(begin() + pos, item);
}

template <typename T>
typename MyList<T>::iterator MyList<T>::erase(iterator pos) {
    node *cur, *pre;
    iterator res(pos._Node->next);
    if (pos._Node == head) {
        node* temp = head;
        head = temp->next;
        delete temp;
        return res;
    }
    for (pre = head; pre->next != pos._Node; pre = pre->next)
        ;
    cur = pre->next;
    pre->next = cur->next;
    if (cur == nullptr) throw std::underflow_error("underflow");
    delete cur;
    return res;
}

template <typename T>
void MyList<T>::erase(size_t pos) {
    erase(begin() + pos);
}

template <typename T>
void MyList<T>::erase(size_t first, size_t last) {
    erase(begin() + first, begin() + last);
}

template <typename T>
void MyList<T>::reverse() {
    MyList<T> temp(*this);
    clear();
    while (!temp.empty()) {
        push_back(temp.back());
        temp.pop_back();
    }
}

template <typename T>
MyList<T>& MyList<T>::operator=(const MyList<T>& other) {
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
typename MyList<T>::iterator MyList<T>::erase(iterator first, iterator last) {
    for (auto it = first; it != last; it = erase(it))
        ;
    return last;
}

template <typename T>
void MyList<T>::push_front(const T& item) {
    insert(begin(), item);
}

template <typename T>
void MyList<T>::pop_front() {
    erase(begin());
}

template <typename T>
T& MyList<T>::front() const {
    if (head == nullptr) throw std::underflow_error("underflow");
    return head->entry;
}

template <typename T>
void MyList<T>::remove(const T& value) {
    for (auto it = begin(); it != end();) {
        if (*it == value) {
            it = erase(it);
        } else {
            it++;
        }
    }
}

template <typename T>
void MyList<T>::insertion_sort() {
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