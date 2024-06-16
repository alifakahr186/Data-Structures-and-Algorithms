#include <iostream>
using namespace std;

int binarySearch(int a[], int n, int data) {
    int l = 0, r = n - 1;

    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (data == a[mid]) {
            return mid;
        } else if (data < a[mid]) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return -1;
}

int main() {
    int arr[] = {5, 9, 17, 23, 25, 45, 59, 63, 71, 89};
    int n = sizeof(arr) / sizeof(arr[0]);
    int data = 59;

    int result = binarySearch(arr, n, data);

    if (result == -1) {
        cout << "Element not found." << endl;
    } else {
        cout << "Element found at index: " << result << endl;
    }

    return 0;
}



