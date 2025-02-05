#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
};

void insertAtBeginning(Node **head_ref, int new_data) {
    Node *new_node = new Node;

    new_node->data = new_data;
    new_node->next = *head_ref;

    *head_ref = new_node;
}

void printList(struct Node *node) {
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
        delete temp;
    }
}

int main() {
    Node *head = NULL;  
    int choice = 1;

    while (choice != 0) {
        int new_data;
        cout << "Enter data: ";
        cin >> new_data;

        insertAtBeginning(&head, new_data);

        cout << "Do you want to continue adding nodes (0/1)? ";
        cin >> choice;
    }

    cout << "Linked list after insertions at the beginning: ";
    printList(head);

    // Free the dynamically allocated memory
    deleteList(head);

    return 0;
}
