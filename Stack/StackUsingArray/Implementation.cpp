#include <iostream>
#include <limits>
using namespace std;

#define N 100

int stack[N];
int top = -1; // Indicate an empty stack

bool isFull() {
    return top == N - 1;
}

bool isEmpty() {
    return top == -1;
}

void push(int x) {
    if (isFull()) {
        cout << "Stack Overflow" << endl;
    } else {
        top++;
        stack[top] = x;
    }
}

void pop() {
    if (isEmpty()) {
        cout << "Stack Underflow" << endl;
    } else {
        int item = stack[top];
        top--;
        cout << "Popped item: " << item << endl;
    }
}

void peek() {
    if (isEmpty()) {
        cout << "Stack is empty" << endl;
    } else {
        cout << "Top element: " << stack[top] << endl;
    }
}

void display() {
    if (isEmpty()) {
        cout << "Stack is empty" << endl;
    } else {
        cout << "Stack elements: ";
        for (int i = top; i >= 0; i--) {
            cout << stack[i] << " ";
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
