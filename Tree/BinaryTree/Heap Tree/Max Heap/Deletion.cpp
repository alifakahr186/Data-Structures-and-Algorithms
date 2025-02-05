#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class MaxHeap {
public:
    vector<int> A;  // Use a vector to store heap elements

    void insertMaxHeap(int value) {
        A.push_back(value);
        int n = A.size();  
        int i = n - 1;  

        while (i > 0) {
            int parent = (i - 1) / 2;

            if (A[parent] < A[i]) {
                swap(A[parent], A[i]);
                i = parent;  
            } else {
                break;  
            }
        }
    }

    void deleteMaxHeap() {
        if (A.size() == 0) {
            cout << "Heap is empty, nothing to delete!" << endl;
            return;
        }

        A[0] = A[A.size() - 1];  // Move the last element to the root
        A.pop_back();  

        heapifyDown(0);
    }

    void heapifyDown(int i) {
        int n = A.size();
        int largest = i;  
        int left = 2 * i + 1;  
        int right = 2 * i + 2;  

        if (left < n && A[left] > A[largest])
            largest = left;

        if (right < n && A[right] > A[largest])
            largest = right;

        if (largest != i) {
            swap(A[i], A[largest]);
            heapifyDown(largest);  // Recursively heapify the affected subtree
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
    MaxHeap maxHeap;

    int n;
    cout << "How many elements would you like to insert? ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int value;
        cout << "Enter value to insert: ";
        cin >> value;

        maxHeap.insertMaxHeap(value);
        cout << "Max Heap after insertion of " << value << ": ";
        maxHeap.display();
    }

    char choice;
    cout << "Do you want to delete the max element? (y/n): ";
    cin >> choice;

    while (choice == 'y') {
        maxHeap.deleteMaxHeap();
        cout << "Max Heap after deletion: ";
        maxHeap.display();

        cout << "Do you want to delete another max element? (y/n): ";
        cin >> choice;
    }

    return 0;
}
