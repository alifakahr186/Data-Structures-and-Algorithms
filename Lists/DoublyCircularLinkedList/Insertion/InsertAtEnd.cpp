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
    struct node *tail;

    new_node->data = new_data;
    
    if (*head_ref == NULL)
    {
        *head_ref = tail = new_node;
        new_node->prev = tail;
        new_node->next = *head_ref;

    }

    else
    {
        struct node *tail = (*head_ref)->prev;
        new_node->next = *head_ref;
        (*head_ref)->prev = new_node;
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
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

    int new_data;
    cout << "Enter data to insert at the End: " << " ";
    cin >> new_data;
    insertatend(&head, new_data);


    temp = head;
    do {
        cout << temp->data << " ";
        temp = temp->next;
        /*To check is over circular linked list correct
        tail->next->data;
        head->prev->data;
        */
    } while (temp != head);

    return 0;
}

