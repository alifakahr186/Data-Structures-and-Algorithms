#include <iostream>

struct Node {
    int data;
    Node* next;
};

Node* front = nullptr;
Node* rear = nullptr;

void enqueue(int x){
    Node* newnode = new Node;
    newnode->data = x;
    newnode->next = nullptr;

    if(front == nullptr && rear == nullptr){
        front = rear = newnode;
    }

    else{
        rear->next = newnode;
        rear = newnode;
    }
}

void display() {
    Node* temp = front;

    if(front == nullptr && rear == nullptr){
        std::cout << "Underflow";
    }

    else{
        
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
    }
}

void dequeue(){
    
    Node* temp = front;

    if (front == nullptr && rear == nullptr){
        std::cout << "Underflow";
    }

    else{
        std::cout << "\n";
        std::cout << front->data;
        front = front->next;
        delete temp;
    }

}

void peek(){

    if (front == nullptr && rear == nullptr){
        std::cout << "Underflow";
    }

    else{
        std::cout << front->data;
    }
}

int main() {
    enqueue(8);
    enqueue(4);
    enqueue(9);

    display();

    dequeue();



    return 0;
}
