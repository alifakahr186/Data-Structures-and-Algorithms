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
    int A[] = {7, 2, 9, 1, 5, 8, 3, 6, 10, 4};
    int n = sizeof(A) / sizeof(A[0]);

    cout << "Array before sorting: ";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }

    heapSort(A, n);

    cout << "\nArray after sorting: ";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }

    return 0;
}
