#include <bits/stdc++.h>
using ll = long long;
using namespace std;

constexpr int mod = 998244353;
int _norm(int x) {
    if (x < 0) {
        x += mod;
    }
    if (x >= mod) {
        x -= mod;
    }
    return x;
}
template <class T>
T power(T a, ll b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
struct ModInt {
    int x;
    ModInt(int x = 0) : x(_norm(x)) {}
    ModInt(ll x) : x(_norm(x % mod)) {}
    int val() const {
        return x;
    }
    ModInt operator-() const {
        return ModInt(_norm(mod - x));
    }
    ModInt inv() const {
        assert(x != 0);
        return power(*this, mod - 2);
    }
    ModInt& operator*=(const ModInt& rhs) {
        x = ll(x) * rhs.x % mod;
        return *this;
    }
    ModInt& operator+=(const ModInt& rhs) {
        x = _norm(x + rhs.x);
        return *this;
    }
    ModInt& operator-=(const ModInt& rhs) {
        x = _norm(x - rhs.x);
        return *this;
    }
    ModInt& operator/=(const ModInt& rhs) {
        return *this *= rhs.inv();
    }
    friend ModInt operator*(const ModInt& lhs, const ModInt& rhs) {
        ModInt res = lhs;
        res *= rhs;
        return res;
    }
    friend ModInt operator+(const ModInt& lhs, const ModInt& rhs) {
        ModInt res = lhs;
        res += rhs;
        return res;
    }
    friend ModInt operator-(const ModInt& lhs, const ModInt& rhs) {
        ModInt res = lhs;
        res -= rhs;
        return res;
    }
    friend ModInt operator/(const ModInt& lhs, const ModInt& rhs) {
        ModInt res = lhs;
        res /= rhs;
        return res;
    }
    friend std::istream& operator>>(std::istream& is, ModInt& a) {
        ll v;
        is >> v;
        a = ModInt(v);
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const ModInt& a) {
        return os << a.val();
    }
};