#include <iostream>

using namespace std;

void maxHeapify(int A[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && A[l] > A[largest]) {
        largest = l;
    }

    if (r < n && A[r] > A[largest]) {
        largest = r;
    }
    
    // If the largest is not the root, swap and continue heapifying
    if (largest != i) {
        swap(A[i], A[largest]);
        maxHeapify(A, n, largest);
    }
}

void heapSort(int A[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(A, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(A[0], A[i]);
        maxHeapify(A, i, 0);
    }
}

int main() {
    const int MAX_SIZE = 50; 
    int arr[MAX_SIZE];       
    int size;

    cout << "Enter the size of the array (max " << MAX_SIZE << "): ";
    cin >> size;

    if (size <= 0 || size > MAX_SIZE) {
        cout << "Error: Invalid size. Size must be between 1 and " << MAX_SIZE << "." << endl;
        return 1;
    }

    cout << "Enter " << size << " elements of the array: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    heapSort(A, n);

    cout << "Array after sorting: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
