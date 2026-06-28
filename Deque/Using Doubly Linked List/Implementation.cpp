#include <iostream>
#include <limits>
using namespace std;

struct Node
{
    int data;
    Node* next;
    Node* prev;
};

Node* front = NULL;
Node* rear = NULL;


bool isEmpty()
{
    return (front == NULL);
}

void enqueueFront(int x)
{
    Node* new_node = new Node;

    new_node->data = x;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (isEmpty())
    {
        front = rear = new_node;
    }
    else
    {
        new_node->next = front;
        front->prev = new_node;
        front = new_node;
    }

    cout << x << " inserted at Front." << endl;
}

void enqueueRear(int x)
{
    Node* new_node = new Node;

    new_node->data = x;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (isEmpty())
    {
        front = rear = new_node;
    }
    else
    {
        rear->next = new_node;
        new_node->prev = rear;
        rear = new_node;
    }

    cout << x << " inserted at Rear." << endl;
}

void dequeueFront()
{
    if (isEmpty())
    {
        cout << "Deque is Empty." << endl;
        return;
    }

    Node* temp = front;

    cout << "Removed Element: " << temp->data << endl;

    if (front == rear)
    {
        front = rear = NULL;
    }
    else
    {
        front = front->next;
        front->prev = NULL;
    }

    delete temp;
}

void dequeueRear()
{
    if (isEmpty())
    {
        cout << "Deque is Empty." << endl;
        return;
    }

    Node* temp = rear;

    cout << "Removed Element: " << temp->data << endl;

    if (front == rear)
    {
        front = rear = NULL;
    }
    else
    {
        rear = rear->prev;
        rear->next = NULL;
    }

    delete temp;
}

void getFront()
{
    if (isEmpty())
    {
        cout << "Deque is Empty." << endl;
    }
    else
    {
        cout << "Front Element: " << front->data << endl;
    }
}

void getRear()
{
    if (isEmpty())
    {
        cout << "Deque is Empty." << endl;
    }
    else
    {
        cout << "Rear Element: " << rear->data << endl;
    }
}

void display()
{
    if (isEmpty())
    {
        cout << "Deque is Empty." << endl;
        return;
    }

    Node* temp = front;

    cout << "Deque Elements: ";

    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << endl;
}

int getValidIntInput(string prompt)
{
    int value;

    while (true)
    {
        cout << prompt;
        cin >> value;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input. Please enter an integer.\n";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

int main()
{
    int option;
    int value;

    do
    {
        cout << "\n========== DEQUE USING DOUBLY LINKED LIST ==========\n";
        cout << "1. Enqueue Front\n";
        cout << "2. Enqueue Rear\n";
        cout << "3. Dequeue Front\n";
        cout << "4. Dequeue Rear\n";
        cout << "5. Display\n";
        cout << "6. Get Front\n";
        cout << "7. Get Rear\n";
        cout << "0. Exit\n";

        option = getValidIntInput("Enter Option: ");

        switch (option)
        {
        case 1:
            value = getValidIntInput("Enter Value: ");
            enqueueFront(value);
            break;

        case 2:
            value = getValidIntInput("Enter Value: ");
            enqueueRear(value);
            break;

        case 3:
            dequeueFront();
            break;

        case 4:
            dequeueRear();
            break;

        case 5:
            display();
            break;

        case 6:
            getFront();
            break;

        case 7:
            getRear();
            break;

        case 0:
            cout << "Program Ended." << endl;
            break;

        default:
            cout << "Invalid Option." << endl;
        }

    } while (option != 0);

    while (!isEmpty())
    {
        dequeueFront();
    }

    return 0;
}