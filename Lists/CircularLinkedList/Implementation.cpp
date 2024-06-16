#include <iostream>
using namespace std;

struct node {
    int data;
    struct node* next;
};

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

    temp = head;

    do {
        cout << temp->data << " ";
        temp = temp->next;
        /*
        To check is over circular linked list correct
        cout << tail->next->data << " ";
        temp = temp->next;
        */
    } while (temp != head);

    return 0;
}
