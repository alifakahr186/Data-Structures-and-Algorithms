#include <iostream>

void countSort(int a[], int n, int b[], int k) {
    int count[k + 1] = {0}; // Initialize count array with 0

    // Count the occurrences of each element in 'a'
    for (int i = 0; i < n; i++) {
        count[a[i]]++;
    }

    // Update count array to store the cumulative sum
    for (int i = 1; i <= k; i++) {
        count[i] = count[i] + count[i - 1];
    }

    // Place the elements in their correct positions in 'b'
    for (int i = n - 1; i >= 0; i--) {
        b[--count[a[i]]] = a[i];
    }
}

int main() {
    int n = 8; // Number of elements in array 'a'
    int a[] = {4, 2, 2, 8, 3, 3, 1, 7};
    int k = 8; // The maximum element in array 'a'
    int b[n]; // Array to store the sorted elements

    countSort(a, n, b, k);

    // Print the sorted array 'b'
    std::cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        std::cout << b[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
