#include <iostream>

using namespace std;

struct node
{
    int data;
    struct node *next;
    struct node *prev;
};


void insertatposition(struct node **head_ref, int new_data, int position){

    struct node *new_node = new node;
    struct node *temp = *head_ref;

    new_node->data = new_data;

    if (*head_ref == NULL || position == 0)
    {
        new_node->next = NULL;
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }

    else if (temp == NULL)
    {
        cout << "Invalid position" << endl;
        return;
    }
    
    
    for (int i = 0; temp != NULL && i < position - 1; i++)
    {
        temp = temp->next;
        
    }

    new_node->prev = temp;
    new_node->next = temp->next;
    temp->next = new_node;
    


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
    int position;
    cout << "Enter position to insert a new node: ";
    cin >> position;
    cout << "Enter data to insert: " << position << ": ";
    cin >> new_data;
    insertatposition(&head, new_data, position);

    temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    
    return 0;
}
