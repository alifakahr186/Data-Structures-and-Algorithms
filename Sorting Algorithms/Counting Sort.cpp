#include <iostream>

using namespace std;

void countSort(int a[], int n, int b[], int k) {
    int count[k + 1] = {0};

    for (int i = 0; i < n; i++) {
        count[a[i]]++;
    }

    for (int i = 1; i <= k; i++) {
        count[i] = count[i] + count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        b[--count[a[i]]] = a[i];
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

    // Find the maximum element (k) to define the range of values
    int k = *max_element(arr, arr + size);

    // Create an output array b to store the sorted result
    int b[size];
    
    countSort(arr, size, b, k);

    cout << "Array after sorting: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
