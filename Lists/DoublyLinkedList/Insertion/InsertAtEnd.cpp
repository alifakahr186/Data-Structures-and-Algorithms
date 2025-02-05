#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void insertAtEnd(Node** head_ref, int new_data) {
    Node* new_node = new Node;

    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }

    Node* temp = *head_ref;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = new_node;
    new_node->prev = temp;
}

void printList(Node* node) {
    while (node != NULL) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

void deleteList(Node** head_ref) {
    Node* temp;
    while (*head_ref != NULL) {
        temp = *head_ref;
        *head_ref = (*head_ref)->next;
        delete temp;
    }
    *head_ref = NULL;
}

int main() {
    Node* head = NULL;  
    int choice = 1;

    while (choice != 0) {
        int new_data;
        cout << "Enter data to insert at the end: ";
        cin >> new_data;

        insertAtEnd(&head, new_data);

        cout << "Do you want to continue adding nodes (0/1)? ";
        cin >> choice;
    }

    cout << "Linked list after insertions at the end: ";
    printList(head);

    // Free the dynamically allocated memory
    deleteList(&head);

    if (head == NULL) {
        cout << "Memory successfully freed and list deleted." << endl;
    }

    return 0;
}
