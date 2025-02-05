#include <iostream>
#include <algorithm>

using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    int rank;

    Node(int value) {
        data = value;
        left = right = nullptr;
        rank = 0;  // Initial rank of a leaf node is 0
    }
};

// WAVL Tree class
class WAVLTree {
private:
    Node* root;

    // Helper function to get the rank of a node (returns -1 for null nodes)
    int getRank(Node* node) {
        if (node == nullptr)
            return -1;
        return node->rank;
    }

    // Helper function to update the rank of a node based on its children
    void updateRank(Node* node) {
        if (node == nullptr) return;
        node->rank = 1 + max(getRank(node->left), getRank(node->right));
    }

    Node* rotateRight(Node* node) {
        Node* leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;
        updateRank(node);
        updateRank(leftChild);
        return leftChild;
    }

    Node* rotateLeft(Node* node) {
        Node* rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;
        updateRank(node);
        updateRank(rightChild);
        return rightChild;
    }

    Node* fixRankViolations(Node* node) {
        if (node == nullptr)
            return node;

        int leftRank = getRank(node->left);
        int rightRank = getRank(node->right);

        // Case 1: Left-left imbalance -> Right rotation
        if (leftRank - rightRank == 2) {
            if (getRank(node->left->left) >= getRank(node->left->right)) {
                node = rotateRight(node); 
            } else {
                node->left = rotateLeft(node->left);  
                node = rotateRight(node);             
            }
        }

        // Case 2: Right-right imbalance -> Left rotation
        if (rightRank - leftRank == 2) {
            if (getRank(node->right->right) >= getRank(node->right->left)) {
                node = rotateLeft(node);  
            } else {
                node->right = rotateRight(node->right);  
                node = rotateLeft(node);                 
            }
        }

        updateRank(node);
        return node;
    }

    Node* insert(Node* node, int key) {
        if (node == nullptr)
            return new Node(key);

        if (key < node->data)
            node->left = insert(node->left, key);
        else if (key > node->data)
            node->right = insert(node->right, key);
        else
            return node;  // Duplicate keys not allowed

        node = fixRankViolations(node);

        return node;
    }

    void inorderTraversal(Node* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }

public:
    // Constructor to initialize the root to nullptr
    WAVLTree() {
        root = nullptr;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void inorderTraversal() {
        inorderTraversal(root);
        cout << endl;
    }
};

int main() {
    WAVLTree tree;

    int arr[] = {10, 5, 15, 3, 8, 12, 18, 7, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        tree.insert(arr[i]);
    }

    cout << "In-order traversal before deletion: ";
    tree.inorderTraversal();

    return 0;
}
