#include <iostream>
using namespace std;

int main() {
    int n = 10;
    int a[n] = {7, 1, 9, 2, 10, 5, 8, 3, 6, 4};
    int i, j, temp;

    for (i = 0; i < n - 1; i++) {
        int min = i;
        j = i + 1;

        while (j < n) {
            if (a[j] < a[min]) {
                min = j;
            }
            j++;
        }

        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }

    // print the sorted array
    cout << "Sorted array: ";
    for (i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}
