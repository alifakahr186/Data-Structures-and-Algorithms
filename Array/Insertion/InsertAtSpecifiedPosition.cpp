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

    cout << "Enter the number you want to insert: ";
    cin >> num;

    cout << "Enter the position to insert the number (1 to " << size + 1 << "): ";
    cin >> pos;

    if (pos < 1 || pos > size + 1) {
        cout << "Error: Invalid position. Please enter a position between 1 and " << size + 1 << "." << endl;
        return 1;
    }

    if (size >= MAX_SIZE) {
        cout << "Error: Cannot insert element. Array is full." << endl;
        return 1;
    }

    // Shift elements to the right to create space for the new element
    for (int i = size - 1; i >= pos - 1; i--) {
        arr[i + 1] = arr[i];
    }

    arr[pos - 1] = num;
    size++;

    cout << "Array after insertion: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
