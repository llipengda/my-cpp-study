#include <bits/stdc++.h>

struct bigint {
    std::vector<int> v = std::vector<int>(200, 0);
    int f = 1;
    int len = 0;

    friend std::ostream& operator<<(std::ostream&, bigint&);

    bigint(const std::string& str) {
        int i = 0;
        for (int k = str.length() - 1; k >= 0; k--) {
            auto c = str[k];
            if (c == '-') {
                f = -1;
                continue;
            }
            v[i++] = c - '0';
        }
        len = i;
    }

    bigint(const std::vector<int>& v, int len, int f) {
        this->v = v;
        this->v.resize(200);
        this->f = f;
        this->len = len;
    }

    bigint square() const {
        std::vector<int> nv(len * 2, 0);
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                nv[j + i] += v[j] * v[i];
            }
        }
        int l = 0;
        for (int i = 0; i < len * 2; i++) {
            nv[i + 1] += nv[i] / 10;
            nv[i] %= 10;
            if (nv[i] != 0) {
                l = i + 1;
            }
        }
        return bigint(nv, l, 1);
    }

    bigint operator-(const bigint& rhs) const {
        // assert rhs > 0
        std::vector<int> resv(200, 0);

        int f = 1;
        if (len < rhs.len) {
            f = -1;
        } else if (len == rhs.len) {
            for (int i = len - 1; i >= 0; i--) {
                if (v[i] < rhs.v[i]) {
                    f = -1;
                    break;
                } else if (v[i] > rhs.v[i]) {
                    break;
                }
            }
        }

        auto lv = v;
        auto rv = rhs.v;

        if (f == -1) {
            lv.swap(rv);
        }

        // assert lhs > rhs
        auto max_len = std::max(len, rhs.len);
        for (int i = 0; i < max_len; i++) {
            auto l = lv[i];
            auto r = rv[i];
            if (l < r) {
                resv[i] = l + 10 - r;
                int k = i + 1;
                while (lv[k] <= 0) {
                    lv[k++] = 9;
                }
                lv[k] -= 1;
            } else {
                resv[i] = l - r;
            }
        }

        int i = max_len - 1;
        while (resv[i--] == 0) {
            max_len--;
        }
        
        return bigint(resv, max_len, f);
    }
};

std::ostream& operator<<(std::ostream& out, const bigint& a) {
    if (a.f == -1){
        out << '-';
    }
    for (int i = a.len - 1; i >= 0; i--) {
        out << a.v[i];
    }
    return out;
}

int main() {
    std::string str_a, str_b;
    std::cin >> str_a >> str_b;
    bigint a{str_a};
    bigint b{str_b};
    std::cout << a.square() - b.square();
}