#include <iostream>
#include <vector>
using namespace std;

class HashTable {
private:
    struct Node {
        int key;  
        int next;  
    };

    vector<Node> table; 
    int size;           
    int neighborhood;  

    bool isEmpty(int index) {
        return table[index].key == -1;
    }

public:
    HashTable(int size, int neighborhood) {
        this->size = size;
        this->neighborhood = neighborhood;
        table.resize(size, {-1, -1}); // Initialize all slots as empty (-1)
    }
    
    // Hash function: h(k) = k % size
    int hashFunction(int key) {
        return key % size;
    }

    void insert(int key) {
        int homeIndex = hashFunction(key);

        // Try to insert at the home index first
        if (isEmpty(homeIndex)) {
            table[homeIndex].key = key;
            cout << "Inserted " << key << " at index " << homeIndex << endl;
        } else {
            // If the home index is occupied, check within the neighborhood
            bool inserted = false;
            int startIdx = homeIndex;

            for (int i = 0; i < neighborhood; i++) {
                // We will try to insert into the next slot in the neighborhood range
                int idx = (startIdx + i) % size;

                if (isEmpty(idx)) {
                    table[idx].key = key;
                    cout << "Inserted " << key << " at index " << idx << endl;
                    inserted = true;
                    break;
                } else {
                    // Collision occurs, so we need to "hop" the existing key
                    int displacedKey = table[idx].key;
                    table[idx].key = key;

                    // Move the displaced key one slot forward in the neighborhood
                    startIdx = (startIdx + 1) % size;  // Move to the next slot
                    key = displacedKey;
                    cout << "Hopped key " << displacedKey << " from index " << idx << " to index " << startIdx << endl;
                }
            }

            // If no available slot was found within the neighborhood, the table is full
            if (!inserted) {
                cout << "Hash table is full. Could not insert key: " << key << endl;
            }
        }
    }

    void display() {
        for (int i = 0; i < size; ++i) {
            cout << "Index " << i << ": ";
            if (isEmpty(i)) {
                cout << "Empty";
            } else {
                cout << table[i].key;
            }
            cout << endl;
        }
    }
};

int main() {
    std::vector<int> arr = {10, 15, 26, 30, 25, 35, 45}; 
    int size = 10;  
    int neighborhood = 4;  

    HashTable hashTable(size, neighborhood);

    for (int key : arr) {
        hashTable.insert(key);
    }

    cout << "\nFinal Hash Table:" << endl;
    hashTable.display();

    return 0;
}
