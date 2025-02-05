#include <iostream>
#include <vector>
using namespace std;

const int MAX_KEYS = 5; 
const int MAX_CHILDREN = MAX_KEYS + 1; 

class Node {
public:
    int data[MAX_KEYS]; 
    Node* children[MAX_CHILDREN]; 
    int numKeys; 
    bool isLeaf; 
    Node* next;  // Pointer to the next leaf node for linked list

    Node() {
        numKeys = 0;
        isLeaf = true;
        next = nullptr;
        for (int i = 0; i < MAX_KEYS; ++i) {
            data[i] = 0;
            children[i] = nullptr;
        }
        children[MAX_KEYS] = nullptr;
    }
};

class BPlusTree {
private:
    Node* root;

    Node* createNode() {
        return new Node();
    }

    void splitChild(Node* parentNode, int index, Node* childNode) {
        Node* newChild = createNode();
        newChild->isLeaf = childNode->isLeaf;
        newChild->numKeys = MAX_KEYS / 2;

        // Move second half of data to newChild
        for (int i = 0; i < MAX_KEYS / 2; ++i) {
            newChild->data[i] = childNode->data[i + MAX_KEYS / 2];
        }

        if (!childNode->isLeaf) {
            for (int i = 0; i <= MAX_KEYS / 2; ++i) {
                newChild->children[i] = childNode->children[i + MAX_KEYS / 2];
            }
        } else {
            // For leaf nodes, link newChild to childNode and update the linked list
            newChild->next = childNode->next;
            childNode->next = newChild;
        }

        childNode->numKeys = MAX_KEYS / 2;

        // Shift parent's children and data to make room for newChild
        for (int i = parentNode->numKeys; i > index; --i) {
            parentNode->children[i + 1] = parentNode->children[i];
            parentNode->data[i] = parentNode->data[i - 1];
        }

        parentNode->children[index + 1] = newChild;
        parentNode->data[index] = childNode->data[MAX_KEYS / 2];
        ++parentNode->numKeys;
    }

    void insertNonFull(Node* node, int key) {
        int i = node->numKeys - 1;

        if (node->isLeaf) {
            // Insert into leaf node
            while (i >= 0 && key < node->data[i]) {
                node->data[i + 1] = node->data[i];
                --i;
            }
            node->data[i + 1] = key;
            ++node->numKeys;

        } else {
            // Navigate to the correct child
            while (i >= 0 && key < node->data[i]) {
                --i;
            }

            if (node->children[i + 1]->numKeys == MAX_KEYS) {
                splitChild(node, i + 1, node->children[i + 1]);
                if (key > node->data[i + 1]) {
                    ++i;
                }
            }
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
                newRoot->isLeaf = false;
                newRoot->children[0] = root;
                splitChild(newRoot, 0, root);
                int i = 0;
                if (newRoot->data[0] < key) {
                    ++i;
                }
                insertNonFull(newRoot->children[i], key);
                root = newRoot;
            } else {
                insertNonFull(root, key);
            }
        }
        return root;
    }

    void inorderLeafTraversal(Node* node) {
        // Traverse through leaf nodes in a linked list manner
        while (node != nullptr) {
            for (int i = 0; i < node->numKeys; ++i) {
                cout << node->data[i] << " ";
            }
            node = node->next;  // Move to the next leaf node
        }
    }

public:
    BPlusTree() {
        root = nullptr;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void inorderTraversal() {
        if (root == nullptr) return;
        
        // Find the leftmost leaf
        Node* node = root;
        while (!node->isLeaf) {
            node = node->children[0];
        }
        inorderLeafTraversal(node);
        cout << endl;
    }
};

int main() {
    BPlusTree btree;
    int arr[] = {9, 15, 8, 34, 28, 17, 11, 2, 1, 3, 10, 14, 25, 7, 18, 5, 29, 19};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < arrSize; ++i) {
        btree.insert(arr[i]);
    }

    cout << "Inorder traversal of the constructed B+ tree is:\n";
    btree.inorderTraversal();
    return 0;
}
