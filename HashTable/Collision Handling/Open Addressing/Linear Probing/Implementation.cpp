#include <iostream>
#include <vector>

class HashTable {
private:
    std::vector<int> table;
    int size;

public:
    HashTable(int size) : size(size){ 
        table.resize(size, -1); 
    }

    void insert(int key) {
        int index = hashFunction(key);

        // Linear probing to find an empty slot
        while (table[index] != -1) {
            index = (index + 1) % size;
        }

        table[index] = key; 
    }

    int hashFunction(int key) {
        return key % size; 
    }

    void displayHash() {
        for (int i = 0; i < size; ++i) {
            std::cout << "Slot " << i << ": ";
            if (table[i] != -1) {
                std::cout << table[i];
            } else {
                std::cout << " _ ";
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
