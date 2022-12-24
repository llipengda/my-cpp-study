#include <bits/stdc++.h>
using namespace std;
struct person {
    int number;
    person* link;
};
person* create(int n)
{
    person *head, *end, *node;
    head = new person;
    end = head;
    for (int i = 1; i <= n; i++) {
        node = new person;
        node->number = i;
        end->link = node;
        end = node;
    }
    end->link = head->link;
    return head;
}
int main()
{
    int n, m;
    cin >> n >> m;
    person* head = create(n);
    person* next = head->link;
    int i = 0;
    if (m == 1) {
        for (int i = 1; i <= n; i++)
            cout << i << ' ';
    } else {
        while (head != next) {
            ++i;
            if (i == m) {
                cout << next->number << ' ';
                head->link = next->link;
                delete next;
                next = head->link;
                i = 0;
            } else {
                head = head->link;
                next = next->link;
            }
        }
        cout << head->number;
    }
}