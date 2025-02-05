#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* next;
};

// Function to insert a new node at a specified position in the linked list
void insertAtPosition(Node **head_ref, int new_data, int position)
{
    Node* new_node = new Node;
    new_node->data = new_data;

    if (*head_ref == NULL || position == 0)
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
        return;
    }

    Node* temp = *head_ref;
    for (int i = 0; temp != NULL && i < position - 1; i++){
        temp = temp->next;
    }
    
    new_node->next = temp->next;
    temp->next = new_node;

    if (temp == NULL) { 
        cout << "Invalid position" << endl;
        delete new_node;
        return;
    }

}

void printList(Node* node) {
    while (node != NULL) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

// Free the allocated memory
void deleteList(Node** head_ref) {
    Node* temp;
    while (*head_ref != NULL) {
        temp = *head_ref;
        *head_ref = (*head_ref)->next;
        delete temp;
    }
    *head_ref = NULL;
}

int main()
{
    Node* head = NULL;
    Node* newnode, *temp;
    int choice = 1;

    while (choice != 0)
    {
        newnode = new Node;
        cout << "Enter data: ";
        cin >> newnode->data;
        newnode->next = NULL;

        if (head == NULL){
            head = temp = newnode;
        } else{
            temp->next = newnode;
            temp = newnode;
        }

        cout << "Do you want to continue (0/1)? ";
        cin >> choice;
    }

    cout << "Singly Linked list before insertion: ";
    printList(head);

    int new_data, position;
    cout << "Enter position to insert a new node: ";
    cin >> position;
    cout << "Enter data to insert: " << position << ": ";
    cin >> new_data;
    insertAtPosition(&head, new_data, position);

    cout << "Singly Linked list after insertion: ";
    printList(head);

    // Free the dynamically allocated memory
    deleteList(&head);

    return 0;
}