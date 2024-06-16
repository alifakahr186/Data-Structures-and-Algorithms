#include <iostream>
using namespace std;

int main() {

    int a[50], size, i, j, temp;
    int flag = 0;
    cout << "Enter size of array: ";
    cin >> size;

    cout << "Enter elements  of array: ";
    for (i = 0; i < size; i++) {
        cin >> a[i];
    }
    
    cout << "Sorted list: ";
    for (int i = 0; i < size - 1 ; i++){
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (a[j] > a[j+1])
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            } 
        }
        if(flag == 0){
            break;
        }
    }
    
    cout << "Sorted array: ";
    for(int i = 0; i < size; i++) {
        cout << a[i] << " ";
    }
    
    cout << endl;    
    return 0;
}
