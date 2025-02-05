#include <iostream>
using namespace std;

int main() {
    const int SIZE = 5; 
    int arr[SIZE];      
    int key, i;
    bool found = false; 

    cout << "Enter " << SIZE << " elements of the array: ";
    for (i = 0; i < SIZE; i++) {
        cin >> arr[i];
    }

    cout << "Enter the number to search: ";
    cin >> key;

    for (i = 0; i < SIZE; i++) {
        if (arr[i] == key) {
            found = true;
            break; 
        }
    }

    if (found) {
        cout << "Element " << key << " found at position " << i + 1 << " (1-based index)." << endl;
    } else {
        cout << "Element " << key << " not found in the array." << endl;
    }

    return 0;
}