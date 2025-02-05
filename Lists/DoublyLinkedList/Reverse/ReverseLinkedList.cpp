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

void reverselist(Node **head_ref)
{
    Node *current = *head_ref;
    Node *temp = NULL;

    while (current != NULL)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if (temp != NULL)
    {
        *head_ref = temp->prev;
    }
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
void deleteList(struct Node *head) {
    struct Node *temp;
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

        insertAtEnd(&head, new_data);

        cout << "Do you want to continue (0/1)? ";
        cin >> choice;
    }

    cout << "Original list: ";
    printList(head);

    reverselist(&head);

    cout << "Reversed list: ";
    printList(head);

    // Free the dynamically allocated memory
    deleteList(head);
    
    return 0;
}
