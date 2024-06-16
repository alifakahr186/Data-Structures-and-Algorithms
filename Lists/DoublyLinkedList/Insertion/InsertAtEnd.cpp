#include <iostream>

using namespace std;

struct node
{
    int data;
    struct node *next;
    struct node *prev;
};


void insertatend(struct node **head_ref, int new_data){

    struct node *new_node = new node;
    struct node *tail = *head_ref;

    new_node->data = new_data;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (*head_ref == NULL)
    {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }

    while (tail->next != NULL)
    {
        tail = tail->next;
    }

    tail->next = new_node;
    new_node->prev = tail;

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

    int new_data;
    cout << "Enter data to insert at the end: ";
    cin >> new_data;
    insertatend(&head, new_data);

    temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    
    return 0;
}
