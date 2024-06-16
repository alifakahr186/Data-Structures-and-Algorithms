#include<iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

void inorder(Node* root);

void inorder(Node* root) {
    if (root == nullptr) {
        return;
    }

    inorder(root->left);
    std::cout << root->data << " ";
    inorder(root->right);
}

int main() {
    Node* root = nullptr; // Initialize root node

    cout << "Inorder is ";
    inorder(root);

    return 0;
}
