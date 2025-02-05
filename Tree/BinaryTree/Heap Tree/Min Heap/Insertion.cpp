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

    void display() {
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

    return 0;
}
