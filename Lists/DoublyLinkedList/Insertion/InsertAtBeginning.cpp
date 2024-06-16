#include <iostream>

using namespace std;

struct node
{
    int data;
    struct node *next;
    struct node *prev;
    
};

void insertatbeginning(struct node **head_ref, int new_data){
    
    struct node *new_node = new node;

    new_node->data = new_data;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (*head_ref != NULL)
    {
        (*head_ref)->prev = new_node;
        new_node->next = *head_ref;

    }
    
    *head_ref = new_node;

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
    cout << "Enter data to insert at the beginning: " << " ";
    cin >> new_data;
    insertatbeginning(&head, new_data);


    temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    
    return 0;
}
