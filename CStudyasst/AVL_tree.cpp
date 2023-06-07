#include <functional>
#include <iostream>
#include <stdexcept>

namespace pdli {
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
     * @return the item found in the tree
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
        } else if (sub_root->balance == balance_factor::left_higher) {
            node* temp = sub_root->left;
            while (temp->right != nullptr) {
                temp = temp->right;
            }
            sub_root->data = temp->data;
            return remove_left(sub_root, temp->data);
        } else {
            node* temp = sub_root->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            sub_root->data = temp->data;
            return remove_right(sub_root, temp->data);
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

template <typename T, typename U>
struct record {
    T key;
    U value;
    record(const T& key) : key(key) {}
    record(const T& key, const U& value) : key(key), value(value) {}
    bool operator==(const record& other) const {
        return key == other.key;
    }
    bool operator!=(const record& other) const {
        return key != other.key;
    }
    bool operator<(const record& other) const {
        return key < other.key;
    }
    bool operator>(const record& other) const {
        return key > other.key;
    }
};

int main() {
    pdli::AVL_tree<record<std::string, std::string>> avlt;
    int n;
    std::cin >> n;
    while (n--) {
        std::string key, value;
        std::cin >> key >> value;
        avlt.insert({key, value});
    }
    std::cin >> n;
    while (n--) {
        std::string key;
        std::cin >> key;
        avlt.remove(key);
    }
    for (int i = 0; i < 2; i++) {
        std::string key;
        std::cin >> key;
        try {
            auto ans = avlt.find(key);
            std::cout << ans.key << ' ' << ans.value << std::endl;
        } catch (...) {
            std::cout << "NULL" << std::endl;
        }
    }
    return 0;
}