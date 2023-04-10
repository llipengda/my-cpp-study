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
        ListIterator() {}
        ~ListIterator() {}
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
    MyList() : head(nullptr), cur(nullptr), pre(nullptr) {}
    MyList(const MyList& other);
    ~MyList();
    size_t size();
    bool empty() const;
    void push_back(const T& item);
    void push_front(const T& item);
    void pop_back();
    void pop_front();
    void clear();
    void reverse();
    void insert(iterator pos, const T& item);
    void remove(const T& value);
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);
    iterator begin() const;
    iterator end() const;
    T& back();
    T& front();
    MyList& operator=(const MyList& other);

protected:
    node* head;
    node* cur;
    node* pre;
};

template <typename T>
MyList<T>::MyList(const MyList& other) {
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
size_t MyList<T>::size() {
    size_t cnt = 0;
    for (cur = head; cur != nullptr; cur = cur->next) cnt++;
    return cnt;
}

template <typename T>
void MyList<T>::push_back(const T& item) {
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
void MyList<T>::pop_back() {
    for (cur = head; cur->next != nullptr; cur = cur->next)
        ;
    for (pre = head; pre->next != cur; pre = pre->next)
        ;
    if (cur == head) {
        delete cur;
        head = cur = pre = nullptr;
        return;
    }
    if (cur == nullptr) throw std::underflow_error("underflow");
    delete cur;
    pre->next = nullptr;
    cur = pre;
    for (pre = head; pre->next != cur && pre->next != nullptr; pre = pre->next)
        ;
}

template <typename T>
T& MyList<T>::back() {
    for (cur = head; cur->next != nullptr; cur = cur->next)
        ;
    if (cur == nullptr) throw std::underflow_error("underflow");
    return cur->entry;
}

template <typename T>
void MyList<T>::clear() {
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
typename MyList<T>::iterator MyList<T>::erase(iterator pos) {
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
void MyList<T>::reverse() {
    MyList<T> temp(*this);
    clear();
    while (!temp.empty()) {
        push_back(temp.back());
        temp.pop_back();
    }
    temp.~MyList();
}

template <typename T>
MyList<T>& MyList<T>::operator=(const MyList<T>& other) {
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
T& MyList<T>::front() {
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

#include <iostream>
struct Term {
    int64_t value;
    int64_t power;
};
class Pol : public MyList<Term> {
public:
    friend Pol operator+(Pol& lhs, Pol& rhs);
    friend Pol operator-(Pol& lhs, Pol& rhs);
    friend Pol operator*(Pol& lhs, Pol& rhs);
    void print();
};

Pol operator+(Pol& lhs, Pol& rhs) {
    Pol ans;
    while (!(lhs.empty() && rhs.empty())) {
        if (lhs.empty()) {
            ans.push_back(rhs.front());
            rhs.pop_front();
        } else if (rhs.empty()) {
            ans.push_back(lhs.front());
            lhs.pop_front();
        } else if (lhs.front().power > rhs.front().power) {
            ans.push_back(lhs.front());
            lhs.pop_front();
        } else if (lhs.front().power < rhs.front().power) {
            ans.push_back(rhs.front());
            rhs.pop_front();
        } else {
            ans.push_back({lhs.front().value + rhs.front().value, lhs.front().power});
            lhs.pop_front();
            rhs.pop_front();
        }
    }
    return ans;
}

Pol operator-(Pol& lhs, Pol& rhs) {
    Pol ans;
    while (!(lhs.empty() && rhs.empty())) {
        if (lhs.empty()) {
            ans.push_back({-rhs.front().value, rhs.front().power});
            rhs.pop_front();
        } else if (rhs.empty()) {
            ans.push_back(lhs.front());
            lhs.pop_front();
        } else if (lhs.front().power > rhs.front().power) {
            ans.push_back(lhs.front());
            lhs.pop_front();
        } else if (lhs.front().power < rhs.front().power) {
            ans.push_back({-rhs.front().value, rhs.front().power});
            rhs.pop_front();
        } else {
            ans.push_back({lhs.front().value - rhs.front().value, lhs.front().power});
            lhs.pop_front();
            rhs.pop_front();
        }
    }
    return ans;
}

Pol operator*(Pol& lhs, Pol& rhs) {
    Pol ans;
    Pol temp = lhs;
    while (!rhs.empty()) {
        for (auto& i : temp) {
            i.power += rhs.front().power;
            i.value *= rhs.front().value;
        }
        ans = ans + temp;
        rhs.pop_front();
        temp = lhs;
    }
    return ans;
}

void Pol::print() {
    while (!empty() && begin()->value == 0) {
        pop_front();
    }
    if (empty()) {
        std::cout << 0 << std::endl;
        return;
    }
    if (begin()->value != 0) {
        if (begin()->value == -1) {
            std::cout << '-';
        } else if (begin()->value != 1) {
            std::cout << begin()->value;
        }
        if (begin()->power != 0) {
            std::cout << 'X';
            if (begin()->power != 1) {
                std::cout << '^' << begin()->power;
            }
        }
        if (std::abs(begin()->value) == 1 && begin()->power == 0) {
            std::cout << 1;
        }
    }
    for (auto it = ++begin(); it != end(); it++) {
        if (it->value != 0) {
            if (it->power > 1) {
                if (std::abs(it->value) == 1) {
                    std::cout << "+-"[it->value < 0] << "X^" << it->power;
                } else {
                    std::cout << "+-"[it->value < 0] << std::abs(it->value) << "X^" << it->power;
                }
            } else if (it->power == 1) {
                if (std::abs(it->value) == 1) {
                    std::cout << "+-"[it->value < 0] << 'X';
                } else {
                    std::cout << "+-"[it->value < 0] << std::abs(it->value) << 'X';
                }
            } else if (it->power == 0) {
                std::cout << "+-"[it->value < 0] << std::abs(it->value);
            }
        }
    }
    std::cout << std::endl;
}