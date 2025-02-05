#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void insertAtPosition(Node** head_ref, int new_data, int pos) {
    Node* new_node = new Node;
    new_node->data = new_data;

    if (pos < 1) {
        cout << "Invalid position." << endl;
        delete new_node;
        return;
    }

    if (*head_ref == NULL) {
        if (pos == 1) {
            new_node->next = new_node;
            new_node->prev = new_node;
            *head_ref = new_node;
        } else {
            cout << "Position out of range for empty list." << endl;
            delete new_node;
        }
        return;
    }

    Node* temp = *head_ref;
    int count = 1;

    // Traverse to the node just before the desired position
    while (count < pos - 1 && temp->next != *head_ref) {
        temp = temp->next;
        count++;
    }

    if (count != pos - 1) {
        cout << "Position out of range." << endl;
        delete new_node;
        return;
    }

    new_node->next = temp->next;
    new_node->prev = temp;
    temp->next->prev = new_node;
    temp->next = new_node;

    if (pos == 1) {
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

    // Insert nodes at the end to build the list initially
    while (choice != 0) {
        int data;
        cout << "Enter data: ";
        cin >> data;

        insertAtPosition(&head, data, (head == NULL) ? 1 : 2);

        cout << "Do you want to continue adding nodes (0/1)? ";
        cin >> choice;
    }

    cout << "Doubly Circular Linked List: ";
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
