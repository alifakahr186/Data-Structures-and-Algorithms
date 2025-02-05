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

int getLength(Node* head) {
    int len = 0;
    if (head != nullptr) {
        Node* temp = head;
        do {
            temp = temp->next;
            len++;
        } while (temp != head);
    }
    return len;
}

void deleteFromPosition(Node** head_ref, int pos) {
    if (*head_ref == nullptr) {
        cout << "The list is empty." << endl;
        return;
    }

    int l = getLength(*head_ref);

    if (pos < 1 || pos > l) {
        cout << "Invalid position: " << pos << endl;
        return;
    }

    Node* current = *head_ref;
    Node* nextnode = nullptr;

    if (pos == 1) {
        Node* tail = *head_ref;
        while (tail->next != *head_ref) {
            tail = tail->next;
        }

        if (*head_ref == (*head_ref)->next) {
            delete *head_ref;
            *head_ref = nullptr;
            return;
        }

        tail->next = current->next;
        *head_ref = current->next;
        delete current;
        return;
    }

    for (int i = 1; i < pos - 1; i++) {
        current = current->next;
    }

    nextnode = current->next;
    current->next = nextnode->next; 
    delete nextnode;  
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
    Node* head = nullptr;
    int choice = 1;

    while (choice != 0) {
        int data;
        cout << "Enter data: ";
        cin >> data;

        insertAtEnd(&head, data);

        cout << "Do you want to continue adding nodes (0/1)? ";
        cin >> choice;
    }

    cout << "Circular Linked List: ";
    printList(head);

    int position;
    cout << "Enter the position to delete a node: ";
    cin >> position;

    deleteFromPosition(&head, position);

    cout << "Circular Linked List after deletion at position " << position << ": ";
    printList(head);

    // Free the dynamically allocated memory
    deleteList(&head);

    return 0;
}
