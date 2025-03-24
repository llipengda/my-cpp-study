#pragma once

#ifndef READ_H
#define READ_H

#include <iostream>
#include <vector>

template <class T>
auto read(T&& t) {
    std::cin >> t;
}

template <class T>
auto read(std::vector<T>& v) {
    T tmp;
    while (std::cin >> tmp) {
        v.push_back(tmp);
    }
}

template <class T = int>
auto read_v() {
    int n;
    std::cin >> n;
    std::vector<T> v(n);
    for (int i = 0; i < n; i++) {
        std::cin >> v[i];
    }
    return std::move(v);
}

template <class T = int>
auto read_v2() {
    int m, n;
    std::cin >> m >> n;
    std::vector<std::vector<T>> v(m, std::vector<T>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> v[i][j];
        }
    }
    return std::move(v);
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
    ((read(args)), ...);
}

#endif