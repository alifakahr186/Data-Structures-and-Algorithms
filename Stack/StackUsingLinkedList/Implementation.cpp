#include <iostream>
#include <limits>
using namespace std;

struct Node {
    int data;
    Node* link;
};

Node* top = nullptr; 

bool isEmpty() {
    return top == nullptr;
}

void push(int x) {
    Node* newnode = new Node();
    if (!newnode) {  // Memory allocation failed
        cout << "Stack Overflow" << endl;
        return;
    }
    newnode->data = x;
    newnode->link = top;
    top = newnode;
}

void pop() {
    if (isEmpty()) {
        cout << "Stack Underflow" << endl;
    } else {
        Node* temp = top;
        cout << "Popped item: " << top->data << endl;
        top = top->link;
        delete temp;
    }
}

void peek() {
    if (isEmpty()) {
        cout << "Stack is empty" << endl;
    } else {
        cout << "Top element: " << top->data << endl;
    }
}

void display() {
    if (isEmpty()) {
        cout << "Stack is empty" << endl;
    } else {
        Node* temp = top;
        cout << "Stack elements: ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->link;
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
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Display\n";
        cout << "4. Peek\n";
        cout << "0. Exit\n";

        option = getValidIntInput("Enter option: ");

        switch (option) {
        case 0:
            break;

        case 1:
            value = getValidIntInput("Enter value to push: ");
            push(value);
            break;

        case 2:
            pop();
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
