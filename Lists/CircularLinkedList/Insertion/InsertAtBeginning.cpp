#include <iostream>
using namespace std;

struct Node {
    int data;
    struct Node* next;
};

void insertAtBeginning(Node** head_ref, int new_data) {
    Node* new_node = new Node;
    new_node->data = new_data;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        new_node->next = new_node; 
    } else {
        Node* tail = *head_ref;
        while (tail->next != *head_ref) {
            tail = tail->next;
        }

        new_node->next = *head_ref;
        tail->next = new_node;  
        *head_ref = new_node;  
    }
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

        insertAtBeginning(&head, data);

        cout << "Do you want to continue adding nodes (0/1)? ";
        cin >> choice;
    }

    cout << "Doubly Circular Linked List after insertions at the beginning: ";
    printList(head);

    deleteList(&head);
    
    return 0;
}
