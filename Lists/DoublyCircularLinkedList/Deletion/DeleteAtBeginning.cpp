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

    if (*head_ref == NULL) {
        *head_ref = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
    } else {
        Node* tail = (*head_ref)->prev;

        new_node->next = *head_ref;
        new_node->prev = tail;
        tail->next = new_node;
        (*head_ref)->prev = new_node;
    }
}

void deleteFromBeginning(Node** head_ref) {
    if (*head_ref == NULL) {
        cout << "Linked list is empty." << endl;
        return;
    }

    Node* temp = *head_ref;

    if ((*head_ref)->next == *head_ref) {
        *head_ref = NULL;
        delete temp;
        return;
    }

    Node* tail = (*head_ref)->prev;
    *head_ref = (*head_ref)->next;
    (*head_ref)->prev = tail;
    tail->next = *head_ref;
    
    delete temp;
}

void printList(Node* head) {
    if (head == NULL) {
        cout << "The list is empty." << endl;
        return;
    }

    Node* temp = head;
    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);
    cout << endl;
}

// Free the allocated memory
void deleteList(Node** head_ref) {
    if (*head_ref == NULL) {
        return;
    }

    Node* current = *head_ref;
    Node* next_node = NULL;

    do {
        next_node = current->next;
        delete current;
        current = next_node;
    } while (current != *head_ref);

    *head_ref = NULL;
}

int main() {
    Node* head = NULL;
    int choice = 1;

    while (choice != 0) {
        int data;
        cout << "Enter data: ";
        cin >> data;

        insertAtEnd(&head, data);

        cout << "Do you want to continue adding nodes (0/1)? ";
        cin >> choice;
    }

    deleteFromBeginning(&head);

    cout << "Doubly Circular Linked List after deletion from the beginning: ";
    printList(head);
    
    // Free the dynamically allocated memory
    deleteList(&head);

    return 0;
}
