#include <iostream>
#include <stdexcept>

namespace pdli {
template <typename T, typename U>
class hash_map {
    struct hash_map_record {
        hash_map_record() : key(-1){};
        hash_map_record(const T& key) : key(key){};
        hash_map_record(const T& key, const U& value) : key(key), value(value){};
        T key;
        U value;
        bool operator==(const hash_map_record& other) const {
            return key == other.key;
        }
    };

public:
    typedef hash_map_record record;
    static const record empty;
    hash_map();
    hash_map(std::size_t size);
    hash_map(const hash_map& other);
    ~hash_map() noexcept;
    hash_map& operator=(const hash_map& other);
    void clear();
    std::size_t size() const;
    void insert(const T& key, const U& value);
    static std::size_t hash_fun(const T& key, std::size_t size);
    U& get_value(const T& key);

protected:
    record* table;
    std::size_t _size;
};

template <typename T, typename U>
const typename hash_map<T, U>::record hash_map<T, U>::empty = hash_map<T, U>::record(-1);

template <typename T, typename U>
hash_map<T, U>::hash_map() {
    _size = 200;
    table = new record[_size + 1];
}

template <typename T, typename U>
hash_map<T, U>::hash_map(std::size_t size) {
    _size = size;
    table = new record[_size + 1];
}

template <typename T, typename U>
hash_map<T, U>::hash_map(const hash_map& other) {
    _size = other._size;
    table = new record[_size + 1];
    for (size_t i = 0; i < _size; i++) {
        table[i] = other.table[i];
    }
}

template <typename T, typename U>
void hash_map<T, U>::clear() {
    delete[] table;
}

template <typename T, typename U>
hash_map<T, U>::~hash_map() noexcept {
    clear();
}

template <typename T, typename U>
hash_map<T, U>& hash_map<T, U>::operator=(const hash_map<T, U>& other) {
    if (this == &other) return *this;
    clear();
    _size = other._size;
    table = new record[_size + 1];
    for (size_t i = 0; i < _size; i++) {
        table[i] = other.table[i];
    }
    return *this;
}

template <typename T, typename U>
std::size_t hash_map<T, U>::size() const {
    return _size;
}

template <typename T, typename U>
std::size_t hash_map<T, U>::hash_fun(const T& key, std::size_t size) {
    return key % size;
}

template <typename T, typename U>
void hash_map<T, U>::insert(const T& key, const U& value) {
    std::size_t pos = hash_fun(key, _size);
    if (table[pos] == empty) {
        table[pos] = {key, value};
        return;
    } else {
        for (std::size_t i = 1, cnt = 0; cnt < (_size + 1) / 2; i += 2) {
            ++cnt;
            pos = (pos + i) % _size;
            if (table[pos] == empty) {
                table[pos] = {key, value};
                return;
            }
        }
    }
    throw std::runtime_error("overflow");
}

template <typename T, typename U>
U& hash_map<T, U>::get_value(const T& key) {
    std::size_t pos = hash_fun(key, _size);
    std::cout << pos << ' ';
    if (table[pos] == key) {
        return table[pos].value;
    } else if (!(table[pos] == empty)) {
        for (std::size_t i = 1, cnt = 0; cnt < (_size + 1) / 2 - 1; i += 2) {
            ++cnt;
            pos = (pos + i) % _size;
            std::cout << pos << ' ';
            if (table[pos] == empty) break;
            if (table[pos] == key) {
                return table[pos].value;
            }
        }
    }
    throw std::runtime_error("not present");
}

} // namespace pdli

#include <iostream>
int main() {
    int n, m;
    std::cin >> n >> m;
    pdli::hash_map<int, int> mp(n);
    while (m--) {
        int key, value;
        std::cin >> key >> value;
        try {
            mp.insert(key, value);
        } catch (...) {
            
        }
    }
    int k1, k2;
    std::cin >> k1 >> k2;
    try {
        int v1 = mp.get_value(k1);
        std::cout << k1 << ' ' << v1 << std::endl;
    } catch (...) {
        std::cout << "NULL" << std::endl;
    }
    try {
        int v2 = mp.get_value(k2);
        std::cout << k2 << ' ' << v2 << std::endl;
    } catch (...) {
        std::cout << "NULL" << std::endl;
    }
}