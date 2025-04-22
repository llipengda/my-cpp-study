#define SHOW_DEBUG
#include "regex/dfa.hpp"

int main() {
    std::string regex;
    std::cin >> regex;

    std::string str;
    std::cin >> str;

    regex::dfa d(regex);
    std::cout << "Match: " << (d.match(str) ? "true" : "false") << std::endl;
}