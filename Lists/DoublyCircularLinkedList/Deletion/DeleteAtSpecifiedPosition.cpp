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

int getListLength(Node* head) {
    if (head == NULL) return 0;

    int length = 0;
    Node* temp = head;
    do {
        length++;
        temp = temp->next;
    } while (temp != head);

    return length;
}

void deleteFromPosition(Node** head_ref, int pos) {
    if (*head_ref == NULL) {
        cout << "The list is empty." << endl;
        return;
    }

    int length = getListLength(*head_ref);
    if (pos < 1 || pos > length) {
        cout << "Invalid position." << endl;
        return;
    }

    Node* temp = *head_ref;

    // If the position is 1, delete the head node
    if (pos == 1) {
        if (temp->next == *head_ref) { // Only one node in the list
            delete temp;
            *head_ref = NULL;
        } else { // More than one node
            Node* tail = temp->prev;
            *head_ref = temp->next;
            (*head_ref)->prev = tail;
            tail->next = *head_ref;
            delete temp;
        }
    } else {
        // Move to the node to delete
        for (int i = 1; i < pos; i++) {
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
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
    if (*head_ref == NULL) return;

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
    
    cout << "Doubly Circular Linked List: ";
    printList(head);

    int position;
    cout << "Enter position to delete node: ";
    cin >> position;
    deleteFromPosition(&head, position);

    cout << "Doubly Circular Linked List after deletion from the specified position: ";
    printList(head);

    // Free the dynamically allocated memory
    deleteList(&head);

    return 0;
}
