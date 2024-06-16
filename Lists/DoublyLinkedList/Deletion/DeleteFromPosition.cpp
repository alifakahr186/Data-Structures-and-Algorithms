#include <iostream>

using namespace std;

struct node
{
    int data;
    struct node *next;
    struct node *prev;
    
};

void deletefromposition(struct node **head_ref, int position){

    struct node *temp = *head_ref;

    if(*head_ref == NULL){
        cout << "List is empty: " << endl;
        return;
    }

    for (int i = 0; temp != NULL && i < position; i++)
    {
        temp = temp->next;
        i++;
    }

    if(temp == NULL){
        cout << "Invalid position: " << endl;
        return;

    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
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

    int position;
    cout << "Enter position to delete node: ";
    cin >> position;
    deletefromposition(&head, position);


    temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    
    return 0;
}
