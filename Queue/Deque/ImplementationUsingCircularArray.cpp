#include <iostream>

#define N 5

int deque[N];
int f = -1, r = -1;

void enqueueFront(int x) {
    if ((f == 0 && r == N-1) || (f == r + 1)) {
        std::cout << "Queue is full." << std::endl;
    } 
    
    else if (f == -1 && r == -1) {
        f = r = 0;
        deque[f] = x;
    } 
    
    else if (f == 0) {
        f = N - 1;
        deque[f] = x;
    } 
    
    else {
        f--;
        deque[f] = x;
    }
}

void enqueueRear(int x) {
    if ((f == 0 && r == N-1) || (f == r + 1)) {
        std::cout << "Queue is full." << std::endl;
    } 
    
    else if (f == -1 && r == -1) {
        f = r = 0;
        deque[r] = x;
    } 
    
    else if (r == N - 1) {
        r = 0;
        deque[r] = x;
    } 
    
    else {
        r++;
        deque[r] = x;
    }

}

void display() {
    int i = f;

    while (i != r) {
        std::cout << deque[i] << " ";
        i = (i + 1) % N;
    }

    std::cout << std::endl;

}

void getFront() {
    std::cout << deque[f] << std::endl;

}

void getRear() {
    std::cout << deque[r] << std::endl;

}

void dequeueFront() {
    if (f == -1 && r == -1) {
        std::cout << "Deque is empty." << std::endl;
    } 
    
    else if (f == r) {
        f = r = -1;
    } 
    
    else if (f == N - 1) {
        std::cout << deque[f] << std::endl;
        f = 0;
    } 
    
    else {
        std::cout << deque[f] << std::endl;
        f++;
    }

}

void dequeueRear() {
    if (f == -1 && r == -1) {
        std::cout << "Deque is empty." << std::endl;
    } 
    
    else if (f == r) {
        f = r = -1;
    } 
    
    else if (r == 0) {
        std::cout << deque[r] << std::endl;
        r = N - 1;
    } 
    
    else {
        std::cout << deque[r] << std::endl;
        r--;
    }

}

int main() {
    enqueueFront(2);
    enqueueFront(5);

    enqueueRear(-1);
    enqueueRear(0);

    enqueueFront(7);
    enqueueFront(4);

    display();

    getFront();
    getRear();

    dequeueFront();     
    display();          
    dequeueRear();      
    display(); 
          
    return 0;
}
