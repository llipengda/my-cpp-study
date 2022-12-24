#include <bits/stdc++.h>
using namespace std;
struct number {
    int info;
    number* link;
};
number* createDown(int n)
{
    number *head, *node, *end;
    head = new number;
    end = head;
    while (n--) {
        node = new number;
        cin >> node->info;
        end->link = node;
        end = node;
    }
    end->link = nullptr;
    return head;
}
int main()
{
    int n, k;
    cin >> n;
    number* head = createDown(n);
    number *head2 = head, *head3 = head;
    number* next = head->link;
    cin >> k;
    while (head->link != nullptr) {
        if (next->info == k) {
            head->link = next->link;
            delete next;
            next = head->link;
        } else {
            head = head->link;
            next = next->link;
        }
    }
    while (head2->link != nullptr) {
        head2 = head2->link;
        cout << head2->info << ' ';
    }
    while (head3->link != nullptr) {
        number* tmp = head3->link;
        delete head3;
        head3 = tmp;
    }
}