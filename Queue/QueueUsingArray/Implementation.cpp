#include <iostream>
#define N 5

int queue[N];
int front = -1; //This is for removing element
int rear = -1; //This is for adding element

//Insertion
void enqueue(int x) {
    if (rear == N - 1) {
        std::cout << "Overflow" << std::endl;
    } else if (front == -1 && rear == -1) {
        front = rear = 0;
        queue[rear] = x;
    } else {
        rear++;
        queue[rear] = x;
    }
}

//Deletion
void dequeue() {
    if (front == -1 && rear == -1) {
        std::cout << "Underflow" << std::endl;
    } else if (front == rear) {
        front = rear = -1;
    } else {
        std::cout << queue[front] << std::endl;
        front++;
    }
}

void display() {
    if (front == -1 && rear == -1) {
        std::cout << "Underflow" << std::endl;
    } else {
        for (int i = front; i <= rear; i++) {
            std::cout << queue[i] << " ";
        }
        std::cout << std::endl;
    }
}

void peek() {
    if (front == -1 && rear == -1) {
        std::cout << "Underflow" << std::endl;
    } else {
        std::cout << queue[front] << std::endl;
    }
}

int main() {
    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);
    enqueue(5);
    enqueue(6); // Overflow

    display(); // 1 2 3 4 5

    dequeue();
    dequeue();
    dequeue();

    display(); // 4 5

    peek(); // 4

    return 0;
}
