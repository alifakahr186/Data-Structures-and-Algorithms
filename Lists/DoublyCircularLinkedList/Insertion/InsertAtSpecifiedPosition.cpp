#include <iostream>

using namespace std;

struct node
{
    int data;
    struct node *next;
    struct node *prev;
    
};

//To check length of linked list
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

void insertatposition(struct node **head_ref, int new_data, int pos){
    struct node *new_node = new node;
    struct node *temp = *head_ref;

    new_node->data = new_data;
    new_node->prev = NULL;
    new_node->next = NULL;

    int l = getlength(*head_ref);

    if (pos < 1 || pos > l)
    {
        cout << "Invalid position: ";
        return;

    }

    else if (temp == NULL)
    {
        cout << "Invalid position " << endl;
        return;

    }

    else
    {
        for(int i = 0; i < pos - 1; i++)
        {
            temp = temp->next;
            
        }
        
    }

    new_node->prev = temp;
    new_node->next = temp->next;
    temp->next->prev = new_node;
    temp->next = new_node;

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
    int position;
    cout << "Enter position to insert a new node: ";
    cin >> position;
    cout << "Enter data to insert: " << position << ": ";
    cin >> new_data;
    insertatposition(&head, new_data, position);


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

