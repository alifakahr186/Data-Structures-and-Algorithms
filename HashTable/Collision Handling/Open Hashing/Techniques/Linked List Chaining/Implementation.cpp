#include <iostream>
#include <vector>

struct Node {
    int data;
    Node* next;

    Node(int d) : data(d), next(nullptr) {} 
};

class HashTable {
private:
    std::vector<Node*> table;  
    int size;

public:
    HashTable(int size) {
        this->size = size;
        table.resize(size, nullptr);
    }

    // Destructor to free allocated memory and prevent memory leaks
    ~HashTable() {
        // Free memory used by each linked list in the table
        for (int i = 0; i < size; ++i) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;  
            }
        }
    }
    
    // Hash function h(k) = (2k + 3) % size
    int hashFunction(int key) const {
        return (2 * key + 3) % size;
    }

    void insert(int key) {
        int index = hashFunction(key);  
        Node* newNode = new Node(key); 

        // Insert the new node at the beginning of the linked list for the bucket
        newNode->next = table[index];
        table[index] = newNode;

        std::cout << "Inserted " << key << " in bucket " << index << std::endl;
    }

    void displayHash() const {
        for (int i = 0; i < size; ++i) {
            std::cout << "Bucket " << i << ": ";
            Node* current = table[i];
            while (current != nullptr) {
                std::cout << current->data << " ";
                current = current->next;
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
    hashTable.displayHash();

    return 0;
}
