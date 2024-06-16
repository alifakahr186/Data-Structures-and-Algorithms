#include <iostream>

using namespace std;

struct node
{
    int data;
    struct node *next;
};

void deletefrompos(struct node **head_ref, int position)
{
    struct node * nextnode;
    struct node *temp = *head_ref;

    if(*head_ref == NULL){
        cout << "List is empty: " << endl;
        return;
    }

    for (int i = 0; temp != NULL && i< position - 1; i++)
    {
        temp = temp->next;
        i++;
    }

    if(temp == NULL){
        cout << "Invlaid position: " << endl;
        return;
    }

    nextnode = temp->next;
    temp->next = nextnode->next;
    delete(nextnode);
    
    

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

    int position;
    cout << "Enter position to delete node: ";
    cin >> position;
    deletefrompos(&head, position);

    temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }

    return 0;
}
