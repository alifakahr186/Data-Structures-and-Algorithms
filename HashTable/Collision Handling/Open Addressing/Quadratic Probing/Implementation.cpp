#include <iostream>
#include <vector>

class HashTable {
private:
    std::vector<int> table;
    int size;

public:
    HashTable(int size) : size(size) {  
        table.resize(size, -1);  // Initialize the table with -1 indicating empty slots
    }

    void insert(int key) {
        int index = hashFunction(key);
        int i = 0;

        while (table[index] != -1 && i < size) { 
            index = (hashFunction(key) + i * i) % size;  
            i++;  
        }

        if (i < size) {
            table[index] = key;  // Place the key if an empty spot is found
        } else {
            std::cout << "Failed to insert key " << key << ": Table is full or no suitable slot found." << std::endl;
        }
    }

    int hashFunction(int key) {
        return key % size; 
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
