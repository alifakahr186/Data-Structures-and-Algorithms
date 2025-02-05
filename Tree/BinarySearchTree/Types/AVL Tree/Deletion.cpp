#include <iostream>
#include <algorithm>

using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int value) {
        data = value;
        left = right = nullptr;
        height = 1;  // Initial height of a node is 1 (leaf node)
    }
};

class AVLTree {
private:
    Node* root;

    int getHeight(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    void updateHeight(Node* node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    int getBalance(Node* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* insert(Node* node, int key) {
        if (node == nullptr)
            return new Node(key);

        if (key < node->data)
            node->left = insert(node->left, key);
        else if (key > node->data)
            node->right = insert(node->right, key);
        else
            return node;  // Duplicate keys not allowed

        updateHeight(node);
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && key < node->left->data)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->data)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* node, int key) {
        if (node == nullptr)
            return node;

        if (key < node->data)
            node->left = deleteNode(node->left, key);
        else if (key > node->data)
            node->right = deleteNode(node->right, key);
        else {
            // Node with only one child or no child
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;

                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else
                    *node = *temp;

                delete temp;
            } else {
                //Find the inorder successor
                Node* temp = minValueNode(node->right);

                // Copy the inorder successor's data to this node
                node->data = temp->data;

                // Delete the inorder successor
                node->right = deleteNode(node->right, temp->data);
            }
        }

        if (node == nullptr)
            return node;

        updateHeight(node);
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);

        // Left Right Case
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);

        // Right Left Case
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorderTraversal(Node* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }

public:
    // Constructor to initialize root to nullptr
    AVLTree() {
        root = nullptr;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void deleteNode(int key) {
        root = deleteNode(root, key);
    }

    void inorderTraversal() {
        inorderTraversal(root);
        cout << endl;
    }
};

int main() {
    AVLTree tree;

    int arr[] = {28, 14, 15, 18, 2, 3, 7, 9, 12};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        tree.insert(arr[i]);
    }

    cout << "In-order traversal of the AVL tree: ";
    tree.inorderTraversal();

    tree.deleteNode(9);

    cout << "In-order traversal after deletion: ";
    tree.inorderTraversal();

    return 0;
}
