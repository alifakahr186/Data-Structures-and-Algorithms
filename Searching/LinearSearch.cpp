#include <iostream>
using namespace std;

int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;  // Return the index where the target is found
        }
    }
    return -1;  // Return -1 if the target is not found
}

int main() {
    int arr[] = {5, 2, 7, 9, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    int target = 7;
    int result = linearSearch(arr, n, target);

    if (result == -1) {
        cout << "Element not found";
    } else {
        cout << "Element found at index " << result;
    }

    return 0;

}



