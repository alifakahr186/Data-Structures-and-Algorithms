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

    // Merging two subtrees for maintaining the heap property after deletion
    Node* merge(Node* leftSubtree, Node* rightSubtree) {
        if (!leftSubtree) return rightSubtree;
        if (!rightSubtree) return leftSubtree;
        
        if (leftSubtree->key > rightSubtree->key) {
            leftSubtree->right = merge(leftSubtree->right, rightSubtree);
            return leftSubtree;
        } else {
            rightSubtree->left = merge(leftSubtree, rightSubtree->left);
            return rightSubtree;
        }
    }

    Node* deleteNode(Node* root, int key) {
        if (root == nullptr) return nullptr;

        if (key < root->key) {
            root->left = deleteNode(root->left, key);   
        } else if (key > root->key) {
            root->right = deleteNode(root->right, key); 
        } else {
            Node* temp = root;
            root = merge(root->left, root->right);
            delete temp;  
        }
        return root;
    }

    void deleteKey(int key) {
        root = deleteNode(root, key);
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

    tree.deleteKey(14);
    
    cout << "Inorder traversal after deleting 14: ";
    tree.inorderTraversal(tree.root);
    cout << endl;

    return 0;
}
