#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;
};

void insertAtEnd(Node **head_ref, int new_data) {
    Node *new_node = new Node;

    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
    } else {
        Node *temp = *head_ref;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void deleteFromPos(Node **head_ref, int position) {
    if (*head_ref == NULL) {
        cout << "Linked List is empty." << endl;
        return;
    }

    Node *temp = *head_ref;

    if (position == 0) {
        *head_ref = temp->next;
        delete temp;
        return;
    }

    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        cout << "Invalid position." << endl;
        return;
    }

    Node *nextnode = temp->next->next;

    delete temp->next;
    temp->next = nextnode;
}

void printList(Node *node) {
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

// Free the allocated memory
void deleteList(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;  // Deallocate memory
    }
}

int main() {
    Node *head = NULL;
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
    deleteFromPos(&head, position);

    cout << "Linked list after deletion: ";
    printList(head);

    // Free the dynamically allocated memory
    deleteList(head);

    return 0;
}
