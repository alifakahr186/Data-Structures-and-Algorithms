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

// Function to construct BST from postorder traversal
Node* constructBSTFromPostorder(int postorder[], int size) {
    if (size == 0) {
        return nullptr;
    }

    Node* root = newNode(postorder[size - 1]);
    int i;

    for (i = size - 2; i >= 0; --i) {
        if (postorder[i] < root->data) {
            break;
        }
    }

    root->right = constructBSTFromPostorder(postorder + i + 1, size - i - 1);
    root->left = constructBSTFromPostorder(postorder, i + 1);

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
    int postorder[] = {5, 17, 19, 18, 16, 70, 85, 60, 20, 20};
    int size = sizeof(postorder) / sizeof(postorder[0]);

    Node* root = constructBSTFromPostorder(postorder, size);

    std::cout << "Inorder traversal of constructed BST: ";
    inorderTraversal(root);
    std::cout << std::endl;

    return 0;
}
