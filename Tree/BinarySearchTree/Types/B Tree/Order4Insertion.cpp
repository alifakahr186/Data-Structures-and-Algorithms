#include <iostream>
using namespace std;

const int MAX_KEYS = 4; 
const int MAX_CHILDREN = MAX_KEYS + 1;  

class Node {
public:
    int data[MAX_KEYS];  
    Node* children[MAX_CHILDREN]; 
    int numKeys; 
    bool isLeaf;  

    Node() {
        numKeys = 0;  
        isLeaf = true;  
        // Initialize all key and child pointer slots to 0/null
        for (int i = 0; i < MAX_KEYS; ++i) {
            data[i] = 0;
            children[i] = nullptr;
        }
        children[MAX_KEYS] = nullptr;  // Initialize the last child pointer
    }
};

class BTree {
private:
    Node* root;  

    Node* createNode() {
        return new Node(); 
    }

    // Split a full child node into two and promote a key to the parent
    void splitChild(Node* parentNode, int index, Node* childNode) {
        Node* newChild = createNode();  // Create a new node for splitting
        newChild->isLeaf = childNode->isLeaf;  // Copy the leaf status
        newChild->numKeys = MAX_KEYS / 2;  // Half the keys go to the new node

        // Copy the second half of childNode's keys to newChild
        for (int i = 0; i < MAX_KEYS / 2; ++i) {
            newChild->data[i] = childNode->data[i + MAX_KEYS / 2];
        }

        // If the childNode is not a leaf, copy its children to the newChild
        if (!childNode->isLeaf) {
            for (int i = 0; i < MAX_CHILDREN / 2; ++i) {
                newChild->children[i] = childNode->children[i + MAX_CHILDREN / 2];
            }
        }

        // Reduce the number of keys in childNode
        childNode->numKeys = MAX_KEYS / 2;

        // Shift children of the parentNode to make space for the newChild
        for (int i = parentNode->numKeys; i >= index + 1; --i) {
            parentNode->children[i + 1] = parentNode->children[i];
        }

        // Link newChild as a child of parentNode
        parentNode->children[index + 1] = newChild;

        // Shift parent's keys to make space for the key to be promoted
        for (int i = parentNode->numKeys - 1; i >= index; --i) {
            parentNode->data[i + 1] = parentNode->data[i];
        }

        // Promote the middle key from childNode to parentNode
        parentNode->data[index] = childNode->data[MAX_KEYS / 2];
        ++parentNode->numKeys; 
    }

    // Insert a key when the node is non-full
    void insertNonFull(Node* node, int key) {
        int i = node->numKeys - 1;  // Start inserting from the last node of key

        if (node->isLeaf) {
            // Check if the key already exists in the current node
            for (int j = 0; j < node->numKeys; ++j) {
                if (node->data[j] == key) {
                    cout << "Key " << key << " is already present, not inserting duplicate." << endl;
                    return;
                }
            }
            // Find the location to insert the new key
            while (i >= 0 && key < node->data[i]) {
                node->data[i + 1] = node->data[i]; 
                --i;
            }

            // Insert the new key
            node->data[i + 1] = key;
            ++node->numKeys;  // Update the key count

        } else { 
            while (i >= 0 && key < node->data[i]) {
                --i;
            }
            // Check if the child is full before recursing
            if (node->children[i + 1]->numKeys == MAX_KEYS) {
                splitChild(node, i + 1, node->children[i + 1]);  // Split the full child
                // After the split, determine which child to go down
                if (key > node->data[i + 1]) {
                    ++i;
                }
            }
            // Recur into the appropriate child
            insertNonFull(node->children[i + 1], key);
        }
    }

    Node* insert(Node* root, int key) {
        if (root == nullptr) {
            root = createNode(); 
            root->data[0] = key; 
            root->numKeys = 1;  
        } else {
            if (root->numKeys == MAX_KEYS) {
                Node* newRoot = createNode();  
                newRoot->isLeaf = false;  // The new root is not a leaf
                newRoot->children[0] = root;  // Make the old root its child
                splitChild(newRoot, 0, root);  // Split the old root

                // Decide whether to insert the key in the left or right child
                int i = 0;
                if (newRoot->data[0] < key) {
                    ++i;
                }

                insertNonFull(newRoot->children[i], key);  
                root = newRoot;  // Now root update

            } else {
                insertNonFull(root, key);
            }
        }
        return root; 
    }

    void inorder(Node* node) {
        if (node != nullptr) {
            int i;
            for (int i = 0; i < node->numKeys; ++i) {
                if (!node->isLeaf) {
                    inorder(node->children[i]); 
                }
                std::cout << node->data[i] << " ";
            }
            if (!node->isLeaf) {
                inorder(node->children[i]);
            }
        }
    }

public:
    // Constructor to initialize root to nullptr
    BTree() {
        root = nullptr; 
    }

    void insert(int key) {
        root = insert(root, key);  
    }

    void inorderTraversal() {
        inorder(root);  
        cout << endl;  
    }
};

int main() {
    BTree btree; 
    int arr[] = {5, 3, 21, 9, 1, 13, 2, 7, 10, 12, 4, 8}; 
    int arrSize = sizeof(arr) / sizeof(arr[0]);  

    for (int i = 0; i < arrSize; ++i) {
        btree.insert(arr[i]);
    }

    std::cout << "Inorder traversal of the constructed B-tree is:\n";
    btree.inorderTraversal();  

    return 0;  
}
