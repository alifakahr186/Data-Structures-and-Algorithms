#include <iostream>
#include <limits>
using namespace std;

#define N 100

int S1[N], S2[N]; // Stacks

int top1 = -1, top2 = -1; 
int count = 0; 

bool isEmpty() {
    return top1 == -1;
}

bool isEmpty2() {
    return top2 == -1;
}

void enqueue(int x) {
    int count;  
    push1(x);  
    count++;
}

void push1(int data){
    if (top1 == N - 1) {
        std::cout << "Overflow" << std::endl;
    } else {
        top1++;
        S1[top1] = data;
    }
}

void push2(int data) {
    if (top2 == N - 1) {
        std::cout << "Overflow" << std::endl;
    } else {
        top2++;
        S2[top2] = data;
    }
}

void dequeue() {
    if (isEmpty()) {
        std::cout << "Queue is empty" << std::endl;
    } else {
        // Transfer elements from S1 to S2 if S2 is empty
        if (isEmpty2()) {
            while (!isEmpty()) {
                int a = pop1();
                push2(a);
            }
        }
        
        int count;
        int b = pop2();
        std::cout << "Dequeued: " << b << std::endl;
        count--;
    }
}

int pop1() {
    return S1[top1--];
}

int pop2() {
    return S2[top2--];
}

void peek() {
    if (isEmpty()) {
        std::cout << "Queue is empty!" << std::endl;
    } else {
        // Ensure elements are moved from S1 to S2 if needed
        if (isEmpty2()) {
            while (!isEmpty()) {
                int a = pop1();
                push2(a);
            }
        }
        std::cout << "Front element: " << S2[top2] << std::endl;
    }
}

void display() {
    if (isEmpty()) {
        std::cout << "Queue is empty!" << std::endl;
        return;
    }

    cout << "Queue elements: ";
    if (!isEmpty2()) {
        for (int i = top2; i >= 0; i--) {
            cout << S2[i] << " ";
        }
    }

    for (int i = 0; i <= top1; i++) {
        cout << S1[i] << " ";
    }

    cout << endl;
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
