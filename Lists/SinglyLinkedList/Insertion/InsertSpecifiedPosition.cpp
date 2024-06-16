#include <iostream>

using namespace std;

struct node
{
    int data;
    struct node *next;
};


// Function to insert a new node at a specified position in the linked list
void insertatposition(struct node **head_ref, int new_data, int position)
{
    // Allocate memory for new node
    struct node *new_node = new node;

    // Assign data to new node
    new_node->data = new_data;

    // If the linked list is empty, insert the new node at the beginning
    if (*head_ref == NULL || position == 0)
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
        return;
    }

    // Traverse the linked list to find the position
    struct node *temp = *head_ref;
    for (int i = 0; temp != NULL && i < position - 1; i++)
    {
        temp = temp->next;
    }
    
    new_node->next = temp->next;
    temp->next = new_node;

    // If the position is invalid, do not insert the new node
    if (temp == NULL)
    {
        cout << "Invalid position" << endl;
        return;
    }
    // Insert the new node at the specified position
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

    int new_data;
    int position;
    cout << "Enter position to insert a new node: ";
    cin >> position;
    cout << "Enter data to insert: " << position << ": ";
    cin >> new_data;
    insertatposition(&head, new_data, position);

    // Print the linked list
    temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }

    return 0;
}
