#include <iostream>
#include <vector>

class HashTable {
private:
    std::vector<int> table;  
    int size;              

public:
    HashTable(int size) {
        this->size = size;
        table.resize(size, -1);  
    }

    // Hash function: h(k) = (2k + 3) % size
    int hashFunction(int key) {
        return (2 * key + 3) % size;
    }

    void insert(int key) {
        int u = hashFunction(key);  
        for (int i = 0; i < size; ++i) {
            int index = (u + i * i) % size;  // Quadratic probing: (u + i^2) % size
            if (table[index] == -1) {       
                table[index] = key;         
                std::cout << "Inserted " << key << " at index " << index << std::endl;
                return;
            }
        }
        std::cout << "Hash table is full. Could not insert key: " << key << std::endl;
    }

    void display() {
        for (int i = 0; i < size; ++i) {
            std::cout << "Index " << i << ": ";
            if (table[i] == -1) {
                std::cout << "Empty" << std::endl;
            } else {
                std::cout << table[i] << std::endl;
            }
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

    std::cout << "\nFinal Hash Table:" << std::endl;
    hashTable.display();

    return 0;
}
