#include <iostream>
#include <cmath>    

using namespace std;

void combSort(int arr[], int n) {
    int gap = n;
    const double shrink = 1.3;
    bool swapped = true;

    while (gap > 1 || swapped) {
        // shrink the gap
        gap = static_cast<int>(floor(gap / shrink));
        if (gap < 1) gap = 1;

        swapped = false;

        // compare elements with current gap
        for (int i = 0; i + gap < n; ++i) {
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
                swapped = true;   // mark that we did a swap
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

    combSort(arr, size);

    cout << "Array after sorting: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
