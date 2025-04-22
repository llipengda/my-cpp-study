#pragma once

#ifndef REGEX_TREE_HPP
#define REGEX_TREE_HPP

#include "exception.hpp"
#include "token.hpp"

#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace regex {

class regex_node {
public:
    enum class type {
        ch,
        concat,
        alt,
        star
    };

    using node_ptr_t = std::shared_ptr<regex_node>;

    type type;

    bool nullable;
    std::unordered_set<std::size_t> firstpos;
    std::unordered_set<std::size_t> lastpos;

    virtual ~regex_node() = default;

    template <class T>
    T& as() {
        return static_cast<T&>(*this);
    }
};

class char_node : public regex_node {
public:
    token_type value;
    size_t number;

    explicit char_node(token_type ch, size_t number) : value(ch), number(number) {
        type = type::ch;
        nullable = false;
        firstpos.insert(number);
        lastpos.insert(number);
    }
};

class concat_node : public regex_node {
public:
    node_ptr_t left, right;
    explicit concat_node(node_ptr_t left, node_ptr_t right) : left(left), right(right) {
        type = type::concat;
        nullable = left->nullable && right->nullable;
        firstpos = left->firstpos;
        if (left->nullable) {
            firstpos.insert(right->firstpos.begin(), right->firstpos.end());
        }
        lastpos = right->lastpos;
        if (right->nullable) {
            lastpos.insert(left->lastpos.begin(), left->lastpos.end());
        }
    }
};

class star_node : public regex_node {
public:
    node_ptr_t child;
    explicit star_node(node_ptr_t child) : child(child) {
        type = type::star;
        nullable = true;
        firstpos = child->firstpos;
        lastpos = child->lastpos;
    }
};

class alt_node : public regex_node {
public:
    node_ptr_t left, right;
    explicit alt_node(node_ptr_t left, node_ptr_t right) : left(left), right(right) {
        type = type::alt;
        nullable = left->nullable || right->nullable;
        firstpos = left->firstpos;
        firstpos.insert(right->firstpos.begin(), right->firstpos.end());
        lastpos = left->lastpos;
        lastpos.insert(right->lastpos.begin(), right->lastpos.end());
    }
};

class regex_tree {
public:
    regex_node::node_ptr_t root;

    std::unordered_map<token_type, std::unordered_set<std::size_t>> token_map;

    std::unordered_map<std::size_t, std::unordered_set<std::size_t>> followpos;

    explicit regex_tree(regex_node& root) : root(&root) {}

    explicit regex_tree(const std::string& s) {
        auto ss = regex::split(s);
#ifdef SHOW_DEBUG
        ::regex::print(ss);
#endif
        auto postfix = to_postfix(ss);
#ifdef SHOW_DEBUG
        ::regex::print(postfix);
#endif

        std::stack<regex_node::node_ptr_t> st;

        size_t i = 1;

        for (const auto& ch : postfix) {
            if (is(ch, op::star)) {
                if (st.empty()) {
                    throw regex::invalid_regex_exception("'*' operator with empty stack");
                }
                auto operand = st.top();
                st.pop();
                st.push(std::make_shared<star_node>(star_node{operand}));
            } else if (is(ch, op::concat)) {
                if (st.size() < 2) {
                    throw regex::invalid_regex_exception("'·' operator with fewer than 2 operands");
                }
                auto right = st.top();
                st.pop();
                auto left = st.top();
                st.pop();
                st.push(std::make_shared<concat_node>(concat_node{left, right}));
            } else if (is(ch, op::alt)) {
                if (st.size() < 2) {
                    throw regex::invalid_regex_exception("'|' operator with fewer than 2 operands");
                }
                auto right = st.top();
                st.pop();
                auto left = st.top();
                st.pop();
                st.push(std::make_shared<alt_node>(alt_node{left, right}));
            } else if (is_nonop(ch)) {
                token_map[ch].insert(i);
                st.push(std::make_shared<char_node>(char_node{ch, i++}));
            } else {
                throw regex::invalid_regex_exception(s);
            }
        }

        if (st.size() != 1) {
            throw regex::invalid_regex_exception("leftover operands after parsing");
        }

        root = st.top();
        st.pop();

        visit([&](regex_node& node) {
            if (node.type == regex_node::type::concat) {
                auto& concat_node = node.as<regex::concat_node>();
                for (auto i : concat_node.left->lastpos) {
                    followpos[i].insert(concat_node.right->firstpos.begin(), concat_node.right->firstpos.end());
                }
            } else if (node.type == regex_node::type::star) {
                auto& star_node = node.as<regex::star_node>();
                for (auto i : star_node.lastpos) {
                    followpos[i].insert(star_node.firstpos.begin(), star_node.firstpos.end());
                }
            }
        });
    }

    void visit(std::function<void(regex_node&)> func) {
        visit(root, func);
    }

    void print() const {
        std::cout << "Regex Tree" << std::endl;
        print(root);
    }

private:
    void visit(regex_node::node_ptr_t node, std::function<void(regex_node&)> func) {
        if (node == nullptr) {
            return;
        }

        func(*node.get());

        if (node->type == regex_node::type::concat) {
            auto& concat_node = node->as<regex::concat_node>();
            visit(concat_node.left, func);
            visit(concat_node.right, func);
        } else if (node->type == regex_node::type::alt) {
            auto& alt_node = node->as<regex::alt_node>();
            visit(alt_node.left, func);
            visit(alt_node.right, func);
        } else if (node->type == regex_node::type::star) {
            auto& star_node = node->as<regex::star_node>();
            visit(star_node.child, func);
        }
    }

    void print(regex_node::node_ptr_t node, int indent = 0) const {
        if (node == nullptr) {
            return;
        }
        std::cout << std::string(indent, ' ');
        if (node->type == regex_node::type::ch) {
            auto& char_node = node->as<regex::char_node>();
            std::cout << char_node.value << '(' << char_node.number << ')' << std::endl;
        } else if (node->type == regex_node::type::concat) {
            std::cout << op_map.at(op::concat) << std::endl;
            print(node->as<regex::concat_node>().left, indent + 2);
            print(node->as<regex::concat_node>().right, indent + 2);
        } else if (node->type == regex_node::type::alt) {
            std::cout << op_map.at(op::alt) << std::endl;
            print(node->as<regex::alt_node>().left, indent + 2);
            print(node->as<regex::alt_node>().right, indent + 2);
        } else if (node->type == regex_node::type::star) {
            std::cout << op_map.at(op::star) << std::endl;
            print(node->as<regex::star_node>().child, indent + 2);
        }
    }
};

} // namespace regex

#endif // REGEX_TREE_HPP
