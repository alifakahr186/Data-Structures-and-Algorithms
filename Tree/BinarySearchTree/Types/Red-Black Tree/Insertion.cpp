#include <iostream>
using namespace std;

enum Color { RED, BLACK };

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node* parent;
    Color color;

    Node(int value) {
        data = value;
        left = right = parent = nullptr;
        color = RED;  // Correct way to initialize color
    }
};

class RedBlackTree {
private:
    Node* root;

    Node* bstInsert(Node* root, Node* newNode) {
        if (root == nullptr) {
            return newNode;
        }

        if (newNode->data < root->data) {
            root->left = bstInsert(root->left, newNode);
            root->left->parent = root;
        } else if (newNode->data > root->data) {
            root->right = bstInsert(root->right, newNode);
            root->right->parent = root;
        }

        return root;
    }

    void redblackTreeInsertFixup(Node*& root, Node* newNode) {
        while (newNode->parent != nullptr && newNode->parent->color == RED) {
            Node* parent = newNode->parent;
            Node* grandparent = parent->parent;

            if (parent == grandparent->left) {
                Node* uncle = grandparent->right;

                if (uncle != nullptr && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    newNode = grandparent;
                } else {
                    if (newNode == parent->right) {
                        newNode = parent;
                        rotateLeft(root, newNode);
                    }

                    parent->color = BLACK;
                    grandparent->color = RED;
                    rotateRight(root, grandparent);
                }
            } else {
                Node* uncle = grandparent->left;

                if (uncle != nullptr && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    newNode = grandparent;
                } else {
                    if (newNode == parent->left) {
                        newNode = parent;
                        rotateRight(root, newNode);
                    }

                    parent->color = BLACK;
                    grandparent->color = RED;
                    rotateLeft(root, grandparent);
                }
            }
        }

        root->color = BLACK;
    }

    Node* rotateLeft(Node*& root, Node* x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left != nullptr) {
            y->left->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;

        return root;
    }

    Node* rotateRight(Node*& root, Node* y) {
        Node* x = y->left;
        y->left = x->right;

        if (x->right != nullptr) {
            x->right->parent = y;
        }

        x->parent = y->parent;

        if (y->parent == nullptr) {
            root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }

        x->right = y;
        y->parent = x;

        return root;
    }

    void inorderTraversal(Node* root) {
        if (root == nullptr) {
            return;
        }

        inorderTraversal(root->left);
        std::cout << root->data << " ";
        inorderTraversal(root->right);
    }

public:
    // Constructor to initialize root to nullptr
    RedBlackTree() {
        root = nullptr;
    }

    void insert(int value) {
        Node* newNode = new Node(value);  
        root = bstInsert(root, newNode);
        redblackTreeInsertFixup(root, newNode);
    }

    void inorderTraversal() {
        inorderTraversal(root);
        cout << endl;
    }
};

int main() {
    RedBlackTree tree;

    int arr[] = {10, 18, 7, 15, 16, 30, 25, 40, 60, 2, 1, 70};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        tree.insert(arr[i]);
    }

    cout << "In-order traversal of the Red-Black tree: ";
    tree.inorderTraversal();

    return 0;
}
