#include <iostream>
using namespace std;

struct node {
    int data;
    struct node* next;
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
    struct node *tail = *head_ref;
    struct node *temp = *head_ref;
    
    new_node->data = new_data;
    new_node->next = nullptr;


    int l = getlength(*head_ref);

    if(pos < 0 || pos > l){
        cout << "Invalid position: ";
        return;

    }

    else
    {
        temp = tail->next;
        for (int i = 1; i < pos - 1; i++)
        {
            temp = temp->next;

        }

        new_node->next = temp->next;
        temp->next = new_node;
        
    }
    
    /*
    To check is over circular linked list correct
    tail->next->data;
    */
}

int main() {
    struct node *head = NULL, *newnode, *temp;
    int choice = 1;

    while (choice) {
        newnode = new node;
        cout << "Enter data: ";
        cin >> newnode->data;
        newnode->next = NULL;
        
        if (head == NULL) {
            head = temp = newnode;
        
        } 
        
        else {
            temp->next = newnode;
            temp = newnode;
        
        }

        temp->next = head;

        cout << "Do you want to continue(1/0)? ";
        cin >> choice;
    }

    int new_data;
    int pos;
    cout << "Enter position to insert a new node: ";
    cin >> pos;
    cout << "Enter data to insert: " << pos << ": ";
    cin >> new_data;
    insertatposition(&head, new_data, pos);
 
    temp = head;

    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);

    return 0;
}
