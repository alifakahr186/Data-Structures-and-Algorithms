#include <iostream>
#include <limits>
using namespace std;

#define N 100

struct Node {
    int data;
    Node* next;
};

Node* front = nullptr; 
Node* rear = nullptr;  

bool isEmpty() {
    return front == nullptr;
}

void enqueue(int x) {
    Node* newnode = new Node;
    newnode->data = x;
    newnode->next = nullptr;

    if (isEmpty()) {
        front = rear = newnode;
        rear->next = front; // Circular linking
    } else {
        rear->next = newnode; 
        rear = newnode;       
        rear->next = front;  
    }
}

void dequeue() {
    if (isEmpty()) {
        std::cout << "Queue is empty!" << std::endl;
    } else if (front == rear) { // Only one element in the queue
        cout << "Removed element: " << front->data << endl;
        delete front;
        front = rear = nullptr;
    } else {
        Node* temp = front;
        cout << "Removed element: " << front->data << endl;
        front = front->next;
        rear->next = front; // Maintain circularity
        delete temp;
    }
}

void peek() {
    if (isEmpty()) {
        cout << "Queue is empty!" << endl;
    } else {
        cout << "Front element: " << front->data << endl;
    }
}

void display() {
    if (isEmpty()) {
        std::cout << "Queue is empty!" << std::endl;
    } else {
        Node* temp = front;
        cout << "Queue elements: ";
        do {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != front); // Loop until we reach back to front
        cout << endl;
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
        cout << "1. Enqueue\n";
        cout << "2. Dequeue\n";
        cout << "3. Display\n";
        cout << "4. Peek\n";
        cout << "0. Exit\n";

        option = getValidIntInput("Enter option: ");

        switch (option) {
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
