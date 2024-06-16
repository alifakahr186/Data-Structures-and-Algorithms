#include <iostream>

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }

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
    if (root == nullptr) {
        return root;
    }

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

int main() {
    Node* root = nullptr;
    int keys[] = {10, 6, 14, 5, 8, 11, 18};

    for (int key : keys) {
        root = insert(root, key);
    }

    std::cout << "Inorder traversal of the BST before deletion: ";
    inorderTraversal(root);
    std::cout << std::endl;

    int keyToDelete = 6;
    root = deleteNode(root, keyToDelete);

    std::cout << "Inorder traversal of the BST after deleting " << keyToDelete << ": ";
    inorderTraversal(root);
    std::cout << std::endl;

    return 0;
}
