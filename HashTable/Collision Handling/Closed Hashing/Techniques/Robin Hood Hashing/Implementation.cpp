#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;      
    int size;                     
    std::vector<int> displacement; 

public:
    HashTable(int size) {
        this->size = size;
        table.resize(size, -1);           
        displacement.resize(size, 0);   
    }

    // Hash function: h(k) = k % size
    int hashFunction(int key) {
        return key % size;
    }

    void insert(int key) {
        int u = hashFunction(key);      
        int localDisplacement = 0;    

        while (true) {
            if (table[u] == -1) {
                // Empty slot found
                table[u] = key;
                displacement[u] = localDisplacement;
                std::cout << "Inserted " << key << " at index " << u << " with probe distance " << localDisplacement << std::endl;
                return;
            }

            // Compare displacements
            int existingDisplacement = displacement[u];
            if (localDisplacement > existingDisplacement) {
                // Swap the new key with the existing key
                std::swap(key, table[u]);
                std::swap(localDisplacement, displacement[u]);
                std::cout << "Swapped " << key << " into index " << u << std::endl;
            }

            // Move to the next slot (linear probing)
            u = (u + 1) % size;
            localDisplacement++;

            // If we've checked the entire table, the table is full
            if (localDisplacement >= size) {
                std::cout << "Hash table is full. Could not insert key: " << key << std::endl;
                return;
            }
        }
    }

    void display() {
        for (int i = 0; i < size; ++i) {
            std::cout << "Index " << i << ": ";
            if (table[i] == -1) {
                std::cout << "Empty";
            } else {
                std::cout << table[i];
            }
            std::cout << "  Probe: " << displacement[i] << std::endl;
        }
    }
};

int main() {
    std::vector<int> arr = {3, 2, 9, 6, 11, 13, 7, 12};
    int size = 7; 

    HashTable hashTable(size);

    for (int key : arr) {
        hashTable.insert(key);
    }

    std::cout << "\nFinal Hash Table:" << std::endl;
    hashTable.display();

    return 0;
}
