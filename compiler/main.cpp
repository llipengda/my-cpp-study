#define SHOW_DEBUG
#include "regex/regex.hpp"

int main() {
    std::string regex = R"(ab|\wd)";
    std::string str = "ad";

    regex::regex r(regex);
    std::cout << "Match: " << (r.match(str) ? "true" : "false") << std::endl;
}