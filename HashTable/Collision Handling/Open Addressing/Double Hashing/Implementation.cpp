#include <iostream>
#include <vector>

class HashTable {
private:
    std::vector<int> table;
    int size;

public:
    HashTable(int size) : size(size) {  
        table.resize(size, -1); 
    }

    // First hash function
    int hash1(int key) {
        return key % size;
    }

    // Second hash function (must never return zero, and preferably prime to the table size)
    int hash2(int key) {
        return 1 + (key % (size - 1));
    }

    void insert(int key) {
        int index = hash1(key);
        int v = hash2(key);
        int i = 0;

        while (table[index] != -1 && i < size) { 
            index = (index + v) % size;  // Apply double hashing
            i++;
        }

        if (table[index] == -1) {
            table[index] = key;  
        } else {
            std::cout << "Failed to insert key " << key << ": Table is full or no suitable slot found." << std::endl;
        }
    }

    void displayHash() {
        for (int i = 0; i < size; ++i) {
            std::cout << "Slot " << i << ": ";
            if (table[i] == -1) {
                std::cout << " _ ";  
            } else {
                std::cout << table[i];  
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    std::vector<int> arr = {3, 2, 9, 6, 11, 13, 7, 12};
    int size = 10;  

    HashTable hashTable(size);

    for (int key : arr) {
        hashTable.insert(key);
    }

    hashTable.displayHash();

    return 0;
}
