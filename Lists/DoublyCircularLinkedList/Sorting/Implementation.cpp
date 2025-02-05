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

    if (*head_ref == NULL) {
        *head_ref = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
    } else {
        Node* tail = (*head_ref)->prev; 

        new_node->next = *head_ref;       
        new_node->prev = tail;            
        tail->next = new_node;            
        (*head_ref)->prev = new_node;    
    }
}

void swapNodes(Node** head_ref, Node* node1, Node* node2) {
    if (node1 == node2) return;

    Node* prev1 = node1->prev;
    Node* next1 = node1->next;
    Node* prev2 = node2->prev;
    Node* next2 = node2->next;

    // Swap the prev and next pointers of node1 and node2
    if (next1 == node2) {  // If nodes are adjacent
        node1->prev = node2;
        node1->next = next2;
        node2->prev = prev1;
        node2->next = node1;

        if (next2 != NULL) next2->prev = node1;
        if (prev1 != NULL) prev1->next = node2;
    } else {
        // Swap the connections between node1 and node2
        if (prev1 != NULL) prev1->next = node2;
        if (next1 != NULL) next1->prev = node2;

        if (prev2 != NULL) prev2->next = node1;
        if (next2 != NULL) next2->prev = node1;

        node2->next = next1;
        node2->prev = prev1;
        node1->next = next2;
        node1->prev = prev2;
    }

    // Adjust head if needed
    if (*head_ref == node1) {
        *head_ref = node2;
    } else if (*head_ref == node2) {
        *head_ref = node1;
    }
}

void sortList(Node** head_ref) {
    if (*head_ref == NULL) return;

    Node* temp;
    bool swapped;
    do {
        swapped = false;
        temp = *head_ref;

        do {
            Node* node1 = temp;
            Node* node2 = temp->next;

            if (node1->data > node2->data) {
                swapNodes(head_ref, node1, node2); 
                swapped = true;
            }
            temp = temp->next;
        } while (temp != *head_ref);
    } while (swapped);
}

void printList(Node* head) {
    if (head == NULL) {
        cout << "The list is empty." << endl;
        return;
    }

    Node* temp = head;
    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);
    cout << endl;
}

// Free the allocated memory
void deleteList(Node** head_ref) {
    if (*head_ref == NULL) {
        return;
    }

    Node* current = *head_ref;
    Node* next_node = NULL;

    do {
        next_node = current->next;
        delete current;
        current = next_node;
    } while (current != *head_ref);

    *head_ref = NULL;  
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

    sortList(&head);

    cout << "Sorted list: ";
    printList(head);

    // Free the dynamically allocated memory
    deleteList(&head);

    return 0;
}
