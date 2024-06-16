#include <iostream>

#define N 5

int S1[N], S2[N];

int top1 = -1, top2 = -1;
int count = 0;

void enqueue(int x) {
    push1(x);
    count++;
}

void push1(int data){
    if (top1 == N - 1){
    
        std::cout << "Overflow" << std::endl;
    } 
    
    else{
        top1++;
        S1[top1] = data;
    }
}


void push2(int data) {
    if (top2 == N - 1) {
        std::cout << "Overflow" << std::endl;
    } 
    
    else {
        top2++;
        S2[top2] = data;
    }

}

void dequeue() {
    int i, a, b;

    if (top1 == -1 && top2 == -1) {
        std::cout << "Queue is empty" << std::endl;
    } 
    
    else {
        for (i = 0; i < count; i++) {
            a = pop1();
            push2(a);
        }

        b = pop2();
        std::cout << b << std::endl;

        count--;
        
        for (i = 0; i < count; i++) {
            a = pop2();
            push1(a);
        }

    }

}

int pop1() {
    return S1[top1--];
}

int pop2() {
    return S2[top2--];
}

void display() {
    int i;

    for (i = 0; i <= top1; i++) {
        std::cout << S1[i] << " ";
    }
    
    std::cout << std::endl;

}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();

    dequeue();
    display();

    return 0;
}
