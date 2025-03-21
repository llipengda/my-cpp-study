#pragma once
#include <vector>
#ifndef OUT_HPP
#define OUT_HPP

#include <iostream>

template <class T>
auto out(T p) {
    std::cout << p;
}

template <class T>
auto out(std::vector<T> v) {
    auto n = v.size();
    std::cout << '[';
    for (int i = 0; i < n; i++) {
        std::cout << v[i] << ",]"[i == n - 1];
    }
}

template <class ...Args>
void out(Args&&... args) {
    ((out(args), std::cout << '\n'), ...);
}

#endif