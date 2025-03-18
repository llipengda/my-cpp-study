#pragma once

#ifndef READ_H
#define READ_H

#include <iostream>
#include <vector>

template <class T = int>
auto read_v() {
    int n;
    std::cin >> n;
    std::vector<T> v(n);
    for (int i = 0; i < n; i++) {
        std::cin >> v[i];
    }
    return v;
}

template <class T = int>
auto read_v_unknown() {
    std::vector<T> v;
    T tmp;
    while (std::cin >> tmp) {
        v.push_back(tmp);
    }
    return v;
}

template <class... Args>
void read(Args&&... args) {
    ((std::cin >> args), ...);
}

#endif