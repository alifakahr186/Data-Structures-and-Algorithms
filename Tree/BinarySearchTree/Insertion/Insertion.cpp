#include <iostream>

struct Node {
    int key;
    Node* left;
    Node* right;
    
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

// Function to insert a new node with a given key
Node* insert(Node* root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    return root;
}

// Function to perform inorder traversal of the BST
void inorderTraversal(Node* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        std::cout << root->key << " ";
        inorderTraversal(root->right);
    }
}

int main() {
    Node* root = nullptr;
    int keys[] = {10, 6, 14, 5, 8, 11, 18};

    for (int key : keys) {
        root = insert(root, key);
    }

    std::cout << "Inorder traversal of the BST: ";
    inorderTraversal(root);
    std::cout << std::endl;

    return 0;
}
