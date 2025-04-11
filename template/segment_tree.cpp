#include <functional>
#include <memory>
#include <vector>

template <class T>
struct segment_tree {
    int n;
    std::vector<T> tree;
    std::unique_ptr<std::vector<T>> value;
    std::function<T(T, T)> fun;
    T identity_element;

    segment_tree(int n_, std::vector<T>&& value_, std::function<T(T, T)> fun_, T identity = T{})
        : n(n_), tree(4 * n), value(std::make_unique<std::vector<T>>(std::move(value_))), fun(fun_), identity_element(identity) {}

    void build(int l, int r, int p) {
        if (l == r) {
            tree[p] = (*value)[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, p * 2);
        build(mid + 1, r, p * 2 + 1);
        tree[p] = fun(tree[p * 2], tree[p * 2 + 1]);
    }

    T query(int il, int ir, int l, int r, int p) {
        if (il <= l && r <= ir) {
            return tree[p];
        }
        int m = (l + r) >> 1;
        T left = identity_element, right = identity_element;
        if (il <= m) {
            left = query(il, ir, l, m, p * 2);
        }
        if (ir > m) {
            right = query(il, ir, m + 1, r, p * 2 + 1);
        }
        return fun(left, right);
    }
};
