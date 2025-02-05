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

    cout << "Delete at the beginning[0][0]: ";

    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = arr[i + 1][j]; 
        }
    }

    for (int j = 0; j < cols; j++) {
        arr[rows - 1][j] = 0;  
    }
    rows--; 
    
    cout << "2D Array after insertion:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
