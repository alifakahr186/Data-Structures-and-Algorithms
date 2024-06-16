#include <iostream>
using namespace std;

const int N = 100;
int stack[N];
int top = -1;

void push() {
    int x;
    cout << "Enter data: ";
    cin >> x;
    if (top == N - 1) {
        cout << "Overflow" << endl;
    }
    else {
        top++;
        stack[top] = x;
    }
}

void pop() {
    int item;
    if (top == -1) {
        cout << "Underflow" << endl;
    }
    else {
        item = stack[top];
        top--;
        cout << item << endl;
    }
}

void peek() {
    if (top == -1) {
        cout << "Stack is empty" << endl;
    }
    else {
        cout << stack[top] << endl;
    }
}

void display() {
    if (top == -1) {
        cout << "Stack is empty" << endl;
    }
    else {
        for (int i = top; i >= 0; i--) {
            cout << stack[i] << " ";
        }
        cout << endl;
    }
}

int main() {
    push();
    push();
    push();
    push();
    push();
    
    pop();
    
    peek();

    display();

    
    return 0;
}
