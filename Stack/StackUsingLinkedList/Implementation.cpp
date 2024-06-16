#include <iostream>

struct Node {
    int data;
    Node* link;
};

Node* top = nullptr;

void push(int x) {
    Node* newnode = new Node();
    newnode->data = x;
    newnode->link = top;
    top = newnode;
}

void display() {
    Node* temp = top;

    if (top == nullptr) {
        std::cout << "List is empty" << std::endl;
    } else {
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->link;
        }
        std::cout << std::endl;
    }
}

void peek() {
    if (top == nullptr) {
        std::cout << "Stack is empty" << std::endl;
    } else {
        std::cout << "Top element is " << top->data << std::endl;
    }
}

void pop() {
    Node* temp = top;

    if (top == nullptr) {
        std::cout << "Underflow" << std::endl;
    } else {
        std::cout << top->data << std::endl;
        top = top->link;
        delete temp;
    }
}

int main() {
    
    push(2);
    push(3);
    push(10);

    display();
    peek();
    pop();
    peek();
    display();

    return 0;
}
