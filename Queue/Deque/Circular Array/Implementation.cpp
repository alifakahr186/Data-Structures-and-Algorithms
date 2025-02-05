#include <iostream>
#include <limits>
using namespace std;

#define N 100

int deque[N];
int front = -1; // removing elements
int rear = -1;  // adding elements

bool isFull() {
    return (rear + 1) % N == front; 
}

bool isEmpty() {
    return front == -1 && rear == -1; 
}

void enqueueFront(int x) {
    if (isFull()) {
        std::cout << "Dequeue is full." << std::endl;
    } 
    else if (isEmpty()) {
        front = rear = 0;
        deque[front] = x;
    } 
    else if (front == 0) {
        front = N - 1;
        deque[front] = x;
    } 
    else {
        front--;
        deque[front] = x;
    }
}

void enqueueRear(int x) {
    if (isFull()) {
        std::cout << "Dequeue is full." << std::endl;
    } 
    else if (isEmpty()) {
        front = rear = 0;
        deque[rear] = x;
    } 
    else if (rear == N - 1) {
        rear = 0;
        deque[rear] = x;
    } 
    else {
        rear++;
        deque[rear] = x;
    }
}

void display() {
    if (isEmpty()) {
        cout << "Deque is empty." << endl;
    } 
    else {
        int i = front;
        cout << "Deque elements: ";
        while (i != rear) {
            cout << deque[i] << " ";
            i = (i + 1) % N;
        }
        cout << deque[rear] << endl;
    }
}

void getFront() {
    if (isEmpty()) {
        cout << "Deque is empty." << endl;
    } else {
        cout << "Front element: " << deque[front] << endl;
    }
}

void getRear() {
    if (isEmpty()) {
        cout << "Deque is empty." << endl;
    } else {
        cout << "Rear element: " << deque[rear] << endl;
    }
}

void dequeueFront() {
    if (isEmpty()) {
        cout << "Deque is empty." << endl;
    } 
    else if (front == rear) { 
        cout << "Removed element: " << deque[front] << endl;
        front = rear = -1; 
    } 
    else {
        cout << "Removed element: " << deque[front] << endl;
        front = (front + 1) % N; 
    }
}

void dequeueRear() {
    if (isEmpty()) {
        cout << "Deque is empty." << endl;
    } 
    else if (front == rear) { 
        cout << "Removed element: " << deque[rear] << endl;
        front = rear = -1; 
    } 
    else {
        cout << "Removed element: " << deque[rear] << endl;
        if (rear == 0) {
            rear = N - 1; 
        } else {
            rear--; 
        }
    }
}

int getValidIntInput(string prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return value;
        }
    }
}

int main() {
    int option;
    int value;

    do {
        cout << "What operation do you want to perform? Select Option number. Enter 0 to exit.\n";
        cout << "1. Enqueue Front\n";
        cout << "2. Enqueue Rear\n";
        cout << "3. Dequeue Front\n";
        cout << "4. Dequeue Rear\n";
        cout << "5. Display\n";
        cout << "6. Get Front\n";
        cout << "7. Get Rear\n";
        cout << "0. Exit\n";

        option = getValidIntInput("Enter option: ");

        switch (option) {
        case 0:
            break;
        
        case 1:
            value = getValidIntInput("Enter value to enqueue at front: ");
            enqueueFront(value);
            break;
        
        case 2:
            value = getValidIntInput("Enter value to enqueue at rear: ");
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

        default:
            cout << "Invalid option. Please select a valid option." << endl;
        }

    } while (option != 0);
    
    return 0;
}
