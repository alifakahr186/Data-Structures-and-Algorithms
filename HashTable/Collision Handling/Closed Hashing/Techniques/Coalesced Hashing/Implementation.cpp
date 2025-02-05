#include <iostream>
#include <vector>
using namespace std;

class HashTable {
private:
    struct Node {
        int key;   
        int next;  
    };

    vector<Node> table; 
    int size;          

    int findLastAvailableSlot() {
        for (int i = size - 1; i >= 0; --i) {
            if (table[i].key == -1) {
                return i;
            }
        }
        return -1; 
    }

public:
    HashTable(int size) {
        this->size = size;
        table.resize(size, {-1, -1});
    }

    // Hash function: h(k) = k % size
    int hashFunction(int key) {
        return key % size;
    }

    void insert(int key) {
        int index = hashFunction(key);

        if (table[index].key == -1) {
            table[index].key = key;
            cout << "Inserted " << key << " at index " << index << endl;
        } else {
            int newSlot = findLastAvailableSlot();
            if (newSlot == -1) {
                cout << "Hash table is full. Could not insert key: " << key << endl;
                return;
            }

            table[newSlot].key = key;
            cout << "Inserted " << key << " at index " << newSlot << endl;

            int current = index;
            while (table[current].next != -1) {
                current = table[current].next;
            }
            table[current].next = newSlot;
        }
    }

    void display() {
        for (int i = 0; i < size; ++i) {
            cout << "Index " << i << ": ";
            if (table[i].key == -1) {
                cout << "Empty";
            } else {
                cout << table[i].key;
                if (table[i].next != -1) {
                    cout << " -> " << table[i].next;
                }
            }
            cout << endl;
        }
    }
};

int main() {
    std::vector<int> arr = {10, 15, 26, 30, 25, 35, 45}; 
    int size = 10;  

    HashTable hashTable(size);

    for (int key : arr) {
        hashTable.insert(key);
    }

    std::cout << "\nFinal Hash Table:" << std::endl;
    hashTable.display();

    return 0;
}

