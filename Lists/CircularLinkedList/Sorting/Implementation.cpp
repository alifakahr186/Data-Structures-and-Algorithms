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
    new_node->next = nullptr;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        new_node->next = *head_ref; 
    } else {
        Node* tail = *head_ref;
        
        while (tail->next != *head_ref) {
            tail = tail->next;
        }

        tail->next = new_node;
        new_node->next = *head_ref;  
    }
}

void swapNodes(Node** head_ref, Node* node1, Node* node2) {
    if (node1 == node2) return;

    Node* prev1 = node1->prev;
    Node* next1 = node1->next;
    Node* prev2 = node2->prev;
    Node* next2 = node2->next;

    if (next1 == node2) {  
        next1 = node2->next;
        if (next2 != nullptr) next2->prev = node1;
        
        prev2 = node1->prev;
        if (prev1 != nullptr) prev1->next = node2;
        
        prev2 = node1;
        prev1 = node2;
    } else {
        if (prev1 != nullptr) prev1->next = node2;
        if (next1 != nullptr) next1->prev = node2;

        if (prev2 != nullptr) prev2->next = node1;
        if (next2 != nullptr) next2->prev = node1;

        node2->next = next1;
        node2->prev = prev1;
        node1->next = next2;
        node1->prev = prev2;
    }

    if (*head_ref == node1) {
        *head_ref = node2;
    } else if (*head_ref == node2) {
        *head_ref = node1;
    }
}

void sortList(Node** head_ref) {
    if (*head_ref == nullptr || (*head_ref)->next == *head_ref) return;

    bool swapped;
    do {
        swapped = false;
        Node* current = *head_ref;
        
        do {
            Node* next_node = current->next;
            if (current->data > next_node->data) {
                swapNodes(head_ref, current, next_node);
                swapped = true;
            }
            current = current->next;
        } while (current != *head_ref && current->next != *head_ref);
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
    Node* head = nullptr;
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

    deleteList(&head);

    return 0;
}
