#pragma once

#ifndef REGEX_TOKEN_HPP
#define REGEX_TOKEN_HPP

#include "exception.hpp"

#include <iostream>
#include <ostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

namespace regex::token {
enum class symbol {
    end_mark,
    number,
    word,
    white_space,
};

enum class op {
    concat,
    alt,
    star,
    plus,
    left_par,
    right_par,
    blackslash
};

const std::unordered_map<symbol, std::string> symbol_map = {
    {symbol::end_mark, "#"},
    {symbol::number, "\\d"},
    {symbol::word, "\\w"},
    {symbol::white_space, "\\s"}};

const std::unordered_map<op, std::string> op_map = {
    {op::concat, "·"},
    {op::alt, "|"},
    {op::star, "*"},
    {op::plus, "+"},
    {op::left_par, "("},
    {op::right_par, ")"},
    {op::blackslash, "\\"}};

enum class nothing {};

struct char_set {
    std::unordered_set<char> chars;
    bool is_negative = false;

    char_set() = default;
    explicit char_set(char from, char to, bool is_negative = false) : is_negative(is_negative) {
        for (char ch = from; ch <= to; ++ch) {
            chars.insert(ch);
        }
    }

    void add(char ch) {
        chars.insert(ch);
    }

    void add(const char_set& other) {
        chars.insert(other.chars.begin(), other.chars.end());
    }

    void add(char from, char to) {
        for (char ch = from; ch <= to; ++ch) {
            chars.insert(ch);
        }
    }

    bool operator==(const char_set& other) const {
        return chars == other.chars && is_negative == other.is_negative;
    }
};

using token_type = std::variant<nothing, symbol, op, char_set, char>;

struct token_type_hash {
    std::size_t operator()(const token_type& t) const {
        if (std::holds_alternative<char>(t)) {
            return std::hash<char>{}(std::get<char>(t));
        } else if (std::holds_alternative<symbol>(t)) {
            return std::hash<int>{}(static_cast<int>(std::get<symbol>(t)));
        } else if (std::holds_alternative<op>(t)) {
            return std::hash<int>{}(static_cast<int>(std::get<op>(t)));
        } else if (std::holds_alternative<char_set>(t)) {
            std::size_t hash = 0;
            const auto& set = std::get<char_set>(t);
            for (const auto& ch : set.chars) {
                hash ^= std::hash<char>{}(ch);
            }
            return hash;
        }
        return 0;
    }
};

static int get_precedence(op opr) {
    switch (opr) {
    case op::star: return 3;
    case op::plus: return 3;
    case op::concat: return 2;
    case op::alt: return 1;
    case op::left_par: return 0;
    case op::right_par: return 0;
    case op::blackslash: return -1;
    }
    return -1;
}

static int get_precedence(token_type ch) {
    op opr;
    if (std::holds_alternative<op>(ch)) {
        opr = std::get<op>(ch);
    } else {
        return -1;
    }

    return get_precedence(opr);
}

static bool is_char(token_type ch) {
    return std::holds_alternative<char>(ch);
}

static bool is_symbol(token_type ch) {
    return std::holds_alternative<symbol>(ch);
}

static bool is_op(token_type ch) {
    return std::holds_alternative<op>(ch);
}

template <typename T>
static bool is(token_type ch, T other) {
    if (auto* p = std::get_if<T>(&ch)) {
        return *p == other;
    }
    return false;
}

static bool match(char c, token_type ch) {
    if (is_char(ch)) {
        return std::get<char>(ch) == c;
    } else if (is_symbol(ch)) {
        symbol sym = std::get<symbol>(ch);
        switch (sym) {
        case symbol::end_mark:
            return false;
        case symbol::number:
            return std::isdigit(c);
        case symbol::word:
            return std::isalnum(c) || c == '_';
        case symbol::white_space:
            return std::isspace(c);
        }
    }
    return false;
}

static const std::vector<token_type> get_possible_token(const char c) {
    std::vector<token_type> result;
    if (std::isalnum(c) || c == '_') {
        result.push_back(symbol::word);
    }
    if (std::isdigit(c)) {
        result.push_back(symbol::number);
    }
    if (std::isspace(c)) {
        result.push_back(symbol::white_space);
    }
    result.push_back(c);
    return result;
}

static bool is_nonop(char ch) {
    return ch != '\\' && ch != '|' && ch != '*' && ch != '(' && ch != ')' && ch != '+';
}

static bool is_nonop(token_type ch) {
    return is_char(ch) || is_symbol(ch);
}

static std::vector<token_type> split(const std::string& s) {
    std::vector<token_type> result{op::left_par};
    token_type last = nothing{};
    for (const char& ch : s) {
        // add concat operator
        if (is_char(last) || is_symbol(last) || is(last, op::right_par) || is(last, op::star) || is(last, op::plus)) {
            if (is_nonop(ch) || ch == '(' || ch == '\\') {
                result.push_back(op::concat);
            }
        }

        if (is(last, op::blackslash)) {
            if (!is_nonop(ch)) {
                last = ch;
            } else if (ch == 'w') {
                last = symbol::word;
            } else if (ch == 'd') {
                last = symbol::number;
            } else if (ch == 's') {
                last = symbol::white_space;
            } else if (ch == '0') {
                last = '\0';
            } else if (ch == 'a') {
                last = '\a';
            } else if (ch == 'v') {
                last = '\v';
            } else if (ch == 'n') {
                last = '\n';
            } else if (ch == 't') {
                last = '\t';
            } else if (ch == 'r') {
                last = '\r';
            } else if (ch == 'f') {
                last = '\f';
            } else {
                throw regex::unknown_character_exception(std::string{'\\', ch});
            }
        } else {
            if (is_nonop(ch)) {
                last = ch;
            } else if (ch == '\\') {
                last = op::blackslash;
                continue;
            } else if (ch == '|') {
                last = op::alt;
            } else if (ch == '*') {
                last = op::star;
            } else if (ch == '+') {
                last = op::plus;
            } else if (ch == '(') {
                last = op::left_par;
            } else if (ch == ')') {
                last = op::right_par;
            } else {
                throw regex::unknown_character_exception(std::string{ch});
            }
        }
        result.push_back(last);
    }

    if (!result.empty()) {
        result.push_back(op::right_par);
        result.push_back(op::concat);
        result.push_back(symbol::end_mark);
    }

    return result;
}

static std::vector<token_type> to_postfix(const std::vector<token_type>& v) {
    std::vector<token_type> res;
    std::stack<token_type> ops;

    for (const auto& ch : v) {
        if (is_char(ch) || is_symbol(ch)) {
            res.push_back(ch);
        } else if (is(ch, op::left_par)) {
            ops.push(ch);
        } else if (is(ch, op::right_par)) {
            while (!ops.empty() && !is(ops.top(), op::left_par)) {
                res.push_back(ops.top());
                ops.pop();
            }
            ops.pop();
        } else if (is(ch, op::alt)) {
            while (!ops.empty() && get_precedence(ops.top()) >= get_precedence(op::alt)) {
                res.push_back(ops.top());
                ops.pop();
            }
            ops.push(ch);
        } else if (is(ch, op::concat)) {
            while (!ops.empty() && get_precedence(ops.top()) >= get_precedence(op::concat)) {
                res.push_back(ops.top());
                ops.pop();
            }
            ops.push(ch);
        } else if (is(ch, op::star) || is(ch, op::plus)) {
            ops.push(ch);
        } else {
            throw regex::unknown_character_exception(std::string{std::get<char>(ch)});
        }
    }

    while (!ops.empty()) {
        res.push_back(ops.top());
        ops.pop();
    }

    return res;
}

const std::unordered_map<char, std::string> escape_map = {
    {'\0', "\\0"},
    {'\a', "\\a"},
    {'\v', "\\v"},
    {'\n', "\\n"},
    {'\t', "\\t"},
    {'\r', "\\r"},
    {'\f', "\\f"}};

inline std::ostream& operator<<(std::ostream& os, const token_type& ch) {
    if (is_char(ch)) {
        char c = std::get<char>(ch);
        if (escape_map.find(c) != escape_map.end()) {
            os << escape_map.at(c);
        } else if (std::isprint(c)) {
            os << c;
        } else {
            os << '\\' << static_cast<int>(c);
        }
    } else if (is_op(ch)) {
        os << op_map.at(std::get<op>(ch));
    } else if (is_symbol(ch)) {
        os << symbol_map.at(std::get<symbol>(ch));
    }
    return os;
}

static void print(const std::vector<token_type>& v) {
    for (const auto& ch : v) {
        std::cout << ch << ' ';
    }
    std::cout << std::endl;
}
} // namespace regex

#endif // REGEX_TOKEN_HPP