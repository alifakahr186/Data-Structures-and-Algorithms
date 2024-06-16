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
     if(*head_ref == NULL)
     {
        cout << "Linked list is empty: " << endl;
        return;
     }

    if (*head_ref != NULL)
    {
        
        (*head_ref)->prev = NULL;
        *head_ref = (*head_ref)->next;

    }

    delete temp;

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


    deletefrombeginning(&head);


    temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    
    return 0;
}
