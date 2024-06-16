#include<iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

void preorder(Node* root);

void preorder(Node* root) {
    if (root == nullptr) {
        return;
    }

    std::cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

int main() {
    Node* root = nullptr; // Initialize root node

    cout << "Preorder is ";
    preorder(root);

    return 0;
}
