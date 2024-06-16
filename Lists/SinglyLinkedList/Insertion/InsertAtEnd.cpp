#include <iostream>

using namespace std;

struct node
{
    int data;
    struct node *next;
};

// Function to insert a new node at the end of the linked list
void insertatend(struct node **head_ref, int new_data)
{
    // Allocate memory for new node
    struct node *new_node = new node;

    // Assign data to the new node and set its next pointer to NULL
    new_node->data = new_data;
    new_node->next = NULL;

    // If the linked list is empty, make the new node the head of the list


    // Traverse the linked list to reach the last node
    struct node *temp = *head_ref;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    // Set the next pointer of the last node to point to the new node
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

    // Insert a new node at the end
    int new_data;
    cout << "Enter data to insert at the end: ";
    cin >> new_data;
    insertatend(&head, new_data);

    temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }

    return 0;
}
