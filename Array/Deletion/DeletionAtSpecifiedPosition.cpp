#include <iostream>
using namespace std;

int main() {
    const int MAX_SIZE = 50; 
    int arr[MAX_SIZE];      
    int size, num, pos;

    cout << "Enter the size of the array (max " << MAX_SIZE << "): ";
    cin >> size;

    if (size < 0 || size > MAX_SIZE) {
        cout << "Error: Invalid size. Size must be between 0 and " << MAX_SIZE << "." << endl;
        return 1;
    }

    cout << "Enter " << size << " elements of the array: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    cout << "Enter position to delete: ";
    cin >> pos;

    if (pos < 1 || pos > size) {
        cout << "Error: Invalid position. Please enter a position between 1 and " << size << "." << endl;
        return 1;
    }

    for (int i = pos - 1; i < size - 1; i++) {
        arr[i] = arr[i + 1];  // Shift elements left
    }
    size--;


    cout << "Array after insertion: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
