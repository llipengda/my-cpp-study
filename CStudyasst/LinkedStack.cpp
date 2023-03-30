#include <stdexcept>

template <typename T>
struct Node {
    T entry;
    Node* next;
    Node() : next(nullptr) {}
    Node(const T& item, Node* add_on = nullptr) : entry(item), next(add_on) {}
};

template <typename T>
class LinkedStack {
public:
    LinkedStack() : top_node(nullptr){}
    LinkedStack(const LinkedStack& other);
    ~LinkedStack();
    bool empty() const;
    void push(const T& item);
    void pop();
    void clear();
    T& top() const;
    size_t size() const;
    LinkedStack& operator=(const LinkedStack& other);

protected:
    Node<T>* top_node;
};

template <typename T>
LinkedStack<T>::LinkedStack(const LinkedStack<T>& other) {
    Node<T>* new_node = new Node<T>;
    top_node = new_node;
    Node<T>* head = other.top_node;
    while (head->next != nullptr) {
        head = head->next;
        new_node->next = new Node<T>(head->entry, head->next);
        new_node = new_node->next;
    }
    top_node->entry = other.top_node->entry;
}

template <typename T>
void LinkedStack<T>::push(const T& item) {
    Node<T>* new_node = new Node<T>(item, top_node);
    if (new_node == nullptr) throw std::bad_alloc();
    top_node = new_node;
}

template <typename T>
void LinkedStack<T>::pop() {
    if (top_node == nullptr) throw std::underflow_error("underflow");
    Node<T>* to_be_delete = top_node;
    top_node = top_node->next;
    delete to_be_delete;
}

template <typename T>
T& LinkedStack<T>::top() const {
    if (top_node == nullptr) throw std::underflow_error("underflow");
    return top_node->entry;
}

template <typename T>
bool LinkedStack<T>::empty() const {
    return top_node == nullptr;
}

template <typename T>
size_t LinkedStack<T>::size() const {
    if (top_node == nullptr) return 0;
    size_t count = 0;
    Node<T>* head = top_node;
    for (; head->next != nullptr; head = head->next)
        count++;
    return count;
}

template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack<T>& other) {
    if (top_node == other.top_node) return *this;
    clear();
    Node<T>* new_node = new Node<T>;
    top_node = new_node;
    Node<T>* head = other.top_node;
    while (head->next != nullptr) {
        head = head->next;
        new_node->next = new Node<T>(head->entry, head->next);
        new_node = new_node->next;
    }
    top_node->entry = other.top_node->entry;
    return *this;
}

template <typename T>
void LinkedStack<T>::clear() {
    Node<T>* to_be_delete = top_node;
    Node<T>* head = top_node;
    while (head != nullptr) {
        head = head->next;
        delete to_be_delete;
        to_be_delete = head;
    }
    top_node = nullptr;
}

template <typename T>
LinkedStack<T>::~LinkedStack<T>() {
    Node<T>* to_be_delete = top_node;
    Node<T>* head = top_node;
    while (head != nullptr) {
        head = head->next;
        delete to_be_delete;
        to_be_delete = head;
    }
}