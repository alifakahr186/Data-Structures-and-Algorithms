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


void deleteFromEnd(Node **head_ref) {
    if (*head_ref == NULL) {
        cout << "Linked list is empty, nothing to delete." << endl;
        return;
    }

    if ((*head_ref)->next == NULL) {
        delete *head_ref;
        *head_ref = NULL;
        return;
    }

    // find the second last node
    Node *second_last = *head_ref;
    while (second_last->next != NULL && second_last->next->next != NULL) {
        second_last = second_last->next;
    }

    Node *last = second_last->next;
    second_last->next = NULL;
    delete last;
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

    deleteFromEnd(&head);

    cout << "Linked list after deleting the last node: ";
    printList(head);

    // Free the dynamically allocated memory
    deleteList(head);

    return 0;
}
