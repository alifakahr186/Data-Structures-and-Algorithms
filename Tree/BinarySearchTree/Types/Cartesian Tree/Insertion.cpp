#include <iostream>
#include <vector>

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

class CartesianTree {
public:
    Node* root;

    CartesianTree() {
        root = nullptr;
    }

    // Inserting a node into the Cartesian Tree Using Max-Heap and BST
    Node* insert(Node* root, int key) {
        if (root == nullptr) return new Node(key);
        
        if (key > root->key) {
            Node* newNode = new Node(key);    
            newNode->left = root;             
            return newNode;                   
        }
        
        root->right = insert(root->right, key);
        
        return root;
    }

    void insert(int key) {
        root = insert(root, key); 
    }

    void inorderTraversal(Node* root) {
        if (root != nullptr) {
            inorderTraversal(root->left);  
            cout << root->key << " ";      
            inorderTraversal(root->right); 
        }
    }
};

int main() {
    CartesianTree tree; 
    vector<int> keys = {10, 6, 14, 5, 8, 11, 18};

    for (int key : keys) {
        tree.insert(key);
    }

    cout << "Inorder traversal of the Cartesian Tree: ";
    tree.inorderTraversal(tree.root);
    cout << endl;

    return 0;
}
