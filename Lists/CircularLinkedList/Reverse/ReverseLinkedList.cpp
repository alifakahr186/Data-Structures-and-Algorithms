#include <iostream>
using namespace std;

struct node {
    int data;
    struct node* next;
};

// Function to reverse a circular linked list
void reverselist(struct node** head_ref) {

    struct node* prev = NULL;
    struct node* current = *head_ref;
    struct node* next;

    if (*head_ref == NULL)
        return;

    do {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    } while (current != *head_ref);

    (*head_ref)->next = prev;
    *head_ref = prev;
}

int main() {
    struct node *head = NULL, *newnode, *temp;
    int choice = 1;

    while (choice) {
        newnode = new node;
        cout << "Enter data: ";
        cin >> newnode->data;
        newnode->next = NULL;
        
        if (head == NULL) {
            head = temp = newnode;
        } 
        else {
            temp->next = newnode;
            temp = newnode;
        }

        temp->next = head;

        cout << "Do you want to continue(1/0)? ";
        cin >> choice;
    }

    cout << "Original circular linked list: ";
    temp = head;
    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);

    // Reverse the circular linked list
    reverselist(&head);

    cout << "\nReversed circular linked list: ";
    temp = head;
    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);

    return 0;
}
