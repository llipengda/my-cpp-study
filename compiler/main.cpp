#define SHOW_DEBUG
#include "regex/regex.hpp"

int main() {
    std::string regex;
    std::cin >> regex;

    std::string str;
    std::cin >> str;

    regex::regex r(regex);
    std::cout << "Match: " << (r.match(str) ? "true" : "false") << std::endl;
}