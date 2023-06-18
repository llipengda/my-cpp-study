#include <bits/stdc++.h>
#define endl '\n'
#define IO ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
using namespace std;
using ll = long long;
namespace pdli {
template <typename T>
class list {
    struct list_node {
        T entry;
        list_node* next = nullptr;
        list_node() {}
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
            list_iterator* tmp = this;
            _M_node = _M_node->next;
            return *tmp;
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
    void replace(const T& old_item, const T& new_item);
    iterator begin() const;
    iterator end() const;
    iterator find(const T& item) const;
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
typename list<T>::iterator list<T>::find(const T& item) const {
    for (auto it = begin(); it != end(); ++it) {
        if (*it == item) return it;
    }
    return end();
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
void list<T>::replace(const T& old_item, const T& new_item) {
    for (auto& i : *this) {
        if (i == old_item) {
            i = new_item;
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
    node* cur = new node;
    node* new_head = cur;
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
    list = new_head->next;
    delete new_head;
}

template <typename T, typename U>
class hash_map {
    struct hash_map_record {
        T key;
        U value = U();
        hash_map_record(const T& key) : key(key){};
        hash_map_record(const T& key, const U& value) : key(key), value(value){};
        bool operator==(const hash_map_record& other) const {
            return key == other.key;
        }
    };
    struct hash_map_iterator {
        list<hash_map_record>* _M_node;
        typename list<hash_map_record>::iterator _M_list_iterator;
        hash_map_iterator() = default;
        hash_map_iterator(list<hash_map_record>* node, const typename list<hash_map_record>::iterator& it) : _M_node(node), _M_list_iterator(it){};
        hash_map_iterator operator++(int) {
            hash_map_iterator tmp = *this;
            do {
                if (_M_list_iterator != _M_node->end()) {
                    ++_M_list_iterator;
                } else {
                    ++_M_node;
                    _M_list_iterator = _M_node->begin();
                }
            } while (_M_list_iterator == nullptr);
            return tmp;
        }
        hash_map_iterator& operator++() {
            do {
                if (_M_list_iterator != _M_node->end()) {
                    ++_M_list_iterator;
                } else {
                    ++_M_node;
                    _M_list_iterator = _M_node->begin();
                }
            } while (_M_list_iterator == nullptr);
            return *this;
        }
        bool operator==(const hash_map_iterator& other) {
            return _M_node == other._M_node && _M_list_iterator == _M_list_iterator;
        }
        bool operator!=(const hash_map_iterator& other) {
            return !(*this == other);
        }
        hash_map_record& operator*() noexcept {
            return *_M_list_iterator;
        }
    };

public:
    typedef hash_map_record record;
    typedef hash_map_iterator iterator;
    static const size_t npos = static_cast<size_t>(-1);
    hash_map();
    hash_map(size_t n);
    hash_map(const hash_map& other);
    ~hash_map();
    hash_map& operator=(const hash_map& other);
    void insert(const T& key, const U& value);
    U& operator[](const T& key) const;
    size_t get_position(const T& key) const;
    U& get_value(const T& key) const;
    iterator get_iterator(const T& key) const;
    void remove(const T& key);
    static size_t _hash_fun(const T& key, const size_t& size);
    iterator begin() const;
    iterator end() const;

protected:
    size_t hash_size = 100;
    list<record>* table;
};

template <typename T, typename U>
hash_map<T, U>::hash_map() {
    table = new list<record>[hash_size + 1];
}

template <typename T, typename U>
hash_map<T, U>::~hash_map() {
    delete[] table;
}

template <typename T, typename U>
hash_map<T, U>::hash_map(size_t n) {
    hash_size = n;
    table = new list<record>[hash_size + 1];
}

template <typename T, typename U>
hash_map<T, U>::hash_map(const hash_map& other) {
    hash_size = other.hash_size;
    table = new list<record>[hash_size + 1];
    for (int i = 0; i < hash_size; ++i) {
        table[i] = other.table[i];
    }
}

template <typename T, typename U>
hash_map<T, U>& hash_map<T, U>::operator=(const hash_map<T, U>& other) {
    if (this == &other) return *this;
    delete[] table;
    hash_size = other.hash_size;
    table = new list<record>[hash_size + 1];
    for (int i = 0; i < hash_size; ++i) {
        table[i] = other.table[i];
    }
    return *this;
}

template <typename T, typename U>
void hash_map<T, U>::insert(const T& key, const U& value) {
    size_t pos = _hash_fun(key, hash_size);
    if (table[pos].find(key) == table[pos].end()) {
        table[pos].push_front({key, value});
    } else {
        table[pos].replace(key, {key, value});
    }
}

template <typename T, typename U>
size_t hash_map<T, U>::get_position(const T& key) const {
    size_t pos = _hash_fun(key, hash_size);
    if (table[pos].find(key) == table[pos].end()) {
        return npos;
    }
    return pos;
}

template <typename T, typename U>
U& hash_map<T, U>::get_value(const T& key) const {
    size_t pos = _hash_fun(key, hash_size);
    if (table[pos].find(key) != table[pos].end()) {
        return table[pos].find(key)->value;
    } else {
        throw std::runtime_error("Value of the key does not exist");
    }
}

template <typename T, typename U>
typename hash_map<T, U>::iterator hash_map<T, U>::get_iterator(const T& key) const {
    size_t pos = _hash_fun(key, hash_size);
    if (table[pos].find(key) != table[pos].end()) {
        return iterator(table + pos, table[pos].find(key));
    } else {
        return iterator(table + pos, table[pos].begin());
    }
}

template <typename T, typename U>
void hash_map<T, U>::remove(const T& key) {
    size_t pos = _hash_fun(key, hash_size);
    table[pos].remove(key);
}

template <typename T, typename U>
U& hash_map<T, U>::operator[](const T& key) const {
    size_t pos = _hash_fun(key, hash_size);
    if (table[pos].find(key) != table[pos].end()) {
        return table[pos].find(key)->value;
    } else {
        table[pos].push_front(key);
        return table[pos].begin()->value;
    }
}

template <typename T, typename U>
typename hash_map<T, U>::iterator hash_map<T, U>::begin() const {
    return iterator(table, table->begin());
}

template <typename T, typename U>
typename hash_map<T, U>::iterator hash_map<T, U>::end() const {
    return iterator(table + hash_size + 1, (table + hash_size + 1)->end());
}

template <typename T, typename U>
size_t hash_map<T, U>::_hash_fun(const T& key, const size_t& size) {
    unsigned seed = 31;
    unsigned hash = 0;
    T tmp = key;
    if (is_same<T, std::string>::value) {
        for (const auto& i : key) {
            hash = (hash * seed + i) % size;
        }
        return hash % size;
    }
    return hash % size;
}

template <typename T>
class AVL_tree {
    enum class balance_factor {
        left_higher,
        right_higher,
        equal_height
    };
    struct AVL_tree_node {
        T data;
        balance_factor balance = balance_factor::equal_height;
        AVL_tree_node* left = nullptr;
        AVL_tree_node* right = nullptr;
        AVL_tree_node() = default;
        AVL_tree_node(const T& item) : data(item) {}
    };

public:
    using node = AVL_tree_node;

    AVL_tree() = default;

    AVL_tree(const AVL_tree& other) {
        clear();
        std::function<void(node*)> m_insert = [&](node* sub_root) {
            if (sub_root == nullptr) return;
            insert(sub_root->data);
            m_insert(sub_root->left);
            m_insert(sub_root->right);
        };
        m_insert(other.root);
    }

    AVL_tree(AVL_tree&& other) {
        clear();
        root = std::move(other.root);
        other.root = nullptr;
    }

    ~AVL_tree() {
        clear();
    }

    AVL_tree& operator=(const AVL_tree& other) {
        if (this == &other) return *this;
        clear();
        std::function<void(node*)> m_insert = [&](node* sub_root) {
            if (sub_root == nullptr) return;
            insert(sub_root->data);
            m_insert(sub_root->left);
            m_insert(sub_root->right);
        };
        m_insert(other.root);
        return *this;
    }

    AVL_tree& operator=(AVL_tree&& other) {
        if (this == &other) return *this;
        clear();
        root = std::move(other.root);
        other.root = nullptr;
        return *this;
    }

    /**
		* @brief Insert an item at the AVL_tree. If the item is already in the tree, throw a duplicate_errer.
		* @param item the item to insert
		*/
    void insert(const T& item) {
        AVL_insert(root, item);
    }

    /**
		* @brief Clear the tree.
		*/
    void clear() {
        m_clear(root);
        root = nullptr;
    }

    /**
		 * @brief Remove an item in the tree
		 * @param item the item to remove
		 */
    void remove(const T& item) {
        AVL_remove(root, item);
    }

    /**
		 * @brief Find an item in the tree.
		 * @param item the item to find
		 * @return reference of the item found in the tree
		 */
    T& find(const T& item) {
        node* cur = root;
        while (cur != nullptr && cur->data != item) {
            std::cout << cur->data.key << ' ';
            if (item < cur->data) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
        if (cur == nullptr) {
            throw std::runtime_error("not present");
        } else {
            return cur->data;
        }
    }

    void in_order(const std::function<void(T&)>& fun) {
        std::function<void(node*, std::function<void(T&)>)> _inorder = [&](node* root, std::function<void(T&)> fun) {
            if (root == nullptr) return;
            _inorder(root->left, fun);
            fun(root->data);
            _inorder(root->right, fun);
        };
        _inorder(root, fun);
    }

    void pre_order(const std::function<void(T&)>& fun) {
        std::function<void(node*, std::function<void(T&)>)> _preorder = [&](node* root, std::function<void(T&)> fun) {
            if (root == nullptr) return;
            fun(root->data);
            _preorder(root->left, fun);
            _preorder(root->right, fun);
        };
        _preorder(root, fun);
    }

    void post_order(const std::function<void(T&)>& fun) {
        std::function<void(node*, std::function<void(T&)>)> _postorder = [&](node* root, std::function<void(T&)> fun) {
            if (root == nullptr) return;
            _postorder(root->left, fun);
            _postorder(root->right, fun);
            fun(root->data);
        };
        _postorder(root, fun);
    }

protected:
    node* root = nullptr;

private:
    /**
		 * @brief Insert an item in the subtree. If the item is already in the subtree, throw a duplicate_errer.
		 * @param subroot where to insert
		 * @param item the item to insert
		 * @return the subtree is increased in height or not
		*/
    bool AVL_insert(node*& sub_root, const T& item) {
        if (sub_root == nullptr) {
            sub_root = new node(item);
            return true;
        } else if (item == sub_root->data) {
            throw std::runtime_error("duplicate error");
        } else if (item < sub_root->data) {
            bool taller = AVL_insert(sub_root->left, item);
            if (taller) {
                switch (sub_root->balance) {
                case balance_factor::left_higher:
                    left_balance(sub_root);
                    taller = false;
                    break;
                case balance_factor::right_higher:
                    sub_root->balance = balance_factor::equal_height;
                    taller = false;
                    break;
                case balance_factor::equal_height:
                    sub_root->balance = balance_factor::left_higher;
                    break;
                }
            }
            return taller;
        } else {
            bool is_taller = AVL_insert(sub_root->right, item);
            if (is_taller) {
                switch (sub_root->balance) {
                case balance_factor::left_higher:
                    sub_root->balance = balance_factor::equal_height;
                    is_taller = false;
                    break;
                case balance_factor::right_higher:
                    right_balance(sub_root);
                    is_taller = false;
                    break;
                case balance_factor::equal_height:
                    sub_root->balance = balance_factor::right_higher;
                    break;
                }
            }
            return is_taller;
        }
    }

    /**
		 * @brief Make a left subtree balanced
		 * @param sub_root root of the left subtree
		 */
    void left_balance(node*& sub_root) {
        node*& left_tree = sub_root->left;
        switch (left_tree->balance) {
        case balance_factor::left_higher: // case L-L
            sub_root->balance = balance_factor::equal_height;
            left_tree->balance = balance_factor::equal_height;
            rotate_right(sub_root);
            break;
        case balance_factor::equal_height:
            throw std::runtime_error("impossible case in left_balance");
            break;
        case balance_factor::right_higher: // case L-R
            node* sub_tree = left_tree->right;
            switch (sub_tree->balance) {
            case balance_factor::equal_height:
                sub_root->balance = balance_factor::equal_height;
                left_tree->balance = balance_factor::equal_height;
                break;
            case balance_factor::left_higher:
                sub_root->balance = balance_factor::right_higher;
                left_tree->balance = balance_factor::equal_height;
                break;
            case balance_factor::right_higher:
                sub_root->balance = balance_factor::equal_height;
                left_tree->balance = balance_factor::left_higher;
                break;
            }
            sub_tree->balance = balance_factor::equal_height;
            rotate_left(left_tree);
            rotate_right(sub_root);
            break;
        }
    }

    /**
		 * @brief Make a right subtree balanced
		 * @param sub_root root of the right subtree
		 */
    void right_balance(node*& sub_root) {
        node*& right_tree = sub_root->right;
        switch (right_tree->balance) {
        case balance_factor::right_higher: // case R-R
            sub_root->balance = balance_factor::equal_height;
            right_tree->balance = balance_factor::equal_height;
            rotate_left(sub_root);
            break;
        case balance_factor::equal_height:
            throw std::runtime_error("impossible case in right_balance");
            break;
        case balance_factor::left_higher: // case R-L
            node* sub_tree = right_tree->left;
            switch (sub_tree->balance) {
            case balance_factor::equal_height:
                sub_root->balance = balance_factor::equal_height;
                right_tree->balance = balance_factor::equal_height;
                break;
            case balance_factor::left_higher:
                sub_root->balance = balance_factor::equal_height;
                right_tree->balance = balance_factor::right_higher;
                break;
            case balance_factor::right_higher:
                sub_root->balance = balance_factor::left_higher;
                right_tree->balance = balance_factor::equal_height;
                break;
            }
            sub_tree->balance = balance_factor::equal_height;
            rotate_right(right_tree);
            rotate_left(sub_root);
            break;
        }
    }

    /**
		 * @brief Do a left rotation at the sub_tree
		 * @param sub_root the root of the sub_tree
		*/
    void rotate_left(node*& sub_root) {
        if (sub_root == nullptr || sub_root->right == nullptr) {
            throw std::runtime_error("impossible case in rotate_left");
        }
        node* right_tree = sub_root->right;
        sub_root->right = right_tree->left;
        right_tree->left = sub_root;
        sub_root = right_tree;
    }

    /**
		 * @brief Do a right rotation at the sub_tree
		 * @param sub_root the root of the sub_tree
		*/
    void rotate_right(node*& sub_root) {
        if (sub_root == nullptr || sub_root->left == nullptr) {
            throw std::runtime_error("impossible case in rotate_right");
        }
        node* left_tree = sub_root->left;
        sub_root->left = left_tree->right;
        left_tree->right = sub_root;
        sub_root = left_tree;
    }

    /**
		 * @brief Clear a subtree.
		 * @param sub_root the root of the subtree
		 */
    void m_clear(node* sub_root) {
        if (sub_root == nullptr) return;
        m_clear(sub_root->left);
        m_clear(sub_root->right);
        delete sub_root;
    }

    /**
		 * @brief Remove an item in a subtree.
		 * @param sub_root the root of the subtree
		 * @param item the item to remove
		 * @return the sub_tree becomes shorter or not
		 */
    bool AVL_remove(node*& sub_root, const T& item) {
        if (sub_root == nullptr) {
            throw std::runtime_error("not found in AVL_remove");
        } else if (item < sub_root->data) {
            return remove_left(sub_root, item);
        } else if (item > sub_root->data) {
            return remove_right(sub_root, item);
        } else if (sub_root->right == nullptr) {
            node* temp = sub_root;
            sub_root = sub_root->left;
            delete temp;
            return true;
        } else if (sub_root->left == nullptr) {
            node* temp = sub_root;
            sub_root = sub_root->right;
            delete temp;
            return true;
        } else if (sub_root->balance == balance_factor::right_higher) {
            // another solution
            // node* temp = sub_root->right;
            // while (temp->left != nullptr) {
            //     temp = temp->left;
            // }
            // return remove_right(sub_root, temp->data);
            node* temp = sub_root->left;
            while (temp->right != nullptr) {
                temp = temp->right;
            }
            sub_root->data = temp->data;
            return remove_left(sub_root, temp->data);
        } else {
            node* temp = sub_root->left;
            while (temp->right != nullptr) {
                temp = temp->right;
            }
            sub_root->data = temp->data;
            return remove_left(sub_root, temp->data);
        }
    }

    /**
		 * @brief Remove an item from a left subtree.
		 * @param sub_root the root of the left subtree
		 * @param item the item to remove
		 * @return the subtree becomes shorter or not
		 */
    bool remove_left(node*& sub_root, const T& item) {
        bool shorter = AVL_remove(sub_root->left, item);
        if (shorter) {
            switch (sub_root->balance) {
            case balance_factor::left_higher:
                sub_root->balance = balance_factor::equal_height;
                break;
            case balance_factor::equal_height:
                sub_root->balance = balance_factor::right_higher;
                shorter = false;
                break;
            case balance_factor::right_higher:
                node* temp = sub_root->right;
                switch (temp->balance) {
                case balance_factor::equal_height:
                    temp->balance = balance_factor::left_higher;
                    rotate_left(sub_root);
                    shorter = false;
                    break;
                case balance_factor::right_higher:
                    sub_root->balance = balance_factor::equal_height;
                    temp->balance = balance_factor::equal_height;
                    rotate_left(sub_root);
                    break;
                case balance_factor::left_higher:
                    node* temp_left = temp->left;
                    switch (temp_left->balance) {
                    case balance_factor::equal_height:
                        sub_root->balance = balance_factor::equal_height;
                        temp->balance = balance_factor::equal_height;
                        break;
                    case balance_factor::right_higher:
                        sub_root->balance = balance_factor::left_higher;
                        temp->balance = balance_factor::equal_height;
                        break;
                    case balance_factor::left_higher:
                        sub_root->balance = balance_factor::equal_height;
                        temp->balance = balance_factor::right_higher;
                        break;
                    }
                    temp_left->balance = balance_factor::equal_height;
                    rotate_right(sub_root->right);
                    rotate_left(sub_root);
                    break;
                }
            }
        }
        return shorter;
    }

    /**
		 * @brief Remove an item from a right subtree.
		 * @param sub_root the root of the right subtree
		 * @param item the item to remove
		 * @return the subtree becomes shorter or not
		 */
    bool remove_right(node*& sub_root, const T& item) {
        bool shorter = AVL_remove(sub_root->right, item);
        if (shorter) {
            switch (sub_root->balance) {
            case balance_factor::right_higher:
                sub_root->balance = balance_factor::equal_height;
                break;
            case balance_factor::equal_height:
                sub_root->balance = balance_factor::left_higher;
                shorter = false;
                break;
            case balance_factor::left_higher:
                node* temp = sub_root->left;
                switch (temp->balance) {
                case balance_factor::equal_height:
                    temp->balance = balance_factor::right_higher;
                    rotate_right(sub_root);
                    shorter = false;
                    break;
                case balance_factor::left_higher:
                    sub_root->balance = balance_factor::equal_height;
                    temp->balance = balance_factor::equal_height;
                    rotate_right(sub_root);
                    break;
                case balance_factor::right_higher:
                    node* temp_right = temp->right;
                    switch (temp_right->balance) {
                    case balance_factor::equal_height:
                        sub_root->balance = balance_factor::equal_height;
                        temp->balance = balance_factor::equal_height;
                        break;
                    case balance_factor::left_higher:
                        sub_root->balance = balance_factor::right_higher;
                        temp->balance = balance_factor::equal_height;
                        break;
                    case balance_factor::right_higher:
                        sub_root->balance = balance_factor::equal_height;
                        temp->balance = balance_factor::left_higher;
                        break;
                    }
                    temp_right->balance = balance_factor::equal_height;
                    rotate_left(sub_root->left);
                    rotate_right(sub_root);
                    break;
                }
            }
        }
        return shorter;
    }
};

} // namespace pdli

struct restaurant {
    string name = "";
    int x = 0;
    int y = 0;
    double dis = 0;
    restaurant() {}
    restaurant(string name, int x, int y) : name(name), x(x), y(y) {}
    bool operator<(const restaurant& other) const {
        return tie(dis, name) < tie(other.dis, other.name);
    }
    bool operator==(const restaurant& other) const {
        return tie(name, x, y, dis) == tie(other.name, other.x, other.y, other.dis);
    }
};

int main() {
    IO;
    auto clk = clock();
    int m, n;
    cin >> m >> n;
    pdli::hash_map<string, pdli::list<restaurant>> unsorted_map;
    pdli::hash_map<string, pdli::AVL_tree<restaurant>> sorted_map;
    while (m--) {
        string name, type;
        int x, y;
        cin >> name >> x >> y >> type;
        auto t = restaurant{name, x, y};
        unsorted_map[type].push_front(t);
    }
    while (n--) {
        int x, y, k;
        string type;
        cin >> x >> y >> type >> k;
        for_each(unsorted_map[type].begin(), unsorted_map[type].end(), [&](restaurant& a) {
            a.dis = sqrt((ll)(x - a.x) * (x - a.x) + (ll)(y - a.y) * (y - a.y));
            sorted_map[type].insert(a);
        });
        int cnt = k;
        sorted_map[type].in_order([&](const restaurant& a) {
            if (--cnt < 0) {
                return;
            }
            cout << a.name << ' ' << fixed << setprecision(3) << a.dis << endl;
        });
    }
#ifndef ONLINE_JUDGE
    cerr << "time : " << clock() - clk << "ms" << endl;
#endif
}