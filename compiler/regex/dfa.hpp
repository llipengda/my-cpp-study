#pragma once

#ifndef REGEX_DFA_HPP
#define REGEX_DFA_HPP

#include "token.hpp"
#include "tree.hpp"

#include <cstddef>
#include <unordered_set>

namespace regex {
class dfa {
public:
    using state_t = std::size_t;
    using token_t = regex::token_type;
    using transition_t = std::unordered_map<state_t, state_t>;
    using dfa_state_t = std::unordered_map<token_t, transition_t>;

    dfa() = delete;

    explicit dfa(const regex::regex_tree& tree) {
        init(tree);
    }

    explicit dfa(const std::string& regex) {
        regex_tree tree(regex);
#ifdef SHOW_DEBUG
        tree.print();
#endif
        init(tree);
#ifdef SHOW_DEBUG
        this->print();
#endif
    }

    void add_transition(state_t from, const token_t& token, state_t to) {
        transitions[token][from] = to;
    }

    bool match(const std::string& str) const {
        state_t current_state = 1;
        for (const auto& ch : str) {
            bool find = false;
            for (const auto& token : regex::get_possible_token(ch)) {
                if (transitions.find(token) == transitions.end()) {
                    continue;
                }
                auto it = transitions.at(token).find(current_state);
                if (it == transitions.at(token).end()) {
                    continue;
                }
                current_state = it->second;
                find = true;
                break;
            }
            if (!find) {
                return false;
            }
        }
        return accept_states.count(current_state) > 0;
    }

    const dfa_state_t& get_transitions() const {
        return transitions;
    }

    void print() const {
        std::cout << "DFA" << std::endl;
        for (const auto& [token, trans] : transitions) {
            for (const auto& [from, to] : trans) {
                std::cout << "  Transition: " << from << " -- " << token << " --> " << to << std::endl;
            }
        }
        std::cout << "  Accept states: ";
        for (const auto& state : accept_states) {
            std::cout << state << " ";
        }
        std::cout << std::endl;
    }

private:
    dfa_state_t transitions;
    std::unordered_set<state_t> accept_states;

    struct d_state_t {
        std::unordered_set<state_t> states;
        state_t id;

        bool operator==(const d_state_t& other) const {
            return states == other.states;
        }
    };

    struct d_state_t_hash {
        std::size_t operator()(const d_state_t& s) const {
            std::size_t h = 0;
            for (auto v : s.states) {
                h += std::hash<state_t>{}(v);
            }
            return h;
        }
    };

    void init(const regex::regex_tree& tree) {
        // TODO：using std::unordered_set
        std::unordered_set<d_state_t, d_state_t_hash> d_states;
        size_t cur = 1;
        d_states.insert({std::unordered_set<state_t>(tree.root->firstpos.begin(), tree.root->firstpos.end()), cur++});

        std::unordered_set<d_state_t, d_state_t_hash> unmarked_d_states = d_states;

        std::unordered_set<token_t> all_tokens;
        for (const auto& token : tree.token_map) {
            all_tokens.insert(token.first);
        }

        auto& token_map = tree.token_map;
        auto& followpos = tree.followpos;

        while (!unmarked_d_states.empty()) {
            auto d_state = *unmarked_d_states.begin();
            unmarked_d_states.erase(unmarked_d_states.begin());

            for (const auto& token : all_tokens) {
                if (regex::is(token, regex::symbol::end_mark)) {
                    continue;
                }

                d_state_t u;
                for (auto i : token_map.at(token)) {
                    if (d_state.states.count(i)) {
                        u.states.insert(followpos.at(i).begin(), followpos.at(i).end());
                    }
                }

                auto it = d_states.find(u);
                if (it == d_states.end()) {
                    u.id = cur++;
                    d_states.insert(u);
                    unmarked_d_states.insert(u);
                } else {
                    u.id = it->id;
                }

                if (u.states.count(*token_map.at(regex::symbol::end_mark).begin())) {
                    accept_states.insert(u.id);
                }

                add_transition(d_state.id, token, u.id);
            }
        }
    }
};
} // namespace regex

#endif // REGEX_DFA_HPP