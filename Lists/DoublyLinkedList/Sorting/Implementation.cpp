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

void printList(Node* head) {
    if (head == NULL) {
        cout << "The list is empty." << endl;
        return;
    }
    Node* temp = head;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void sortList(Node** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return; // List is empty or has only one element
    }

    bool swapped;
    Node* current;

    do {
        swapped = false;
        current = *head;

        while (current->next) {
            if (current->data > current->next->data) {
                int temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                
                swapped = true;
            }
            current = current->next;
        }
        
    } while (swapped);
}

// Free the allocated memory
void deleteList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* head = NULL;
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

    // Sort the doubly linked list
    sortList(&head);

    cout << "Sorted list: ";
    printList(head);

    // Free the dynamically allocated memory
    deleteList(head);
    
    return 0;
}
