#pragma once
#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <cstddef>
#include <iostream>
#include <sstream>
#define debug(...) debug_(__VA_ARGS__, #__VA_ARGS__)
#define debug_out(...) debug_(__VA_ARGS__, #__VA_ARGS__, std::cout)
#define MAX_LEN 20

template <typename T>
struct has_size {
private:
    template <typename U>
    static auto test(int) -> decltype(std::declval<U>().size(), std::true_type());

    template <typename>
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test<T>(0))::value;
};

template <typename T>
struct has_subscript {
private:
    template <typename U>
    static auto test(int) -> decltype(std::declval<U>()[0], std::true_type());

    template <typename>
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test<T>(0))::value;
};

template <typename T>
struct is_ostreamable {
private:
    template <typename U>
    static auto test(int) -> decltype(std::declval<std::ostream&>() << std::declval<U>(), std::true_type());

    template <typename>
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test<T>(0))::value;
};

template <typename T>
struct has_iterator {
private:
    template <typename U>
    static auto test(int) -> decltype(std::begin(std::declval<U>()), std::end(std::declval<U>()), std::true_type());

    template <typename>
    static constexpr std::false_type test(...);

public:
    static constexpr bool value = decltype(test<T>(0))::value;
};

template <typename T, typename std::enable_if<is_ostreamable<T>::value, int>::type = 0>
auto str(T&& x);

template <typename T>
auto str(T&& x, std::size_t len, std::size_t max_len);

template <typename T, std::size_t ML = MAX_LEN, typename std::enable_if<has_size<T>::value && has_subscript<T>::value && !is_ostreamable<T>::value, int>::type = 0>
auto str(T&& x);

template <typename T, std::size_t ML = MAX_LEN, typename std::enable_if<has_iterator<T>::value && !(has_size<T>::value && has_subscript<T>::value) && !is_ostreamable<T>::value, int>::type = 0>
auto str(T&& x);

template <typename T, typename std::enable_if<is_ostreamable<T>::value, int>::type>
auto str(T&& x) {
    return x;
}

template <typename T>
auto str(T&& x, std::size_t len, std::size_t max_len) {
    std::ostringstream oss;
    oss << '[';
    if (len <= max_len) {
        std::string end[]{", ", "]"};
        for (std::size_t i = 0; i < len; i++) {
            oss << str(x[i]) << end[i == len - 1];
        }
    } else {
        std::string end[]{", ", ", ..., "};
        for (std::size_t i = 0; i < max_len - 2; i++) {
            oss << str(x[i]) << end[i == max_len - 2 - 1];
        }
        std::string end2[]{", ", "]"};
        for (std::size_t i = len - 2; i < len; i++) {
            oss << str(x[i]) << end2[i == len - 1];
        }
    }
    if (len == 0) {
        oss << ']';
    }
    return oss.str();
}

template <typename T, std::size_t ML, typename std::enable_if<has_size<T>::value && has_subscript<T>::value && !is_ostreamable<T>::value, int>::type>
auto str(T&& x) {
    return str(x, x.size(), ML);
}

template <typename T, std::size_t ML, typename std::enable_if<has_iterator<T>::value && !(has_size<T>::value && has_subscript<T>::value) && !is_ostreamable<T>::value, int>::type>
auto str(T&& x) {
    std::ostringstream oss;
    oss << '[';
    std::size_t len = 0;
    for (const auto& i : x) {
        oss << str(i) << ", ";
        if (++len >= ML) {
            oss << "..., ";
            break;
        }
    }
    auto s = oss.str();
    if (s.size() > 1) {
        s.pop_back();
        s.pop_back();
    }
    s += ']';
    return s;
}

template <typename T>
auto debug_(T&& x, const std::string& name, std::ostream& out = std::cerr) {
    out << name << " = " << str(x) << '\n';
    return x;
}

#endif // DEBUG_HPP