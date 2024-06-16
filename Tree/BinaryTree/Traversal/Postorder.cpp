#include<iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

void postorder(Node* root);

void postorder(Node* root) {
    if (root == nullptr) {
        return;
    }

    std::cout << root->data << " ";
    postorder(root->left);
    postorder(root->right);
}

int main() {
    Node* root = nullptr; // Initialize root node

    cout << "Postorder is ";
    postorder(root);

    return 0;
}
