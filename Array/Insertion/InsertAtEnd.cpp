#include <iostream>
using namespace std;

int main() {
    const int MAX_SIZE = 50;
    int arr[MAX_SIZE];      
    int size, num;

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

    cout << "Enter the number you want to insert at the end: ";
    cin >> num;

    if (size >= MAX_SIZE) {
        cout << "Error: Cannot insert element. Array is full." << endl;
        return 1;
    }

    arr[size] = num;
    size++;

    cout << "Array after insertion: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
