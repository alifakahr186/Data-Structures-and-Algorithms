#include <iostream>

using namespace std;

struct node
{
    int data;
    struct node *next;
    struct node *prev;
    
};

void deletefrombeginning(struct node **head_ref){
    struct node *temp = *head_ref;
    struct node *tail = *head_ref;

 
    if(*head_ref == NULL)
    {
        cout << "Linked list is empty: " << endl;
        return;
    }
    
    else if ((*head_ref)->next == *head_ref)
    {
        *head_ref = tail = NULL;
        delete temp;
    }
    
    else
    {
        *head_ref = (*head_ref)->next;
        (*head_ref)->prev = tail;
        tail->next = *head_ref;
        delete temp;
    }

}


int main()
{
    struct node *head = NULL, *newnode, *tail, *temp;
    int choice = 1;

    while (choice != 0)
    {
        newnode = new node;
        cout << "Enter data: ";
        cin >> newnode->data;
        newnode->next = NULL;
        newnode->prev = NULL;

        if (head == NULL)
        {
            head = tail = newnode;
            head->next = head;
            head->prev = head;

        }
        else
        {
            tail->next = newnode;
            newnode->prev = tail;
            newnode->next = head;
            head->prev = newnode;
            tail = newnode;
                 
        }

        cout << "Do you want to continue (0/1)? ";
        cin >> choice;
    }

    deletefrombeginning(&head);

    temp = head;
    do {
        cout << temp->data << " ";
        temp = temp->next;
        /*To check is over circular linked list correct
        tail->next->data;
        head->prev->data;
        */
    } while (temp != tail->next);

    return 0;
}

