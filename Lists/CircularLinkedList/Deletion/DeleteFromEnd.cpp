#include <iostream>
using namespace std;

struct node {
    int data;
    struct node* next;
};

void deletefromend(struct node **head_ref){
    struct node *current = *head_ref;
    struct node *previous = NULL;
    struct node *tail = *head_ref;


    if(*head_ref == 0){
        cout << "List is empty: " << endl;
        return;
    }

    while (current->next != tail)
    {
            previous = current;
            current = current->next;

    }
    
    if (current == tail)
    {
        *head_ref = NULL;
        delete current;
    }

    else
    {

        previous->next = tail->next;
        *head_ref = previous->next;
        delete current;
        
    }

    tail = previous;
        
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

    deletefromend(&head);

    temp = head;

    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);

    return 0;
}
