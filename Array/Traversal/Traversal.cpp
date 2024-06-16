#include <iostream>
using namespace std;

int main() {
    int a[50], size, i;

    cout << "Enter size of an array: ";
    cin >> size;

    cout << "Enter elements of array: ";
    for (i = 0; i < size; i++) {
        cin >> a[i];
    }

    cout << "Elements in array are: ";
    for (i = 0; i < size; i++) {
        cout << a[i] << " ";
    }

    return 0;
}
