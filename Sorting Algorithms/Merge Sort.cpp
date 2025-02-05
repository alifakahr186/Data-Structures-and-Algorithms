#include <iostream>

using namespace std;

void merge(int A[], int lb, int mid, int ub) {
    int i = lb;      
    int j = mid + 1; 
    int k = lb;      
    int b[ub - lb + 1]; 

    while (i <= mid && j <= ub) {
        if (A[i] <= A[j]) {
            b[k - lb] = A[i];
            i++;
        } else {
            b[k - lb] = A[j];
            j++;
        }
        k++;
    }

    while (i <= mid) {
        b[k - lb] = A[i];
        i++;
        k++;
    }

    while (j <= ub) {
        b[k - lb] = A[j];
        j++;
        k++;
    }

    for (k = lb; k <= ub; k++) {
        A[k] = b[k - lb];
    }
}

void mergeSort(int arr[], int lb, int ub) {

    if (lb < ub) {
        int mid = (lb + ub) / 2;
        mergeSort(arr, lb, mid);
        mergeSort(arr, mid + 1, ub);
        merge(arr, lb, mid, ub);
        
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

    mergeSort(arr, 0, size - 1);

    cout << "Array after sorting: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
