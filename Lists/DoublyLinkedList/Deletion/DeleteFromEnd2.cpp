#include <iostream>

using namespace std;

struct node {
    int data;
    struct node* next;
    struct node* prev;
};

struct node* tail = NULL;

void deletefromend() {

    struct node* temp;

    if (tail == NULL) 
    {
        cout << "Invalid position: ";
        return;
    }

    else 
    {
        temp = tail;
        tail->prev->next = NULL;
        tail = tail->prev;
        delete temp;
    }


}

int main() {
    struct node* head = NULL, * newnode, * temp;
    int choice = 1;

    while (choice != 0) {
        newnode = new node;
        cout << "Enter data: ";
        cin >> newnode->data;
        newnode->next = NULL;
        newnode->prev = NULL;

        if (head == NULL) {
            head = tail = newnode;
        }
        else {
            tail->next = newnode;
            newnode->prev = tail;
            tail = newnode;
        }

        cout << "Do you want to continue (0/1)? ";
        cin >> choice;
    }

    deletefromend();

    temp = head;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }

    return 0;
}
