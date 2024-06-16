#include <iostream>

// Define the structure for a node in the BST
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Function to create a new node
Node* newNode(int data) {
    Node* temp = new Node;
    temp->data = data;
    temp->left = temp->right = nullptr;
    return temp;
}

// Function to insert nodes into the BST
Node* insert(Node* root, int data) {
    if (root == nullptr) {
        return newNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

// Function to construct BST from preorder traversal
Node* constructBSTFromPreorder(int preorder[], int size) {
    if (size == 0) {
        return nullptr;
    }

    Node* root = nullptr;

    for (int i = 0; i < size; ++i) {
        root = insert(root, preorder[i]);
    }

    return root;
}

// Function to perform inorder traversal of BST
void inorderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }

    inorderTraversal(root->left);
    std::cout << root->data << " ";
    inorderTraversal(root->right);
}

int main() {
    int preorder[] = {20, 16, 5, 18, 17, 19, 20, 60, 85, 70};
    int size = sizeof(preorder) / sizeof(preorder[0]);

    Node* root = constructBSTFromPreorder(preorder, size);

    std::cout << "Inorder traversal of constructed BST: ";
    inorderTraversal(root);
    std::cout << std::endl;

    return 0;
}
