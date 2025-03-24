#include <bits/stdc++.h>

constexpr int days[] = {29, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
constexpr int values[] = {13, 1, 2, 3, 5, 4, 4, 2, 2, 2};

bool is_leap(int y) {
    return (y % 100 == 0 && y % 400 == 0) || y % 4 == 0;
}

std::string str(int v) {
    if (v < 10) {
        return "0" + std::to_string(v);
    }
    return std::to_string(v);
}

std::string next(const std::string& v) {
    auto year = std::stoi(v.substr(0, 4));
    auto month = std::stoi(v.substr(4, 2));
    auto day = std::stoi(v.substr(6));

    if (month == 12 && day == 31) {
        return str(year + 1) + str(1) + str(1);
    }
    auto month_index = month == 2 ? (is_leap(year) ? 0 : 2) : month;
    if (day == days[month_index]) {
        return str(year) + str(month + 1) + str(1);
    }
    return str(year) + str(month) + str(day + 1);
}

int count(const std::string& str) {
    int cnt{};
    for (auto c : str) {
        cnt += values[c - '0'];
    }
    return cnt;
}

int main() {
    int ans{};
    for (std::string s = "20000101"; s != "20240414"; s = next(s)) {
        if (count(s) > 50) {
            ans++;
        }
    }
    std::cout << ans << '\n';
}