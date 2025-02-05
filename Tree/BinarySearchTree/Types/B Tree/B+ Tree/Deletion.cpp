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
        for (int i = 0; i < MAX_KEYS; ++i) {
            data[i] = 0;
            children[i] = nullptr;
        }
        children[MAX_KEYS - 1] = nullptr;
    }
};

class BPlustree {
private:
    Node* root;

    Node* createNode() {
        return new Node();
    }

    void splitChild(Node* parentNode, int index, Node* childNode) {
        Node* newChild = createNode();
        newChild->isLeaf = childNode->isLeaf;
        newChild->numKeys = MAX_KEYS / 2;

        for (int i = 0; i < MAX_KEYS / 2; ++i) {
            newChild->data[i] = childNode->data[i + MAX_KEYS / 2];
        }

        if (!childNode->isLeaf) {
            for (int i = 0; i < MAX_CHILDREN / 2; ++i) {
                newChild->children[i] = childNode->children[i + MAX_CHILDREN / 2];
            }
        }

        childNode->numKeys = MAX_KEYS / 2;

        for (int i = parentNode->numKeys; i >= index + 1; --i) {
            parentNode->children[i + 1] = parentNode->children[i];
        }

        parentNode->children[index + 1] = newChild;

        for (int i = parentNode->numKeys - 1; i >= index; --i) {
            parentNode->data[i + 1] = parentNode->data[i];
        }

        parentNode->data[index] = childNode->data[MAX_KEYS / 2];
        ++parentNode->numKeys;
    }

    void insertNonFull(Node* node, int key) {
        int i = node->numKeys - 1;

        if (node->isLeaf) {
            while (i >= 0 && key < node->data[i]) {
                if (i >= 0 && node->data[i] == key) {
                    return; 
            }
                node->data[i + 1] = node->data[i];
                --i;
            }

            node->data[i + 1] = key;
            ++node->numKeys;

        } else {
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

    int getPredecessor(Node* node) {
        while (!node->isLeaf) {
            node = node->children[node->numKeys];
        }
        return node->data[node->numKeys - 1];
    }

    int getSuccessor(Node* node) {
        while (!node->isLeaf) {
            node = node->children[0];
        }
        return node->data[0];
    }

    void borrowFromPrev(Node* node, int idx) {
        Node* child = node->children[idx];
        Node* sibling = node->children[idx - 1];

        for (int i = child->numKeys - 1; i >= 0; --i) {
            child->data[i + 1] = child->data[i];
        }

        if (!child->isLeaf) {
            for (int i = child->numKeys; i >= 0; --i) {
                child->children[i + 1] = child->children[i];
            }
        }

        child->data[0] = node->data[idx - 1];

        if (!node->isLeaf) {
            child->children[0] = sibling->children[sibling->numKeys];
        }

        node->data[idx - 1] = sibling->data[sibling->numKeys - 1];

        child->numKeys += 1;
        sibling->numKeys -= 1;
    }

    void borrowFromNext(Node* node, int idx) {
        Node* child = node->children[idx];
        Node* sibling = node->children[idx + 1];

        child->data[child->numKeys] = node->data[idx];

        if (!child->isLeaf) {
            child->children[child->numKeys + 1] = sibling->children[0];
        }

        node->data[idx] = sibling->data[0];

        for (int i = 1; i < sibling->numKeys; ++i) {
            sibling->data[i - 1] = sibling->data[i];
        }

        if (!sibling->isLeaf) {
            for (int i = 1; i <= sibling->numKeys; ++i) {
                sibling->children[i - 1] = sibling->children[i];
            }
        }

        child->numKeys += 1;
        sibling->numKeys -= 1;
    }

    void merge(Node* node, int idx) {
        Node* child = node->children[idx];
        Node* sibling = node->children[idx + 1];

        // Move the key from parent down into the child
        child->data[MAX_KEYS / 2] = node->data[idx];

        for (int i = 0; i < sibling->numKeys; ++i) {
            child->data[i + (MAX_KEYS / 2) + 1] = sibling->data[i];
        }

        if (!child->isLeaf) {
            for (int i = 0; i <= sibling->numKeys; ++i) {
                child->children[i + (MAX_KEYS / 2) + 1] = sibling->children[i];
            }
        }
        
        // Move keys in the parent to fill the gap created by moving a parent key down
        for (int i = idx + 1; i < node->numKeys; ++i) {
            node->data[i - 1] = node->data[i];
        }

        for (int i = idx + 2; i <= node->numKeys; ++i) {
            node->children[i - 1] = node->children[i];
        }

        child->numKeys += sibling->numKeys + 1;
        node->numKeys--;

        delete sibling;
    }

    Node* deleteKey(Node* node, int key) {
        if (node == nullptr) {
            return node;
        }
        //Find the index where the key is located
        int idx = 0;
        while (idx < node->numKeys && key > node->data[idx]) {
            idx++;
        }
        // If the key is in this node
        if (idx < node->numKeys && key == node->data[idx]) {
            // Shift keys in the node to the left to fill the gap created by the deleted key
            if (node->isLeaf) {
                for (int i = idx + 1; i < node->numKeys; ++i) {
                    node->data[i - 1] = node->data[i];
                    node->data[i] = parentNode->data[idx]; 
                }
                node->numKeys--;
            } else {
                // If the child before the key (left child) has enough keys, find the predecessor
                if (node->children[idx]->numKeys >= (MAX_KEYS + 1) / 2) {
                    int pred = getPredecessor(node->children[idx]);
                    node->data[idx] = pred;
                    node->children[idx] = deleteKey(node->children[idx], pred);
                } 
                // If the child after the key (right child) has enough keys, find the successor
                else if (node->children[idx + 1]->numKeys >= (MAX_KEYS + 1) / 2) {
                    int succ = getSuccessor(node->children[idx + 1]);
                    node->data[idx] = succ;
                    node->children[idx + 1] = deleteKey(node->children[idx + 1], succ);
                } 
                // If neither child has enough keys, merge the two children and delete the key from the merged node
                else {
                    merge(node, idx);
                    node->children[idx] = deleteKey(node->children[idx], key);
                }
            }
        } else {
            // Check if the key is in the last child
            bool flag = (idx == node->numKeys);
            
            // If the child where the key is supposed to exist has less than the minimum number of keys
            // Than we borrow from prev or borrow from next node
            // Otherwise, if not found merge with either previous or next sibling
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

    Node* deleteKeyFromBTree(Node* root, int key) {
        if (root == nullptr) {
            return root;
        }

        root = deleteKey(root, key);

        if (root->numKeys == 0) {
            Node* temp = root;
            if (root->isLeaf) {
                root = nullptr;
            } else {
                root = root->children[0];
            }
            delete temp;
        }

        return root;
    }

    void inorder(Node* node) {
        if (node != nullptr) {
            int i;
            for (i = 0; i < node->numKeys; ++i) {
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
    BPlustree() {
        root = nullptr;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void deleteKeyFromBTree(int key) {
        root = deleteKeyFromBTree(root, key);
    }

    void inorderTraversal() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    BPlustree bplustree;
    int arr[] = {9, 15, 8, 34, 28, 17, 11, 2, 1, 3, 10, 14, 25, 7, 18, 5, 12};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < arrSize; ++i) {
        bplustree.insert(arr[i]);
    }

    std::cout << "Inorder traversal of the constructed B-tree is:\n";
    bplustree.inorderTraversal();

    bplustree.deleteKeyFromBTree(14);

    cout << "Inorder traversal of the B-tree after deletion:\n";
    bplustree.inorderTraversal();

    return 0;
}
