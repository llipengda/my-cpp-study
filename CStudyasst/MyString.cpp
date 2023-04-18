#include <cstring>
#include <iostream>

class MyString {
public:
    MyString();
    ~MyString();
    MyString(const MyString& other);
    MyString(const char* other);
    size_t length() const;
    const char* c_str() const;
    MyString& operator=(const MyString& other);
    bool operator<(const MyString& other) const;
    bool operator>(const MyString& other) const;
    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;
    bool operator>=(const MyString& other) const;
    bool operator<=(const MyString& other) const;
    void operator+=(const MyString& rhs);
    friend MyString operator+(const MyString& lhs, const MyString& rhs);
    friend std::istream& operator>>(std::istream& in, MyString& str);
    friend std::ostream& operator<<(std::ostream& out, const MyString& str);
    char& operator[](const size_t n) const;
    int64_t find(const MyString& other) const;
protected:
    char* entries;
    size_t len;
};

MyString::MyString() {
    entries = nullptr;
    len = 0;
}

MyString::~MyString() {
    delete[] entries;
    len = 0;
}

MyString::MyString(const MyString& other) {
    len = other.len;
    entries = new char[len + 1];
    strcpy(entries, other.entries);
}

MyString::MyString(const char* other) {
    len = strlen(other);
    entries = new char[len + 1];
    strcpy(entries, other);
}

size_t MyString::length() const {
    return len;
}

const char* MyString::c_str() const {
    return static_cast<const char*>(entries);
}

MyString& MyString::operator=(const MyString& other) {
    if (this == &other) return *this;
    if (len != 0) delete[] entries;
    len = other.len;
    entries = new char[len + 1];
    strcpy(entries, other.entries);
    return *this;
}

bool MyString::operator<(const MyString& other) const {
    return strcmp(entries, other.entries) < 0;
}

bool MyString::operator>(const MyString& other) const {
    return strcmp(entries, other.entries) > 0;
}

bool MyString::operator==(const MyString& other) const {
    return strcmp(entries, other.entries) == 0;
}

bool MyString::operator<=(const MyString& other) const {
    return !(*this > other);
}

bool MyString::operator>=(const MyString& other) const {
    return !(*this < other);
}

bool MyString::operator!=(const MyString& other) const {
    return !(*this == other);
}

MyString operator+(const MyString& lhs, const MyString& rhs) {
    MyString ans;
    ans.len = lhs.len + rhs.len;
    ans.entries = new char[ans.len + 1];
    strcpy(ans.entries, lhs.entries);
    strcat(ans.entries, rhs.entries);
    return ans;
}

void MyString::operator+=(const MyString& rhs) {
    *this = *this + rhs;
}

std::istream& operator>>(std::istream& in, MyString& str) {
    char temp[1024];
    in >> temp;
    str = temp;
    return in;
}

std::ostream& operator<<(std::ostream& out, const MyString& str) {
    out << str.entries;
    return out;
}

char& MyString::operator[](const size_t n) const {
    if (n >= len) throw std::range_error("out of range");
    return entries[n];
}

int64_t MyString::find(const MyString& sub) const {
    if (strstr(entries, sub.entries) == nullptr) {
        return -1;
    } else {
        return strstr(entries, sub.entries) - entries;
    }
}
