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

void printList(struct Node *node) {
    while (node != NULL) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

int getLength(Node *head) {
    int length = 0;
    Node *temp = head;

    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    return length;
}

// Free the allocated memory
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

    cout << "Linked list after insertions at the end: ";
    printList(head);

    int length = getLength(head);
    cout << "Length of the linked list: " << length << endl;

    // Free the dynamically allocated memory
    deleteList(head);

    return 0;
}
