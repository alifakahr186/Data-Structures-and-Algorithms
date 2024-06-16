#include <iostream>

using namespace std;

void shellSort(int arr[], int n){
    for (int gap = n / 2; gap > 0; gap /= 2){

        for (int j = gap; j < n; j++){

            for (int i = j - gap; i >= 0; i -= gap){

                if (arr[i + gap] > arr[i]){
                    break;
                } 
                else{
                    swap(arr[i + gap], arr[i]);
                }
    
            }

        }

    }

}

int main() {
    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    int arr[n];
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Original Array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    shellSort(arr, n);

    cout << "Sorted Array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
