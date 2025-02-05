#include <iostream>
using namespace std;

int main() {
    const int MAX_ROWS = 5; 
    const int MAX_COLS = 5; 
    int rows, cols, key;
    int arr[MAX_ROWS][MAX_COLS]; 
    bool found = false; 

    cout << "Enter the number of rows (max " << MAX_ROWS << "): ";
    cin >> rows;
    cout << "Enter the number of columns (max " << MAX_COLS << "): ";
    cin >> cols;

    if (rows < 0 || rows > MAX_ROWS || cols < 0 || cols > MAX_COLS) {
        cout << "Error: Invalid size. Rows and columns must be within the allowed range." << endl;
        return 1;
    }

    cout << "Enter the elements of the 2D array:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> arr[i][j];
        }
    }

    cout << "Enter the number to search: ";
    cin >> key;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] == key) {
                found = true;
                cout << "Element " << key << " found at position [" << i << "][" << j << "]." << endl;
                break;
            }
        }
        if (found) break; 
    }

    if (!found) {
        cout << "Element " << key << " not found in the array." << endl;
    }

    // Optionally, print the entire 2D array
    cout << "The 2D array is:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
