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

int main() {
    Node* root = nullptr;
    cout << "Creating the binary tree.\n";
    root = createNode();

    return 0;
}
