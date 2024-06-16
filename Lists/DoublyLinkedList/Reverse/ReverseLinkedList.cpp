#include <iostream>

using namespace std;

struct node
{
    int data;
    struct node *next;
    struct node *prev;
    
};

void reverselist(struct node **head_ref)
{
    struct node *current = *head_ref;
    struct node *temp = NULL;

    while (current != NULL)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if (temp != NULL)
    {
        *head_ref = temp->prev;
    }
}

int main()
{
    struct node *head = NULL, *newnode, *temp;
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
            head = temp = newnode;
        }
        else
        {
            temp->next = newnode;
            newnode->prev = temp;
            temp = newnode;      
        }

        cout << "Do you want to continue (0/1)? ";
        cin >> choice;
    }

    cout << "Original List: ";
    temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }

    reverselist(&head);

    cout << "\nReversed List: ";
    temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    
    return 0;
}
