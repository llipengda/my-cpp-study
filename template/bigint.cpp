#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>
#include <string>
#include <vector>

bool using_fft = false;

class FFT {
private:
    int _n, _m, _N;
    std::vector<int> r;
    const double PI = std::acos(-1);
    void expand(int temp);
    void fft(std::vector<std::complex<double>>& A, int f);
    std::vector<int> mul(std::vector<std::complex<double>>& A, std::vector<std::complex<double>>& B);

public:
    std::vector<int> multi(std::vector<int>& AA, std::vector<int>& BB);
};

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
    friend BigInt operator/(const BigInt& lhs, const long long& rhs);
    friend BigInt operator%(const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator%(const BigInt& lhs, const long long& rhs);
    BigInt& operator+=(const BigInt& other);
    BigInt& operator-=(const BigInt& other);
    BigInt& operator*=(const BigInt& other);
    BigInt& operator*=(const long long& other);
    BigInt& operator/=(const BigInt& other);
    BigInt& operator/=(const long long& other);
    BigInt& operator%=(const BigInt& other);
    BigInt& operator%=(const long long& other);
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;
    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    friend std::ostream& operator<<(std::ostream& out, const BigInt& a);
    friend std::istream& operator>>(std::istream& in, BigInt& a);
    size_t size() const;
    bool iszero() const;

private:
    void string_to_vector();
    void vector_to_string();
    bool greater_eq(std::vector<int> a, std::vector<int> b, int last_dg, int len);

protected:
    std::vector<int> v;
    std::string s;
    int f = 1;
};

void FFT::expand(int temp) {
    int L = 0;
    for (_N = 1; _N <= temp; _N <<= 1, L++)
        ;
    r.resize(_N + 1);
    for (int i = 0; i < _N; ++i) r[i] = r[i >> 1] >> 1 | (i & 1) << (L - 1);
    return;
}

void FFT::fft(std::vector<std::complex<double>>& A, int f) {
    for (int i = 0; i < _N; ++i)
        if (i < r[i]) std::swap(A[i], A[r[i]]);
    for (int i = 1; i < _N; i <<= 1) {
        std::complex<double> wn(std::cos(PI / i), f * std::sin(PI / i));
        for (int j = 0; j < _N; j += i << 1) {
            std::complex<double> w(1, 0);
            for (int k = 0; k < i; ++k, w *= wn) {
                std::complex<double> x = A[j + k], y = w * A[i + j + k];
                A[j + k] = x + y;
                A[i + j + k] = x - y;
            }
        }
    }
}

std::vector<int> FFT::mul(std::vector<std::complex<double>>& A, std::vector<std::complex<double>>& B) {
    expand(_n + _m);
    A.resize(_N + 1);
    B.resize(_N + 1);
    fft(A, 1);
    fft(B, 1);
    for (int i = 0; i <= _N; ++i) A[i] *= B[i];
    fft(A, -1);
    std::vector<int> vec;
    for (int i = 0; i < _n + _m - 1; ++i)
        vec.push_back((int)(A[i].real() / _N + 0.5));
    return vec;
}

std::vector<int> FFT::multi(std::vector<int>& AA, std::vector<int>& BB) {
    std::vector<std::complex<double>> A, B;
    _n = AA.size();
    _m = BB.size();
    A.resize(_n);
    B.resize(_m);
    for (int i = 0; i < _n; ++i) A[i] = AA[i];
    for (int i = 0; i < _m; ++i) B[i] = BB[i];
    return mul(A, B);
}

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

bool greater_eq(std::vector<int> a, std::vector<int> b, int last_dg, int len) {
    if (a[last_dg + len] != 0) return true;
    for (int i = len - 1; i >= 0; --i) {
        if (a[last_dg + i] > b[i]) return true;
        if (a[last_dg + i] < b[i]) return false;
    }
    return true;
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

bool BigInt::operator==(const BigInt& other) const { return !((*this < other) && (*this > other)); }

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

BigInt& BigInt::operator/=(const BigInt& other) {
    *this = *this / other;
    return *this;
}

BigInt& BigInt::operator/=(const long long& other) {
    *this = *this / other;
    return *this;
}

BigInt& BigInt::operator%=(const BigInt& other) {
    *this = *this % other;
    return *this;
}

BigInt& BigInt::operator%=(const long long& other) {
    *this = *this % other;
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
    BigInt res;
    if (lhs.f == rhs.f) {
        res.f = 1;
    } else {
        res.f = -1;
    }
    if (using_fft) {
        FFT F;
        std::vector<int> _lhs = lhs.v;
        std::vector<int> _rhs = rhs.v;
        res.v = F.multi(_lhs, _rhs);
        res.v.resize(lhs.v.size() + rhs.v.size());
        for (size_t i = 0; i < res.v.size(); i++) {
            res.v[i + 1] += res.v[i] / 10;
            res.v[i] %= 10;
        }
        res.vector_to_string();
        return res;
    }
    if (lhs.s == "0" || rhs.s == "0") {
        return BigInt(0LL);
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
    if (rhs > 9223372036854775807LL / 9 || using_fft) {
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

BigInt operator/(const BigInt& lhs, const BigInt& rhs) {
    BigInt res;
    if (lhs.f == rhs.f) {
        res.f = 1;
    } else {
        res.f = -1;
    }
    if (rhs.s == "0") throw std::runtime_error("division by zero");
    BigInt rem = lhs;
    rem.v.resize(lhs.v.size() + rhs.v.size());
    res.v.resize(lhs.v.size() + rhs.v.size());
    for (int i = lhs.v.size() - rhs.v.size(); i >= 0; i--) {
        while (greater_eq(rem.v, rhs.v, i, rhs.v.size())) {
            for (int j = 0; j < rhs.v.size(); ++j) {
                rem.v[i + j] -= rhs.v[j];
                if (rem.v[i + j] < 0) {
                    rem.v[i + j + 1] -= 1;
                    rem.v[i + j] += 10;
                }
            }
            res.v[i] += 1;
        }
    }
    res.vector_to_string();
    return res;
}

BigInt operator/(const BigInt& lhs, const long long& rhs) {
    return lhs / BigInt(rhs);
}

BigInt operator%(const BigInt& lhs, const BigInt& rhs) {
    BigInt res;
    if (lhs.f == rhs.f) {
        res.f = 1;
    } else {
        res.f = -1;
    }
    if (rhs.s == "0") throw std::runtime_error("division by zero");
    BigInt rem = lhs;
    rem.v.resize(lhs.v.size() + rhs.v.size());
    res.v.resize(lhs.v.size() + rhs.v.size());
    for (int i = lhs.v.size() - rhs.v.size(); i >= 0; i--) {
        while (greater_eq(rem.v, rhs.v, i, rhs.v.size())) {
            for (int j = 0; j < rhs.v.size(); ++j) {
                rem.v[i + j] -= rhs.v[j];
                if (rem.v[i + j] < 0) {
                    rem.v[i + j + 1] -= 1;
                    rem.v[i + j] += 10;
                }
            }
            res.v[i] += 1;
        }
    }
    rem.vector_to_string();
    return rem;
}

BigInt operator%(const BigInt& lhs, const long long& rhs) {
    return lhs / BigInt(rhs);
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

size_t BigInt::size() const {
    return v.size();
}

bool BigInt::iszero() const {
    return s == "0";
}

int main() {
    using_fft = true;
    BigInt a, b;
    int n = 1;
    // std::cin >> n;
    while (n--) {
        std::cin >> a >> b;
        std::cout << a + b << std::endl;
        std::cout << a - b << std::endl;
        std::cout << a * b << std::endl;
        std::cout << a / b << std::endl;
        std::cout << a % b << std::endl;
    }
}