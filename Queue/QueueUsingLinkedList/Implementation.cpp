#include <iostream>
#include <limits>
using namespace std;

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
    } else {
        rear->next = newnode;   
        rear = newnode;         
    }
}

void dequeue() {
    if (isEmpty()) {
        std::cout << "Queue is empty! Underflow!" << std::endl;
    } else {
        Node* temp = front;
        std::cout << "Dequeued: " << front->data << std::endl;
        front = front->next;  

        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;  
    }
}

void peek() {
    if (isEmpty()) {
        std::cout << "Queue is empty! Cannot peek!" << std::endl;
    } else {
        std::cout << "Front element: " << front->data << std::endl;
    }
}

void display() {
    if (isEmpty()) {
        std::cout << "Queue is empty!" << std::endl;
    } else {
        Node* temp = front;
        cout << "Queue elements: ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
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
