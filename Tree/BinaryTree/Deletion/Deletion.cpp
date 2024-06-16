#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
};

Node* createNode() {
    int x;
    Node* newNode = new Node();
    
    cout << "Enter data (-1 for no node): ";
    cin >> x;

    if (x == -1) {
        return nullptr;
    }

    newNode->data = x;
    cout << "Enter left child of " << x << ": ";
    newNode->left = createNode();
    cout << "Enter right child of " << x << ": ";
    newNode->right = createNode();

    return newNode;
}

// Function to delete a binary tree
void deleteTree(Node* node) {
    if (node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);

    cout << "Deleting node with data: " << node->data << endl;
    delete node;
}

int main() {
    Node* root = nullptr;
    cout << "Creating the binary tree.\n";
    root = createNode();

    // Perform operations with the tree...

    // Deleting the tree when done
    deleteTree(root);
    root = nullptr; // Optional: Set root to nullptr after deletion

    return 0;
}
