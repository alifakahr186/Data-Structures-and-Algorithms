#include <iostream>
using namespace std;

struct node {
    int data;
    struct node* next;
};

int getlength(struct node *head)
{
    int len = 0;
    if (head != NULL)
    {
        struct node* temp = head;
        do {
            temp = temp->next;
            len++;
        } while (temp != head);
    }
    return len;
}

void deletefromposition(struct node **head_ref, int pos){
    struct node *current = *head_ref;
    struct node *nextnode = *head_ref;
    struct node *tail = *head_ref;

    int l = getlength(*head_ref);
    
    if (pos < 1 || pos > l)
    {
        cout << "Invalid position: ";
        return;
    }

    else
    {
        for (int i = 0; i < pos - 1; i++)
        {
            current = current->next;
        }

        nextnode = current->next;
        current->next = nextnode->next;
        delete nextnode;
    }
    

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

    int position;
    cout << "Enter position to delete node: ";
    cin >> position;
    deletefromposition(&head, position);

    temp = head;

    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);

    return 0;
}
