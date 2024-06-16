#include <iostream>
#include <algorithm>

int Partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int start = low;
    int end = high;

    while (start < end) {
        while (arr[start] <= pivot) {
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
        QuickSort(arr, low, partitionIndex - 1);
        QuickSort(arr, partitionIndex + 1, high);
    }
}

int main() {
    int arr[] = {3, 7, 8, 5, 2, 1, 9, 4};
    int size = sizeof(arr) / sizeof(arr[0]);

    QuickSort(arr, 0, size - 1);

    std::cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }

    return 0;
}
