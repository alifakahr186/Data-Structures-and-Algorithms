#include <iostream>
#include <limits>
using namespace std;

#define N 100

int queue[N];
int front = -1; // removing elements
int rear = -1;  // adding elements

bool isFull() {
    return rear == N - 1; // Queue for full
}

bool isEmpty() {
    return front == -1 && rear == -1;
}

// Add an element
void enqueue(int x) {
    if (isFull()) {
        cout << "Overflow: Queue is full!" << endl;
    } else if (isEmpty()) {
        front = rear = 0;
        queue[rear] = x;
    } else {
        rear++;
        queue[rear] = x;
    }
}

// Remove an element
void dequeue() {
    if (isEmpty()) {
        cout << "Underflow: Queue is empty!" << endl;
    } else if (front == rear) {
        cout << "Removing element: " << queue[front] << endl;
        front = rear = -1; // Reset to initial state
    } else {
        cout << "Removing element: " << queue[front] << endl;
        front++;
    }
}

void display() {
    if (isEmpty()) {
        cout << "Queue is empty" << endl;
    } else {
        cout << "Queue elements: ";
        for (int i = front; i <= rear; i++) {
            cout << queue[i] << " ";
        }
        cout << endl;
    }
}

// For front element
void peek() {
    if (isEmpty()) {
        cout << "Queue is empty" << endl;
    } else {
        cout << "Front element: " << queue[front] << endl;
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

    do
    {
        cout << "What operation do you want to perform? Select Option number. Enter 0 to exit.\n";
        cout << "1. Enqueue\n";
        cout << "2. Dequeue\n";
        cout << "3. Display\n";
        cout << "4. Peek\n";
        cout << "0. Exit\n";

        option = getValidIntInput("Enter option: ");

        switch (option)
        {
        case 0:
            break;
        
        case 1:
            value = getValidIntInput("Enter value to enqueue: ");
            enqueue(value);
            break;
        
        case 2:
            dequeue();
            break;

        case 3:
            display();
            break;

        case 4:
            peek();
            break;

        default:
            cout << "Invalid option. Please select a valid option." << endl;
        }

    } while (option != 0);
    
    return 0;
}
