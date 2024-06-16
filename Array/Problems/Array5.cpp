#include <iostream>

int main() {
    int arr[] = {2, 5, 6, 1, 2, 8, 5, 6, 9, 3};
    int size = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                arr[j] = -1;
            }
        }
    }

    std::cout << "New array: ";
    for (int i = 0; i < size; i++) {
        if (arr[i] != -1) {
            std::cout << arr[i] << " ";
        }
    }

    return 0;
}
