#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class HashTable {
private:
    std::vector<int> table1, table2;
    int size;
    const int MAX_ITERATIONS = 10;  // Threshold to trigger rehashing

    void rehash() {
        std::cout << "Rehashing...\n";
        std::vector<int> oldTable1 = table1, oldTable2 = table2;
        size *= 2;  // Double the size
        table1.assign(size, -1);
        table2.assign(size, -1);

        for (int key : oldTable1) {
            if (key != -1) insert(key);
        }
        for (int key : oldTable2) {
            if (key != -1) insert(key);
        }
    }

public:
    HashTable(int size) {
        this->size = size;
        table1.resize(size, -1);  
        table2.resize(size, -1);
    }

    // Hash function h1(k) = k % m
    int hashFunction1(int key) const { 
        return key % size; 
    }  
    
    // Hash function h2(k) = k/m % m
    int hashFunction2(int key) const {
        return (key / size) % size; 
    }  


    void insert(int key) {
        int iterations = 0;

        while (iterations < MAX_ITERATIONS) {
            int u = hashFunction1(key);
            if (table1[u] == -1) {
                table1[u] = key;
                std::cout << "Inserted " << key << " into Table 1 at index " << u << std::endl;
                return;
            }

            std::swap(key, table1[u]);

            int u2 = hashFunction2(key);
            if (table2[u2] == -1) {
                table2[u2] = key;
                std::cout << "Inserted " << key << " into Table 2 at index " << u2 << std::endl;
                return;
            }

            std::swap(key, table2[u2]);
            iterations++;
        }

        rehash();
        insert(key);  // Retry insertion after rehashing
    }

    void display() const {
        std::cout << "Table 1:\n";

        for (int i = 0; i < size; i++) {
            std::cout << "Index " << i << ": ";
            if (table1[i] == -1) {
                std::cout << "Empty" << std::endl;
            } else {
                std::cout << table1[i] << std::endl;
            }
        }
        
        std::cout << "\n";
        
        std::cout << "Table 2:\n";

        for (int i = 0; i < size; i++) {
            std::cout << "Index " << i << ": ";
            if (table2[i] == -1) {
                std::cout << "Empty" << std::endl;
            } else {
                std::cout << table2[i] << std::endl;
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
