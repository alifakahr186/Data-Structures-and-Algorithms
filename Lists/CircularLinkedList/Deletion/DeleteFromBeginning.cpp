#include <iostream>
using namespace std;

struct node {
    int data;
    struct node* next;
};

void deletefrombeginning(struct node **head_ref){
    
    struct node *tail = *head_ref;
    struct node *temp = tail->next;
    
    if (*head_ref == NULL) {
        cout << "List is empty: " << endl;
        return;
    }
    
    if (temp == *head_ref) { // list has only one node
        *head_ref = NULL;
    } else {
        tail->next = temp->next; // set tail to point to new head
        *head_ref = tail->next; // update head_ref to point to new head
    }
    
    delete temp; // delete original head

}



int main() {
    struct node *head = NULL, *newnode, *temp;
    int choice = 1;

    while (choice) {
        newnode = new node;
        cout << "Enter data: ";
        cin >> newnode->data;
        newnode->next = NULL;
        
        if (head == NULL) {
            head = temp = newnode;
        
        } 
        
        else {
            temp->next = newnode;
            temp = newnode;
        
        }

        temp->next = head;

        cout << "Do you want to continue(1/0)? ";
        cin >> choice;
    }

    deletefrombeginning(&head);

    temp = head;

    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);

    return 0;
}
