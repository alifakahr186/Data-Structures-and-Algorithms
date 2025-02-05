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

void deleteFromPosition(Node** head_ref, int position) {
    if (*head_ref == NULL) {
        cout << "List is empty." << endl;
        return;
    }

    Node* temp = *head_ref;

    // Traverse to the specified position
    for (int i = 0; temp != NULL && i < position; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Invalid position." << endl;
        return;
    }

    // Update pointers and delete node
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        // If deleting the head node
        *head_ref = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    delete temp;
    cout << "Node at position " << position << " deleted." << endl;
}

void printList(struct Node *node) {
    if (node == NULL) {
        cout << "Linked list is empty." << endl;
        return;
    }
    while (node != NULL) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

// Function to free the allocated memory
void deleteList(struct Node *head) {
    struct Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    struct Node *head = NULL;
    int choice = 1;

    while (choice != 0) {
        int new_data;
        cout << "Enter data: ";
        cin >> new_data;

        insertAtEnd(&head, new_data);

        cout << "Do you want to continue (0/1)? ";
        cin >> choice;
    }

    cout << "Linked list before deletion: ";
    printList(head);

    int position;
    cout << "Enter position to delete node: ";
    cin >> position;
    deleteFromPosition(&head, position);

    cout << "Linked list after deletion: ";
    printList(head);

    // Free the dynamically allocated memory
    deleteList(head);

    return 0;
}
