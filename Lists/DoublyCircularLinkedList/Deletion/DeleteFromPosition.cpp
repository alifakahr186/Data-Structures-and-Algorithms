#include <iostream>

using namespace std;

struct node
{
    int data;
    struct node *next;
    struct node *prev;
    
};

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

void deletefromposition(struct node **head_ref, int pos){
    struct node *temp = *head_ref;
    struct node *tail = *head_ref;

    int l = getlength(*head_ref);

    if(pos < 1 || pos > l)
    {
        cout << "Invalid position: " << endl;
        return;

    }

    else if (*head_ref == NULL)
    {
        cout << "List is empty: " << endl;
        return;
    }

    else
    {
        for (int i = 0; i < pos; i++)
        {
            temp = temp->next;
        
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

        if (temp->next == *head_ref)
        {
            tail = temp->prev;
            delete temp;

        }

        else
        {
            delete temp;
        }
               
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

    int position;
    cout << "Enter position to delete node: ";
    cin >> position;
    deletefromposition(&head, position);

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

