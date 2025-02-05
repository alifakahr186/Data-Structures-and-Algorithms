#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

int getLength(Node* head) {
    if (head == NULL) return 0;
    
    int length = 1; 
    Node* temp = head->next;

    while (temp != head) {
        length++;
        temp = temp->next;
    }

    return length;
}

void insertAtPosition(Node** head_ref, int new_data, int pos) {
    Node* new_node = new Node;
    new_node->data = new_data;
    new_node->next = nullptr;
    new_node->prev = nullptr;

    int length = getLength(*head_ref);

    if (pos < 1 || pos > length + 1) {
        cout << "Invalid position!" << endl;
        return;
    }

    if (pos == 1) {
        if (*head_ref == nullptr) {
            *head_ref = new_node;
            new_node->next = new_node;
            new_node->prev = new_node;
        } else {
            Node* tail = (*head_ref)->prev;
            new_node->next = *head_ref;
            new_node->prev = tail;
            tail->next = new_node;
            (*head_ref)->prev = new_node;
            *head_ref = new_node;  
        }
    }

    else if (pos == length + 1) {
        Node* tail = (*head_ref)->prev;
        new_node->next = *head_ref;
        new_node->prev = tail;
        tail->next = new_node;
        (*head_ref)->prev = new_node;
    }

    else {
        Node* temp = *head_ref;
        for (int i = 1; i < pos - 1; i++) {
            temp = temp->next;
        }

        new_node->next = temp->next;
        new_node->prev = temp;
        temp->next->prev = new_node;
        temp->next = new_node;
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

        insertAtPosition(&head, data, (head == NULL) ? 1 : 2);

        cout << "Do you want to continue adding nodes (0/1)? ";
        cin >> choice;
    }

    cout << "Circular Linked List: ";
    printList(head);
    
    int new_data, position;
    cout << "Enter position to insert a new node: ";
    cin >> position;
    cout << "Enter data to insert at position " << position << ": ";
    cin >> new_data;
    insertAtPosition(&head, new_data, position);

    cout << "Circular Doubly Linked List after insertion: ";
    printList(head);

    // Free the dynamically allocated memory
    deleteList(&head);

    return 0;
}
