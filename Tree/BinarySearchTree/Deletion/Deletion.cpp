#include <iostream>

using namespace std;

class Node {
public:
    int key;
    Node *left, *right;
    
    // Constructor to initialize the node with data and nullptr children
    Node(int k) {
        key = k;
        left = right = nullptr;
    }
};

class BinaryTree {
public:
    Node* root;

    BinaryTree() {
        root = nullptr;
    }

    Node* insert(Node* root, int key) {
        if (root == nullptr) return new Node(key);

        if (key < root->key) 
            root->left = insert(root->left, key);
        else if (key > root->key) 
            root->right = insert(root->right, key);

        return root;
    }

    Node* findMin(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* deleteNode(Node* root, int key) {
        if (root == nullptr) return root;

        if (key < root->key) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->key) {
            root->right = deleteNode(root->right, key);
        } else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            // Find the inorder successor
            Node* temp = findMin(root->right);
            root->key = temp->key; 
            root->right = deleteNode(root->right, temp->key);  
        }
        return root;
    }

    void inorderTraversal(Node* root) {
        if (root != nullptr) {
            inorderTraversal(root->left);
            std::cout << root->key << " ";
            inorderTraversal(root->right);
        }
    }
};

int main() {
    BinaryTree tree;  
    int keys[] = {10, 6, 14, 5, 8, 11, 18};

    // Insert the keys into the tree
    for (int key : keys) {
        tree.root = tree.insert(tree.root, key);
    }

    std::cout << "Inorder traversal of the BST before deletion: ";
    tree.inorderTraversal(tree.root);
    std::cout << std::endl;

    int keyToDelete = 6;
    tree.root = tree.deleteNode(tree.root, keyToDelete);

    std::cout << "Inorder traversal of the BST after deleting " << keyToDelete << ": ";
    tree.inorderTraversal(tree.root);
    std::cout << std::endl;

    return 0;
}
