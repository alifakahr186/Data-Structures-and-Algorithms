#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

void insertAtEnd(Node** head_ref, int new_data) {
    Node* new_node = new Node;
    new_node->data = new_data;
    new_node->next = nullptr;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        new_node->next = *head_ref; 
    } else {
        Node* tail = *head_ref;
        
        while (tail->next != *head_ref) {
            tail = tail->next;
        }

        tail->next = new_node;
        new_node->next = *head_ref; 
    }
}

void deleteFromEnd(Node** head_ref) {
    if (*head_ref == nullptr) {
        cout << "List is empty." << endl;
        return;
    }

    Node* temp = *head_ref;
    Node* prev = nullptr;

    if (temp->next == *head_ref) {
        delete temp;
        *head_ref = nullptr;  
        return;
    }

    while (temp->next != *head_ref) {
        prev = temp;
        temp = temp->next;
    }

    prev->next = *head_ref; 
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

    deleteFromEnd(&head);
    
    cout << "Doubly Circular Linked List after deletion from the beginning: ";
    printList(head);
    
    // Free the dynamically allocated memory
    deleteList(&head);

    return 0;
}
