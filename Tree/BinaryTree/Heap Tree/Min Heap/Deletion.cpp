#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class MinHeap {
public:
    vector<int> A;  // Use a vector to store heap elements

    void insertMinHeap(int value) {
        A.push_back(value);  
        int n = A.size();  
        int i = n - 1;  

        while (i > 0) {
            int parent = (i - 1) / 2; 

            if (A[parent] > A[i]) {
                swap(A[parent], A[i]);
                i = parent; 
            } else {
                break;  
            }
        }
    }

    void deleteMinHeap() {
        if (A.size() == 0) {
            cout << "Heap is empty, nothing to delete!" << endl;
            return;
        }

        A[0] = A[A.size() - 1]; 
        A.pop_back();  

        heapifyDown(0);  
    }

    void heapifyDown(int i) {
        int n = A.size();
        int smallest = i; 
        int left = 2 * i + 1; 
        int right = 2 * i + 2;  

        if (left < n && A[left] < A[smallest])
            smallest = left;

        if (right < n && A[right] < A[smallest])
            smallest = right;

        if (smallest != i) {
            swap(A[i], A[smallest]);
            heapifyDown(smallest); 
        }
    }

    void display() {
        if (A.size() == 0) {
            cout << "Heap is empty!" << endl;
            return;
        }
        
        cout << "Heap elements: ";
        for (int i = 0; i < A.size(); i++) {
            cout << A[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    MinHeap minHeap;

    int n;
    cout << "How many elements would you like to insert? ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int value;
        cout << "Enter value to insert: ";
        cin >> value;

        minHeap.insertMinHeap(value);  
        cout << "Min Heap after insertion of " << value << ": ";
        minHeap.display();  
    }

    char choice;
    cout << "Do you want to delete the min element? (y/n): ";
    cin >> choice;

    while (choice == 'y') {
        minHeap.deleteMinHeap();  
        cout << "Min Heap after deletion: ";
        minHeap.display(); 

        cout << "Do you want to delete another min element? (y/n): ";
        cin >> choice;
    }

    return 0;
}
