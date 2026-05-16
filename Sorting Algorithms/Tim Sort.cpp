#include <iostream>
#include <algorithm>

using namespace std;

const int MIN_RUN = 32;

void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

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

void timSort(int arr[], int n){
    const int RUN = 32;

    // Sort individual runs using insertion sort
    for (int r = 0; r < n; r += MIN_RUN) {
        int right = min(r + MIN_RUN - 1, n - 1);
        insertionSort(arr, r, right);
    }

    // Merge sorted runs
    for (int size = RUN; size < n; size *= 2) {
        for (int lb = 0; lb < n; lb += 2 * size) {
            int mid = min(lb + size - 1, n - 1);
            int ub = min(lb + 2 * size - 1, n - 1);

            if (mid < ub) {
                merge(arr, lb, mid, ub);
            }
        }
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

    timSort(arr, size);

    cout << "Array after sorting: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}