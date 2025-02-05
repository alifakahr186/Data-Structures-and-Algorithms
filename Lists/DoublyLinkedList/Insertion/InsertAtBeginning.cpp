#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void insertAtBeginning(Node** head_ref, int new_data) {
    Node* new_node = new Node;

    new_node->data = new_data;
    new_node->prev = NULL;
    new_node->next = *head_ref;

    if (*head_ref != NULL) {
        (*head_ref)->prev = new_node;
    }

    *head_ref = new_node;
}

void printList(Node* node) {
    while (node != NULL) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

// Free the allocated memory
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
        cout << "Enter data to insert at the beginning: ";
        cin >> new_data;

        insertAtBeginning(&head, new_data);

        cout << "Do you want to continue adding nodes (0/1)? ";
        cin >> choice;
    }

    cout << "Linked list after insertion at the beginning: ";
    printList(head);

    // Free the dynamically allocated memory
    deleteList(&head);

    return 0;
}
