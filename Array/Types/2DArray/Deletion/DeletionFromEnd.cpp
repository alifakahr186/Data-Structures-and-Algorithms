#include <iostream>
using namespace std;

int main() {
    const int MAX_ROWS = 5; 
    const int MAX_COLS = 5; 
    int rows, cols, num;
    int arr[MAX_ROWS][MAX_COLS]; 

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

    cout << "Delete at the end: ";

    if (cols > 1) {
        arr[rows - 1][cols - 1] = 0; 
    } else if (cols == 1 && rows > 1) {
        rows--; 
    } else {
        cout << "Array is empty. No element to delete." << endl;
        return 1;
    }
    
    cout << "2D Array after insertion:\n" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
