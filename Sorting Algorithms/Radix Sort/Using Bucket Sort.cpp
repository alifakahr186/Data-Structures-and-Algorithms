#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

// maximum element
int maxEle(int arr[], int n) {
    int maxVal = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

// insert at end of linked list
void insertAtEnd(Node*& head_ref, int value) {
    Node* new_node = new Node(value);

    if (head_ref == nullptr) {
        head_ref = new_node;
        return;
    }

    Node* temp = head_ref;

    while (temp->next != nullptr) {
        temp = temp->next;
    }

    temp->next = new_node;
}

// radix sort using buckets
void radixSort(int arr[], int n) {

    int maxVal = maxEle(arr, n);

    Node* bucket[10];

    int exp = 1;

    // loop until all digit places are processed
    while (maxVal / exp > 0) {

        // initialize buckets
        for (int i = 0; i < 10; i++) {
            bucket[i] = nullptr;
        }

        // distribute elements into buckets
        for (int i = 0; i < n; i++) {
            int digit = (arr[i] / exp) % 10;
            insertAtEnd(bucket[digit], arr[i]);
        }
 
        // collect elements back into array
        int index = 0;

        for (int i = 0; i < 10; i++) {
            Node* temp = bucket[i];

            while (temp != nullptr) {
                arr[index++] = temp->data;
                temp = temp->next;
            }
        }

        exp *= 10;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int* arr = new int[n];

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    radixSort(arr, n);

    cout << "Sorted array: ";
    printArray(arr, n);

    delete[] arr;

    return 0;
}