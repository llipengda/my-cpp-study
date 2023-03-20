#include <algorithm>
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>


class BigInt {
public:
    BigInt(){};
    BigInt(const long long& x) : s(std::to_string(x)) { string_to_vector(); }
    BigInt(const std::string& s) : s(s) { string_to_vector(); }
    BigInt(const std::vector<int> v, int f = 1) : v(v), f(f) { vector_to_string(); }
    BigInt(const char* s) : s(std::string(s)) { string_to_vector(); }
    BigInt(const BigInt& other) : v(other.v), f(other.f), s(other.s) {}
    BigInt& operator=(const BigInt& other);
    BigInt& operator=(const std::string& other);
    BigInt& operator=(const char* other);
    BigInt& operator=(long long& other);
    friend BigInt operator+(const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator-(const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator*(const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator*(const BigInt& lhs, const long long& rhs);
    friend BigInt operator/(const BigInt& lhs, const BigInt& rhs);
    BigInt& operator+=(const BigInt& other);
    BigInt& operator-=(const BigInt& other);
    BigInt& operator*=(const BigInt& other);
    BigInt& operator*=(const long long& other);
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;
    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    friend std::ostream& operator<<(std::ostream& out, const BigInt& a);
    friend std::istream& operator>>(std::istream& in, BigInt& a);

private:
    void string_to_vector();
    void vector_to_string();

protected:
    std::vector<int> v;
    std::string s;
    int f = 1;
};

void BigInt::string_to_vector() {
    if (s[0] == '-') f = -1;
    v.resize(f == 1 ? s.size() : s.size() - 1);
    for (size_t i = (f == 1 ? 0 : 1); i < (f == 1 ? v.size() : v.size() + 1); i++) {
        v[f == 1 ? i : i - 1] = s[i] - '0';
    }
    std::reverse(v.begin(), v.end());
}

void BigInt::vector_to_string() {
    while (v.back() == 0 && v.size() > 1) v.pop_back();
    std::reverse(v.begin(), v.end());
    s.resize(f == 1 ? v.size() : v.size() + 1);
    if (f == -1) s[0] = '-';
    for (size_t i = (f == 1 ? 0 : 1); i < s.size(); i++) {
        s[i] = v[f == 1 ? i : i - 1] + '0';
    }
    if (s == "-0") {
        s = "0";
        f = 0;
    }
    std::reverse(v.begin(), v.end());
}

BigInt& BigInt::operator=(const BigInt& other) {
    v = other.v;
    s = other.s;
    f = other.f;
    return *this;
}

BigInt& BigInt::operator=(const std::string& other) {
    BigInt n(other);
    *this = n;
    return *this;
}

BigInt& BigInt::operator=(const char* other) {
    BigInt n(other);
    *this = n;
    return *this;
}

BigInt& BigInt::operator=(long long& other) {
    BigInt n(other);
    *this = n;
    return *this;
}

bool BigInt::operator<(const BigInt& other) const {
    if (f == other.f) {
        return f == 1 ? s < other.s : s > other.s;
    } else {
        return f == -1;
    }
}

bool BigInt::operator>(const BigInt& other) const {
    if (f == other.f) {
        return f == 1 ? s > other.s : s < other.s;
    } else {
        return f == 1;
    }
}

bool BigInt::operator<=(const BigInt& other) const { return !(*this > other); }

bool BigInt::operator>=(const BigInt& other) const { return !(*this < other); }

bool BigInt::operator==(const BigInt& other) const {
    return !((*this < other) && (*this > other));
}

bool BigInt::operator!=(const BigInt& other) const { return !(*this == other); }

BigInt& BigInt::operator+=(const BigInt& other) {
    BigInt _other(other);
    v.resize(std::max(v.size(), _other.v.size()) + 1);
    v.back() = 0;
    if (f == -1) {
        for (auto& i : v) i = -i;
    }
    if (_other.f == -1) {
        for (auto& i : _other.v) i = -i;
    }
    for (size_t i = 0; i < v.size(); i++) {
        v[i] += (i < _other.v.size() ? _other.v[i] : 0);
    }
    size_t negative_pos = 0;
    bool find_negative_pos = false;
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] <= -10) {
            v[i] += 10;
            v[i + 1]--;
        }
    }
    for (size_t i = 0; i < v.size() - 1; i++) {
        if (v[i] >= 10) {
            v[i] -= 10;
            v[i + 1]++;
        } else if (v[i] < 0) {
            if (!find_negative_pos) {
                negative_pos = i;
                find_negative_pos = true;
            }
            v[i] += 10;
            v[i + 1]--;
        }
    }
    if (v.back() == -1) {
        v.pop_back();
        f = -1;
        v[negative_pos] -= 10;
        v[negative_pos] = -v[negative_pos];
        for (size_t i = negative_pos + 1; i < v.size(); i++) {
            v[i] -= 9;
            v[i] = -v[i];
        }
        size_t positive_pos = 0;
        if (negative_pos != 0) {
            for (; v[positive_pos] == 0; positive_pos++)
                ;
            if (positive_pos != negative_pos) {
                v[positive_pos] = 10 - v[positive_pos];
                v[negative_pos]--;
            }
        }
        for (size_t i = positive_pos + 1; i < negative_pos; i++) {
            v[i] = 9 - v[i];
        }
    } else if (v.back() == 0) {
        v.pop_back();
    }
    vector_to_string();
    return *this;
}

BigInt& BigInt::operator-=(const BigInt& other) {
    BigInt _other(other);
    _other.f = -_other.f;
    *this += _other;
    return *this;
}

BigInt& BigInt::operator*=(const BigInt& other) {
    *this = *this * other;
    return *this;
}

BigInt& BigInt::operator*=(const long long& other) {
    *this = *this * other;
    return *this;
}

BigInt operator+(const BigInt& lhs, const BigInt& rhs) {
    BigInt res(lhs);
    return res += rhs;
}

BigInt operator-(const BigInt& lhs, const BigInt& rhs) {
    BigInt res(lhs);
    return res -= rhs;
}

BigInt operator*(const BigInt& lhs, const BigInt& rhs) {
    if (lhs.s == "0" || rhs.s == "0") {
        return BigInt(0LL);
    }
    BigInt res;
    if (lhs.f == rhs.f) {
        res.f = 1;
    } else {
        res.f = -1;
    }
    res.v.resize(lhs.v.size() + rhs.v.size());
    for (auto& i : res.v) i = 0;
    for (size_t i = 0; i < lhs.v.size(); i++) {
        for (size_t j = 0; j < rhs.v.size(); j++) {
            res.v[i + j] += lhs.v[i] * rhs.v[j];
            if (res.v[i + j] >= 10) {
                res.v[i + j + 1] += res.v[i + j] / 10;
                res.v[i + j] %= 10;
            }
        }
    }
    res.vector_to_string();
    return res;
}

BigInt operator*(const BigInt& lhs, const long long& rhs) {
    if (lhs.s == "0" || rhs == 0) {
        return BigInt(0LL);
    }
    if (rhs > 9223372036854775807LL / 9) {
        return lhs * BigInt(rhs);
    }
    BigInt res;
    if (lhs.f == (rhs > 0 ? 1 : (rhs < 0 ? -1 : 0))) {
        res.f = 1;
    } else {
        res.f = -1;
    }
    res.v.resize(lhs.v.size() + std::to_string(rhs).size());
    std::vector<unsigned long long> tmp_v(res.v.size(), 0);
    for (auto& i : res.v) i = 0;
    for (size_t i = 0; i < lhs.v.size(); i++) {
        tmp_v[i] += lhs.v[i] * rhs;
        tmp_v[i + 1] += tmp_v[i] / 10;
        tmp_v[i] %= 10;
    }
    for (size_t i = lhs.v.size(); i < tmp_v.size(); i++) {
        tmp_v[i + 1] += tmp_v[i] / 10;
        tmp_v[i] %= 10;
    }
    for (size_t i = 0; i < tmp_v.size(); i++) res.v[i] = tmp_v[i];
    res.vector_to_string();
    return res;
}

std::ostream& operator<<(std::ostream& out, const BigInt& a) {
    out << a.s;
    return out;
}

std::istream& operator>>(std::istream& in, BigInt& a) {
    std::string str;
    in >> str;
    a = str;
    return in;
}

int main() {
    BigInt a, b;
    int n = 1;
    // std::cin >> n;
    while (n--) {
        std::cin >> a >> b;
        std::cout << a * b << std::endl;
    }
}