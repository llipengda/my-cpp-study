#include <bits/stdc++.h>
using namespace std;
struct number {
    int real, imagine;
    number* link;
};
//BUG 
number* createDown(int n)
{
    number *head, *node, *end;
    head = new number;
    end = head;
    while (n--) {
        node = new number;
        cin >> node->real >> node->imagine;
        end->link = node;
        end = node;
    }
    end->link = nullptr;
    return head;
}
int main()
{
    number* head = createDown(10);
    int real = 0, imagine = 0;
    while (head->link != nullptr) {
        head = head->link;
        real += head->real;
        imagine += head->imagine;
    }
    cout<<real<<'+'<<imagine<<'i';
}