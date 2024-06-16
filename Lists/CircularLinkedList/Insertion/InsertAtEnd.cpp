#include <iostream>
using namespace std;

struct node {
    int data;
    struct node* next;
};

void insertatend(struct node **head_ref, int new_data){
    
    struct node *new_node = new node;
    struct node *tail = *head_ref;

    new_node->data = new_data;    
    new_node->next = NULL;

    if(tail == NULL){
        tail = new_node;
        tail->next = new_node;
        *head_ref = new_node;

    }

    else
    {
        new_node->next = tail->next;
        tail->next = new_node;
        tail = new_node;
        *head_ref = tail->next;
    }

    /*
    To check is over circular linked list correct
    tail->next->data;
    */
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

    int new_data;
    cout << "Enter data to insert at the End: ";
    cin >> new_data;
    insertatend(&head, new_data);
    
    temp = head;

    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);

    return 0;
}
