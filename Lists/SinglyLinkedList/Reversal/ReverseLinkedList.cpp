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

void reverseList(Node **head) {
    Node *prev = NULL;
    Node *curr = *head;
    Node *next = NULL;
    
    while (curr != NULL) {
        next = curr->next;  
        curr->next = prev;  
        prev = curr;        
        curr = next;
    }
    
    *head = prev; 
}

void printList(Node *head) {
    if (head == NULL) {
        cout << "The list is empty." << endl;
        return;
    }
    Node *temp = head;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
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

    cout << "Original list: ";
    printList(head);

    reverseList(&head);

    cout << "Reversed list: ";
    printList(head);

    // Free the dynamically allocated memory
    deleteList(head);
    
    return 0;
}
