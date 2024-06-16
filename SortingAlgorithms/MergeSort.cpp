#include <iostream>
using namespace std;
 
void merge(int A[], int lb, int mid, int ub) {
    int i = lb;
    int j = mid + 1;
    int k = lb;
    int b[ub+1];

    while (i <= mid && j <= ub) {

        if (A[i] <= A[j]) {
            b[k] = A[i];
            i++;
        }

        else {
            b[k] = A[j];
            j++;
        }
        k++;
    }

    if (i > mid) {
        while (j <= ub) {
            b[k] = A[j];  
            j++;
            k++;
        }
    }
    else {
        while (i <= mid) {
            b[k] = A[i];
            i++;
            k++;
        }
    }

    for (k = lb; k <= ub; k++) {
        A[k] = b[k];
    }
}

void mergeSort(int A[], int lb, int ub) {

    if (lb < ub) {
        int mid = (lb + ub) / 2;
        mergeSort(A, lb, mid);
        mergeSort(A, mid + 1, ub);
        merge(A, lb, mid, ub);
        
    }
}

int main() {
    int arr[] = {7, 2, 9, 1, 5, 8, 3, 6, 10, 4};
    int size = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, 0, size - 1);

    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}
