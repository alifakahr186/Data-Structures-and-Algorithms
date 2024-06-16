#include <iostream>

using namespace std;

struct node
{
    int data;
    struct node *next;
    struct node *prev;
    
};

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

