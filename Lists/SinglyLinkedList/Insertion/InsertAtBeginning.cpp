#include <iostream>

using namespace std;

struct node
{
    int data;
    struct node *next;
};

// Function to insert a new node at the beginning of the linked list
void insertatbeginning(struct node **head_ref, int new_data)
{
    // Allocate memory for new node
    struct node *new_node = new node;

    // Assign data and set next pointer to current head node
    new_node->data = new_data;
    new_node->next = *head_ref;

    // Update head pointer to point to new node
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

    // Insert a new node at the beginning
    int new_data;
    cout << "Enter data to insert at the beginning: ";
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
