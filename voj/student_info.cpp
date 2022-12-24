#include <bits/stdc++.h>
using namespace std;
struct person {
    string number, name, gender, address;
    int age;
    double score;
    person* link;
};
person* createUp(void)
{
    person *head, *node;
    string number;
    head = new person;
    head->link = nullptr;
    cin >> number;
    while (number != "end") {
        node = new person;
        node->number = number;
        cin >> node->name >> node->gender >> node->age >> node->score >> node->address;
        node->link = head->link;
        head->link = node;
        cin >> number;
    }
    return head;
}
int main()
{
    person* head = createUp();
    while (head->link != nullptr) {
        head = head->link;
        cout << head->number << ' ' << head->name << ' ' << head->gender << ' ' << head->age << ' ' << head->score << ' ' << head->address << endl;
    }
}