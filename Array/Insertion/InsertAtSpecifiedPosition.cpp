#include <iostream>
using namespace std;

int main() {
    int a[50], size, i, num, pos;

    cout << "Enter size of array: ";
    cin >> size;

    cout << "Enter elements of array: ";
    for (i = 0; i < size; i++) {
        cin >> a[i];
    }

    cout << "Enter data you want to insert: ";
    cin >> num;

    cout << "Enter position: ";
    cin >> pos;

    if (pos <= 0 || pos > size + 1) {
        cout << "Invalid position\n";
    }
    else {
        for (i = size - 1; i >= pos - 1; i--) {
            a[i+1] = a[i];
        }
        a[pos-1] = num;
        size++;

        cout << "Array after insertion: ";
        for (i = 0; i < size; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
