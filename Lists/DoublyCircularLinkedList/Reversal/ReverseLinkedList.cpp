#include <iostream>
using namespace std;

struct node {
    int data;
    struct node* next;
    struct node* prev;
};

void reverselist(struct node** head_ref) {

    struct node* current = *head_ref;
    struct node* temp = NULL;

    if (*head_ref == NULL) {
        cout << "List is empty." << endl;
        return;
    }

    do {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    } while (current != *head_ref);

    *head_ref = temp->prev;
}

int main() {
    struct node* head = NULL;
    struct node* newnode, * tail, * temp;
    int choice = 1;

    while (choice != 0) {
        newnode = new node;
        cout << "Enter data: ";
        cin >> newnode->data;
        newnode->next = NULL;
        newnode->prev = NULL;

        if (head == NULL) {
            head = tail = newnode;
            head->next = head;
            head->prev = head;
        }
        else {
            tail->next = newnode;
            newnode->prev = tail;
            newnode->next = head;
            head->prev = newnode;
            tail = newnode;
        }

        cout << "Do you want to continue (0/1)? ";
        cin >> choice;
    }

    temp = head;
    cout << "Original list: ";
    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);
    cout << endl;

    reverselist(&head);

    temp = head;
    cout << "Reversed list: ";
    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);
    cout << endl;

    return 0;
}
