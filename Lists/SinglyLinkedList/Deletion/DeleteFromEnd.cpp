#include <iostream>

using namespace std;

struct node
{
    int data;
    struct node *next;
};

void deletefromend(struct node **head_ref)
{
    if (*head_ref == NULL)
    {
        cout << "Linked list is empty" << endl;
        return;
    }

    if ((*head_ref)->next == NULL)
    {
        // If there is only one node in the list, delete it and set head to NULL
        delete *head_ref;
        *head_ref = NULL;
        return;
    }

    // Find the second last node of the linked list
    struct node *second_last = *head_ref;
    while (second_last->next->next != NULL)
    {
        second_last = second_last->next;
    }

    // Store the last node in a temporary variable
    struct node *last = second_last->next;

    // Set the next pointer of the second last node to NULL
    second_last->next = NULL;

    // Free the memory of the last node
    delete last;
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

        if (head == NULL)
        {
            head = temp = newnode;
        }
        else
        {
            temp->next = newnode;
            temp = newnode;
     
        }
         
        cout << "Do you want to continue (0/1)? ";
        cin >> choice;
    }

    deletefromend(&head);

    temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }

    return 0;
}
