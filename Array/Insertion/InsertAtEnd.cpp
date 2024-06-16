#include <iostream>
using namespace std;

int main() {
    int a[50], size, i, num;

    cout << "Enter size of array: ";
    cin >> size;

    cout << "Enter elements of array: ";
    for (i = 0; i < size; i++) {
        cin >> a[i];
    }

    cout << "Enter data you want to insert: ";
    cin >> num;

    a[size] = num;
    size++;

    cout << "Array after insertion: ";
    for (i = 0; i < size; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}
