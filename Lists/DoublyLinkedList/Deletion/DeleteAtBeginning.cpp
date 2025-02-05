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

void deleteFromBeginning(Node** head_ref) {
    if (*head_ref == NULL) {
        cout << "Linked list is empty." << endl;
        return;
    }

    Node* temp = *head_ref;  

    *head_ref = (*head_ref)->next;

    if (*head_ref != NULL) {
        (*head_ref)->prev = NULL;
    }

    delete temp;  
    cout << "Node deleted from the beginning." << endl;
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
    struct Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;  // Deallocate memory
    }
}

int main() {
    Node* head = NULL;
    Node* newnode, *temp;
    int choice = 1;

    while (choice != 0) {
        newnode = new Node;
        int new_data;    
        cout << "Enter data: ";
        cin >> newnode->data;
        newnode->next = NULL;
        newnode->prev = NULL;

        if (head == NULL) {
            head = temp = newnode;
        } else {
            temp->next = newnode;
            newnode->prev = temp;
            temp = newnode;      
        }

        insertAtEnd(&head, new_data);

        cout << "Do you want to continue (0/1)? ";
        cin >> choice;
    }

    cout << "Linked list before deletion: ";
    printList(head);

    deleteFromBeginning(&head);

    cout << "Linked list after deletion: ";
    printList(head);

    // Free the dynamically allocated memory
    deleteList(head);

    return 0;
}
