#include <functional>
#include <stdexcept>

namespace pdli {
template <typename T>
class BST {
    struct BST_node {
        T entry;
        BST_node* left;
        BST_node* right;
        BST_node() : left(nullptr), right(nullptr) {}
        BST_node(const T& value) : entry(value), left(nullptr), right(nullptr) {}
    };
    using node = BST_node;

protected:
    node* root;

public:
    BST() : root(nullptr) {}
    BST(const BST& other) {
        clear();
        std::function<void(node*)> r_insert = [&](node* subroot) {
            if (subroot == nullptr) return;
            insert(subroot->entry);
            r_insert(subroot->left);
            r_insert(subroot->right);
        };
        r_insert(other.root);
    }
    BST& operator=(const BST& other) {
        if (this == &other) return *this;
        clear();
        std::function<void(node*)> r_insert = [&](node* subroot) {
            if (subroot == nullptr) return;
            insert(subroot->entry);
            r_insert(subroot->left);
            r_insert(subroot->right);
        };
        r_insert(other.root);
    }
    ~BST() {
        clear();
    }
    void clear() {
        std::function<void(node*)> r_clear = [&](node* subroot) {
            if (subroot == nullptr) return;
            r_clear(subroot->left);
            r_clear(subroot->right);
            delete subroot;
        };
        r_clear(root);
    }
    void insert(const T& item) {
        if (root == nullptr) {
            root = new node(item);
            return;
        }
        node* cur = root;
        node* pre = root;
        while (cur != nullptr) {
            if (item < cur->entry) {
                pre = cur;
                cur = cur->left;
            } else {
                pre = cur;
                cur = cur->right;
            }
        }
        if (item < pre->entry) {
            pre->left = new node(item);
        } else {
            pre->right = new node(item);
        }
    }
    void remove(const T& item) {
        node* cur = root;
        node* pre = root;
        while (cur != nullptr && cur->entry != item) {
            pre = cur;
            if (item < cur->entry) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
        if (cur == nullptr) return;
        if (cur->right == nullptr) {
            if (pre == cur) {
                root = cur->left;
            }
            if (pre->left == cur) {
                pre->left = cur->left;
            } else {
                pre->right = cur->left;
            }
            delete cur;
        } else if (cur->left == nullptr) {
            if (pre == cur) {
                root = cur->right;
            }
            if (pre->left == cur) {
                pre->left = cur->right;
            } else {
                pre->right = cur->right;
            }
            delete cur;
        } else {
            node* to_del = cur->left;
            node* parent = cur;
            while (to_del->right != nullptr) {
                parent = to_del;
                to_del = to_del->right;
            }
            cur->entry = to_del->entry;
            if (parent == cur) {
                cur->left = to_del->left;
            } else {
                parent->right = to_del->left;
            }
            delete to_del;
        }
    }
    T& find(const T& item) {
        node* cur = root;
        while (cur != nullptr && cur->entry != item) {
            if (item < cur->entry) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
        if (cur == nullptr) {
            throw std::runtime_error("NOT FOUND");
        } else {
            return cur->entry;
        }
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
};
