#include <iostream>
#include <vector>

struct Node {
    int data;
    Node* next;

    Node(int d) : data(d), next(nullptr) {}  // Constructor to initialize a new node
};

class HashTable {
private:
    std::vector<Node*> table;  // Using vector to handle the table
    int size;

public:
    HashTable(int size) : size(size) {  // Constructor to initialize hash table
        table.resize(size, nullptr);
    }

    ~HashTable() {  // Destructor to clean up the linked lists
        for (int i = 0; i < size; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* prev = current;
                current = current->next;
                delete prev;
            }
        }
    }

    void insert(int key) {
        int index = hashFunction(key);
        Node* newNode = new Node(key);

        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            Node* current = table[index];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    int hashFunction(int key) {  // Simple modulus-based hash function
        return key % size;
    }

    void displayHash() {
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
    int size = 10;  // Size of the Hash Table

    HashTable hashTable(size);

    for (int key : arr) {
        hashTable.insert(key);
    }

    hashTable.displayHash();

    return 0;
}
