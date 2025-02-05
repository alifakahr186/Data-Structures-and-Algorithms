#include <iostream>
#include <vector>

class HashTable {
private:
    std::vector<std::vector<int>> table;  
    int size;

public:
    // Constructor to initialize hash table with the specified size
    HashTable(int size) {
        this->size = size;
        table.resize(size);  // Resize the table to the specified size
    }

    // Hash function h(k) = (2k + 3) % size
    int hashFunction(int key) {
        return (2 * key + 3) % size;
    }

    void insert(int key) {
        int index = hashFunction(key);  
        table[index].push_back(key);     
        std::cout << "Inserted " << key << " into bucket " << index << std::endl;
    }

    // Display the hash table
    void display() {
        for (int i = 0; i < size; ++i) {
            std::cout << "Bucket " << i << ": ";
            for (int value : table[i]) {
                std::cout << value << " ";
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

    std::cout << "\nFinal Hash Table:" << std::endl;
    hashTable.display();

    return 0;
}
