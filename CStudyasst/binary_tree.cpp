#include <functional>
#include <stack>

namespace pdli {
template <typename T>
class binary_tree {
    struct binary_tree_node {
        binary_tree_node(const T& entry)
            : entry(entry), left(nullptr), right(nullptr) {}
        binary_tree_node(const T& entry, binary_tree_node* left, binary_tree_node* right)
            : entry(entry), left(left), right(right) {}
        T entry;
        binary_tree_node* left;
        binary_tree_node* right;
    };

public:
    typedef binary_tree_node node;
    binary_tree() : root(nullptr), count(0) {}
    ~binary_tree() noexcept;
    binary_tree(const binary_tree& other);
    binary_tree& operator=(const binary_tree& other);
    void clear();
    void insert(const T& data);
    void inorder(const std::function<void(T&)> fun);
    void preorder(const std::function<void(T&)> fun);
    void postorder(const std::function<void(T&)> fun);
    std::size_t size() const;
    std::size_t height() const;

protected:
    node* root;
    std::size_t count;
    void __const_inorder(const std::function<void(T&)> fun) const;
    void __inorder(node*& sub_root, const std::function<void(T&)> fun);
    void __preorder(node*& sub_root, const std::function<void(T&)> fun);
    void __postorder(node*& sub_root, const std::function<void(T&)> fun);
    std::size_t __height(node* sub_root) const;
};

template <typename T>
void binary_tree<T>::clear() {
    std::function<void(node*&)> del = [&](node*& sub_root) {
        if (sub_root == nullptr) return;
        del(sub_root->left);
        del(sub_root->right);
        delete sub_root;
    };
    del(root);
    count = 0;
    root = nullptr;
}

template <typename T>
binary_tree<T>::~binary_tree() noexcept {
    clear();
}

template <typename T>
binary_tree<T>::binary_tree(const binary_tree& other) {
    root = nullptr;
    count = 0;
    auto ins = [&](const T& item) {
        insert(item);
    };
    other.__const_inorder(ins);
}

template <typename T>
void binary_tree<T>::insert(const T& data) {
    if (root == nullptr) {
        root = new node(data);
        ++count;
        return;
    }
    std::stack<bool> nums;
    std::size_t cnt = size();
    while (cnt) {
        nums.push(cnt-- & 1);
        cnt >>= 1;
    }
    node* cur = root;
    while (nums.size() > 1) {
        if (nums.top()) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
        nums.pop();
    }
    if (nums.top()) {
        cur->left = new node(data);
    } else {
        cur->right = new node(data);
    }
    ++count;
}

template <typename T>
std::size_t binary_tree<T>::size() const {
    return count;
}

template <typename T>
void binary_tree<T>::__inorder(node*& sub_root, const std::function<void(T&)> fun) {
    if (sub_root == nullptr) return;
    __inorder(sub_root->left, fun);
    fun(sub_root->entry);
    __inorder(sub_root->right, fun);
}

template <typename T>
void binary_tree<T>::__preorder(node*& sub_root, const std::function<void(T&)> fun) {
    if (sub_root == nullptr) return;
    fun(sub_root->entry);
    __preorder(sub_root->left, fun);
    __preorder(sub_root->right, fun);
}

template <typename T>
void binary_tree<T>::__postorder(node*& sub_root, const std::function<void(T&)> fun) {
    if (sub_root == nullptr) return;
    __postorder(sub_root->left, fun);
    __postorder(sub_root->right, fun);
    fun(sub_root->entry);
}

template <typename T>
void binary_tree<T>::inorder(const std::function<void(T&)> fun) {
    __inorder(root, fun);
}

template <typename T>
void binary_tree<T>::__const_inorder(const std::function<void(T&)> fun) const {
    std::function<void(node*)> inorder = [&](node* sub_root) {
        if (sub_root == nullptr) return;
        inorder(sub_root->left);
        fun(sub_root->entry);
        inorder(sub_root->right);
    };
    inorder(root);
}

template <typename T>
void binary_tree<T>::preorder(const std::function<void(T&)> fun) {
    __preorder(root, fun);
}

template <typename T>
void binary_tree<T>::postorder(const std::function<void(T&)> fun) {
    __postorder(root, fun);
}

template <typename T>
binary_tree<T>& binary_tree<T>::operator=(const binary_tree<T>& other) {
    if (this == &other) return *this;
    clear();
    auto ins = [&](const T& item) {
        insert(item);
    };
    other.__const_inorder(ins);
    return *this;
}

template <typename T>
std::size_t binary_tree<T>::__height(node* sub_root) const {
    if (sub_root == nullptr) return 0;
    return std::max(__height(sub_root->left), __height(sub_root->right)) + 1;
}

template <typename T>
std::size_t binary_tree<T>::height() const {
    return __height(root);
}
} // namespace pdli
