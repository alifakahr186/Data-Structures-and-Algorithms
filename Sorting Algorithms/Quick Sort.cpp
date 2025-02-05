#include <iostream>
#include <algorithm>

using namespace std;

int Partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int start = low;
    int end = high;

    while (start < end) {
        while (arr[start] <= pivot && start < high) {
            start++;
        }

        while (arr[end] > pivot) {
            end--;
        }

        if (start < end) {
            std::swap(arr[start], arr[end]);
        }
    }

    std::swap(arr[low], arr[end]);
    return end;
}

void QuickSort(int arr[], int low, int high) {
    if (low < high) {
        int partitionIndex = Partition(arr, low, high);
        QuickSort(arr, low, partitionIndex - 1);    // Left part
        QuickSort(arr, partitionIndex + 1, high);   // Right part
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

    QuickSort(arr, 0, size - 1);

    cout << "Array after sorting: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
