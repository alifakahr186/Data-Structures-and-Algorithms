#include<iostream>

const int MAX_KEYS = 4; // Maximum number of keys in a node
const int MAX_CHILDREN = MAX_KEYS + 1; // Maximum number of children for a node

struct BTreeNode {
    int keys[MAX_KEYS]; // Array to hold keys
    BTreeNode* children[MAX_CHILDREN]; // Array to hold child nodes
    int numKeys; // Number of keys currently in the node
    bool isLeaf; // Flag indicating if the node is a leaf node
};

BTreeNode* createNode() {
    BTreeNode* newNode = new BTreeNode(); // Allocate memory for a new node
    newNode->numKeys = 0; // Initialize number of keys to zero
    newNode->isLeaf = true; // Set the new node as a leaf node

    // Initialize keys and children pointers in the new node
    for (int i = 0; i < MAX_KEYS; ++i) {
        newNode->keys[i] = 0; // Initialize keys with zero
        newNode->children[i] = nullptr; // Initialize child pointers to nullptr
    }

    newNode->children[MAX_KEYS] = nullptr; // Initialize the last child pointer to nullptr
    return newNode; // Return the newly created node
}

// Function to split a child node
void splitChild(BTreeNode* parentNode, int index, BTreeNode* childNode) {
    // Create a new child node
    BTreeNode* newChild = createNode();
    newChild->isLeaf = childNode->isLeaf;
    newChild->numKeys = MAX_KEYS / 2;

    // Copy keys to the new child node
    for (int i = 0; i < MAX_KEYS / 2; ++i) {
        newChild->keys[i] = childNode->keys[i + MAX_KEYS / 2];
    }

    // Copy children to the new child node if it's not a leaf node
    if (!childNode->isLeaf) {
        for (int i = 0; i < MAX_CHILDREN / 2; ++i) {
            newChild->children[i] = childNode->children[i + MAX_CHILDREN / 2];
        }
    }

    childNode->numKeys = MAX_KEYS / 2; // Update number of keys in the original child node

    // Rearrange parent's pointers to children nodes
    for (int i = parentNode->numKeys; i >= index + 1; --i) {
        parentNode->children[i + 1] = parentNode->children[i];
    }

    parentNode->children[index + 1] = newChild; // Insert the new child node in the parent

    // Rearrange parent's keys
    for (int i = parentNode->numKeys - 1; i >= index; --i) {
        parentNode->keys[i + 1] = parentNode->keys[i];
    }

    parentNode->keys[index] = childNode->keys[MAX_KEYS / 2]; // Update parent's key
    ++parentNode->numKeys; // Increment number of keys in the parent node
}

// Function to insert a key into a non-full node
void insertNonFull(BTreeNode* node, int key) {
    int i = node->numKeys - 1;

    if (node->isLeaf) {
        // Shift keys to make space for the new key
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            --i;
        }

        node->keys[i + 1] = key; // Insert the new key
        ++node->numKeys; // Increment the number of keys

    } else {
        // Find the appropriate child to insert the key
        while (i >= 0 && key < node->keys[i]) {
            --i;
        }

        // If the child is full, split it and potentially adjust index
        if (node->children[i + 1]->numKeys == MAX_KEYS) {
            splitChild(node, i + 1, node->children[i + 1]);
            if (key > node->keys[i + 1]) {
                ++i;
            }
        }
        insertNonFull(node->children[i + 1], key); // Recursively insert into the appropriate child
    }
}

// Function to insert a key into the B-tree
BTreeNode* insert(BTreeNode* root, int key) {
    if (root == nullptr) {
        // If the tree is empty, create a new root with the key
        root = createNode();
        root->keys[0] = key;
        root->numKeys = 1;

    } else {

        if (root->numKeys == MAX_KEYS) {
            // If the root is full, create a new root, split the old root, and insert appropriately
            BTreeNode* newRoot = createNode();
            newRoot->isLeaf = false;
            newRoot->children[0] = root;
            splitChild(newRoot, 0, root);
            int i = 0;

            // Determine the child to insert the key
            if (newRoot->keys[0] < key) {
                ++i;
            } 

            insertNonFull(newRoot->children[i], key);
            root = newRoot; // Update the root pointer

        } else {
            insertNonFull(root, key); // Insert into the non-full root
        }
    
    }

    return root; // Return the updated root
}

//DELETION
// Function to find the predecessor of a key in the tree
int getPredecessor(BTreeNode* node) {
    while (!node->isLeaf) {
        node = node->children[node->numKeys];
    }
    return node->keys[node->numKeys - 1];
}

// Function to find the successor of a key in the tree
int getSuccessor(BTreeNode* node) {
    while (!node->isLeaf) {
        node = node->children[0];
    }
    return node->keys[0];
}

// Function to borrow a key from the previous child of the node
void borrowFromPrev(BTreeNode* node, int idx) {
    BTreeNode* child = node->children[idx];
    BTreeNode* sibling = node->children[idx - 1];

    for (int i = child->numKeys - 1; i >= 0; --i) {
        child->keys[i + 1] = child->keys[i];
    }

    if (!child->isLeaf) {
        for (int i = child->numKeys; i >= 0; --i) {
            child->children[i + 1] = child->children[i];
        }
    }

    child->keys[0] = node->keys[idx - 1];

    if (!node->isLeaf) {
        child->children[0] = sibling->children[sibling->numKeys];
    }

    node->keys[idx - 1] = sibling->keys[sibling->numKeys - 1];

    child->numKeys += 1;
    sibling->numKeys -= 1;
}

// Function to borrow a key from the next child of the node
void borrowFromNext(BTreeNode* node, int idx) {
    BTreeNode* child = node->children[idx];
    BTreeNode* sibling = node->children[idx + 1];

    child->keys[child->numKeys] = node->keys[idx];

    if (!child->isLeaf) {
        child->children[child->numKeys + 1] = sibling->children[0];
    }

    node->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->numKeys; ++i) {
        sibling->keys[i - 1] = sibling->keys[i];
    }

    if (!sibling->isLeaf) {
        for (int i = 1; i <= sibling->numKeys; ++i) {
            sibling->children[i - 1] = sibling->children[i];
        }
    }

    child->numKeys += 1;
    sibling->numKeys -= 1;
}

// Function to merge a node with its sibling
void merge(BTreeNode* node, int idx) {
    BTreeNode* child = node->children[idx];
    BTreeNode* sibling = node->children[idx + 1];

    child->keys[MAX_KEYS / 2] = node->keys[idx];

    for (int i = 0; i < sibling->numKeys; ++i) {
        child->keys[i + (MAX_KEYS / 2) + 1] = sibling->keys[i];
    }

    if (!child->isLeaf) {
        for (int i = 0; i <= sibling->numKeys; ++i) {
            child->children[i + (MAX_KEYS / 2) + 1] = sibling->children[i];
        }
    }

    for (int i = idx + 1; i < node->numKeys; ++i) {
        node->keys[i - 1] = node->keys[i];
    }

    for (int i = idx + 2; i <= node->numKeys; ++i) {
        node->children[i - 1] = node->children[i];
    }

    child->numKeys += sibling->numKeys + 1;
    node->numKeys--;

    delete sibling;
}

// Recursive function to delete a key from the tree
BTreeNode* deleteKey(BTreeNode* node, int key) {
    if (node == nullptr) {
        return node;
    }

    int idx = 0;
    while (idx < node->numKeys && key > node->keys[idx]) {
        idx++;
    }

    if (idx < node->numKeys && key == node->keys[idx]) {
        if (node->isLeaf) {
            for (int i = idx + 1; i < node->numKeys; ++i) {
                node->keys[i - 1] = node->keys[i];
            }
            node->numKeys--;
        } else {
            if (node->children[idx]->numKeys >= (MAX_KEYS + 1) / 2) {
                int pred = getPredecessor(node->children[idx]);
                node->keys[idx] = pred;
                node->children[idx] = deleteKey(node->children[idx], pred);
            } else if (node->children[idx + 1]->numKeys >= (MAX_KEYS + 1) / 2) {
                int succ = getSuccessor(node->children[idx + 1]);
                node->keys[idx] = succ;
                node->children[idx + 1] = deleteKey(node->children[idx + 1], succ);
            } else {
                merge(node, idx);
                node->children[idx] = deleteKey(node->children[idx], key);
            }
        }
    } else {
        bool flag = (idx == node->numKeys);

        if (node->children[idx]->numKeys < (MAX_KEYS + 1) / 2) {
            if (idx > 0 && node->children[idx - 1]->numKeys >= (MAX_KEYS + 1) / 2) {
                borrowFromPrev(node, idx);
            } else if (idx < node->numKeys && node->children[idx + 1]->numKeys >= (MAX_KEYS + 1) / 2) {
                borrowFromNext(node, idx);
            } else {
                if (idx < node->numKeys) {
                    merge(node, idx);
                } else {
                    merge(node, idx - 1);
                }
            }
        }

        if (flag && idx > node->numKeys) {
            node->children[idx - 1] = deleteKey(node->children[idx - 1], key);
        } else {
            node->children[idx] = deleteKey(node->children[idx], key);
        }
    }

    return node;
}

// Function to delete a key from the B-tree
BTreeNode* deleteKeyFromBTree(BTreeNode* root, int key) {
    if (root == nullptr) {
        return root;
    }

    root = deleteKey(root, key);

    if (root->numKeys == 0) {
        BTreeNode* temp = root;
        if (root->isLeaf) {
            root = nullptr;
        } else {
            root = root->children[0];
        }
        delete temp;
    }

    return root;
}

// Function to perform inorder traversal of the B-tree
void inorderTraversal(BTreeNode* node) {
    if (node != nullptr) {
        int i;
        for (i = 0; i < node->numKeys; ++i) {
            if (!node->isLeaf) {
                inorderTraversal(node->children[i]); // Traverse child node
            }
            std::cout << node->keys[i] << " "; // Print keys
        }

        if (!node->isLeaf) {
            inorderTraversal(node->children[i]); // Traverse last child node
        }
    }
}

// Main function
int main() {
    BTreeNode* root = nullptr; // Initialize root node as null pointer
    int arr[] = {9, 15, 8, 34, 28, 17, 11, 2, 1, 3, 10, 14, 25, 7, 18, 5, 29, 19};
    int arrSize = sizeof(arr) / sizeof(arr[0]); // Calculate array size

    // Insert keys into the B-tree
    for (int i = 0; i < arrSize; ++i) {
        root = insert(root, arr[i]);
    }

    // Print inorder traversal of the B-tree
    std::cout << "Inorder traversal of the constructed B-tree is:\n";
    inorderTraversal(root);

    int keyToDelete = 15; // Key you want to delete
    root = deleteKeyFromBTree(root, keyToDelete);

    // Print inorder traversal of the B-tree after deletion
    std::cout << "\n\nInorder traversal after deleting " << keyToDelete << ":\n";
    inorderTraversal(root);

    return 0;
}