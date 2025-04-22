#define SHOW_DEBUG
#include "regex/regex.hpp"

int main() {
    std::string regex = R"(\w+\s+\w+\+)";
    std::string str = "abcde00 \t\n ff44+";

    regex::regex r(regex);
    std::cout << "Match: " << (r.match(str) ? "true" : "false") << std::endl;
}