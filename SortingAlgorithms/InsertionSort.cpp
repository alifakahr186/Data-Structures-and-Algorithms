#include <iostream>
using namespace std;

int main() {

    int a[50], size, i, j, temp;
    cout << "Enter size of array: ";
    cin >> size;

    cout << "Enter elements of array: ";
    for (i = 0; i < size; i++) {
        cin >> a[i]; 
    }
       
    for (int i = 1; i < size ; i++){
        temp = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > temp)
        {
            a[j+1] = a[j];
            j--;
        }
        
        a[j+1] = temp;
    }
    
    cout << "Sorted array: ";
    for(int i = 0; i < size; i++) {
        cout << a[i] << " ";
    }
    
    cout << endl;    
    return 0;
}
