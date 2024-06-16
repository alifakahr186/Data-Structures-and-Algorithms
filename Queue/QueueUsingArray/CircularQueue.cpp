#include <iostream>

#define N 5

int queue[N];
int front = -1;
int rear = -1;

void enqueue(int x)
{
    if (front == -1 && rear == -1)
    {
        front = rear = 0;
        queue[rear] = x;
    }
    else if (((rear + 1) % N) == front)
    {
        std::cout << "Queue is full." << std::endl;
    }
    else
    {
        rear = (rear + 1) % N;
        queue[rear] = x;
    }
}

void dequeue()
{
    if (front == -1 && rear == -1)
    {
        std::cout << "Underflow." << std::endl;
    }
    else if (front == rear)
    {
        front = rear = -1;
    }
    else
    {
        std::cout << queue[front] << std::endl;
        front = (front + 1) % N;
    }
}

void display()
{
    int i = front;

    if (front == -1 && rear == -1)
    {
        std::cout << "Queue is empty." << std::endl;
    }
    else
    {
        std::cout << "Queue is: ";

        while (i != rear)
        {
            std::cout << queue[i] << " ";
            i = (i + 1) % N;
        }

        std::cout << queue[rear] << std::endl;
    }
}

int main()
{
    enqueue(5);
    enqueue(2);
    enqueue(-1);
    enqueue(6);
    enqueue(9);

    display();

    dequeue();
    dequeue();

    enqueue(3);
    enqueue(10);
    enqueue(11);

    return 0;
}
