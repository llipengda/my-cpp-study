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
            T entry;
            AVL_tree_node* left = nullptr;
            AVL_tree_node* right = nullptr;
            balance_factor balance = balance_factor::equal_height;
            AVL_tree_node() = default;
            AVL_tree_node(const T& item): entry(item) {}
        };
    public:
        using node = AVL_tree_node;
        void insert(const T& item) {
            AVL_insert(root, item);
        }
    protected:
        node* root;
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
            } else if (item == sub_root->entry) {
                throw std::runtime_error("duplicate error");
            } else if (item < sub_root->entry) {
                bool is_taller = AVL_insert(sub_root->left, item);
                if (is_taller) {
                    switch (sub_root->balance) {
                    case balance_factor::left_higher:
                        left_balence(sub_root);
                        is_taller = false;
                        break;
                    case balance_factor::right_higher:
                        sub_root->balance = balance_factor::equal_height;
                        is_taller = false;
                        break;
                    case balance_factor::equal_height:
                        sub_root->balance = balance_factor::left_higher;
                        break;
                    default:
                        break;
                    }
                }
                return is_taller;
            } else {
                bool is_taller = AVL_insert(sub_root->left, item);
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
                    default:
                        break;
                    }
                }
                return is_taller;
            }
        }
        
        void left_balence(node*& sub_root) {

        }
        
        void right_balence(node*& sub_root) {

        }
        
        /**
         * @brief Do a left rotate at the sub_tree
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
         * @brief Do a right rotate at the sub_tree
         * @param sub_root the root of the sub_tree
        */
        void rotate_right(node*& sub_root) {
            
        }
    };
}