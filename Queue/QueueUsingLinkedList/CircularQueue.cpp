#include <iostream>

struct Node
{
    int data;
    Node* next;
};

Node* front = nullptr;
Node* rear = nullptr;

void enqueue(int x)
{
    Node* newnode = new Node;
    newnode->data = x;
    newnode->next = nullptr;

    if (rear == nullptr)
    {
        front = rear = newnode;
        rear->next = front;
    }
    else
    {
        rear->next = newnode;
        rear = newnode;
        rear->next = front;
    }
}

void dequeue()
{
    Node* temp = front;
    if (front == nullptr && rear == nullptr)
    {
        std::cout << "List is empty";
    }
    else if (front == rear)
    {
        front = rear = nullptr;
        delete temp;
    }
    else
    {
        front = front->next;
        rear->next = front;
        delete temp;
    }
}

void peek()
{
    if (front == nullptr && rear == nullptr)
    {
        std::cout << "List is empty";
    }
    else
    {
        std::cout << front->data;
    }
}

void display()
{
    Node* temp = front;
    if (front == nullptr && rear == nullptr)
    {
        std::cout << "List is empty";
    }
    else
    {
        while (temp->next != front)
        {
            std::cout << temp->data;
            temp = temp->next;
        }
        std::cout << temp->data;
    }
}

int main()
{
    enqueue(4);
    enqueue(2);
    enqueue(6);

    display();

    dequeue();

    peek();

    return 0;
}
