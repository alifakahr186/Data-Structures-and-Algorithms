#include <iostream>
using namespace std;

int main() {
    const int MAX_DEPTH = 5; 
    const int MAX_ROWS = 5;  
    const int MAX_COLS = 5;  

    int depth, rows, cols;
    int arr[MAX_DEPTH][MAX_ROWS][MAX_COLS]; 

    cout << "Enter the number of depths (max " << MAX_DEPTH << "): ";
    cin >> depth;
    cout << "Enter the number of rows (max " << MAX_ROWS << "): ";
    cin >> rows;
    cout << "Enter the number of columns (max " << MAX_COLS << "): ";
    cin >> cols;

    if (depth < 1 || depth > MAX_DEPTH || rows < 1 || rows > MAX_ROWS || cols < 1 || cols > MAX_COLS) {
        cout << "Error: Invalid size. Depth, rows, and columns must be within the allowed range." << endl;
        return 1;
    }

    cout << "Enter the elements of the 3D array:" << endl;
    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < rows; j++) {
            for (int k = 0; k < cols; k++) {
                cout << "arr[" << i << "][" << j << "][" << k << "]: ";
                cin >> arr[i][j][k];
            }
        }
    }

    cout << "3D Array after insertion:" << endl;
    for (int i = 0; i < depth; i++) {
        cout << "Table " << i + 1 << ":" << endl; 
        for (int j = 0; j < rows; j++) {
            for (int k = 0; k < cols; k++) {
                cout << arr[i][j][k] << " ";
            }
            cout << endl; 
        }
        cout << endl; 
    }

    return 0;
}
