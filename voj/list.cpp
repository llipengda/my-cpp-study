#include <bits/stdc++.h>
using namespace std;
struct person {
    int info;
    person* link;
};
person* createDown(void)
{
    int data;
    person *head, *end, *node;
    head = new person;
    end = head;
    while (cin >> data) {
        node = new person;
        node->info = data;
        end->link = node;
        end = node;
    }
    end->link = nullptr;
    return head;
}
person* createUp(void)
{
    person *head, *node;
    int data;
    head = new person;
    head->link = nullptr;
    while (cin >> data) {
        node = new person;
        node->info = data;
        node->link = head->link;
        head->link = node;
    }
    return head;
}
int main()
{
    person* head = createUp();
    while (head->link != nullptr) {
        head = head->link;
        cout << head->info << ' ';
    }
}