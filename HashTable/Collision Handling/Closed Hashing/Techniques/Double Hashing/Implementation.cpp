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


    // Primary hash function: h(k) = (2k + 3) % m
    int hashFunction(int key) {
        return (2 * key + 3) % size;
    }

    // Secondary hash function: h^2(k) = (3k + 1)
    int secondaryHashFunction(int key) {
        return (3 * key + 1); 
    }

    void insert(int key) {
        int u = hashFunction(key);      
        int v = secondaryHashFunction(key); 

        for (int i = 0; i < size; ++i) {
            int index = (u + v * i) % size; 
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
