#include <bits/stdc++.h>
#define endl '\n'
#define IO std::ios::sync_with_stdio(false), std::cin.tie(nullptr)
using ll = long long;
using pii = std::pair<int, int>;
using namespace std;

template <typename T>
struct A {
    using type = T;
};

template <typename T = int>
struct B : public A<T> {
    A<T>::type t;
    void f() {
        auto f = this->t;
    }
};

struct C : public B<int>, public A<double> {
    using A<double>::type;
    type f;
    void g() {
        auto g = this->t;
    }
};

int main() {
}