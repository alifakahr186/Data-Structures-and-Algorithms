#include <iostream>

enum Color { RED, BLACK };

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* parent;
    Color color;

    Node(int value) : data(value), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};

Node* createNode(int value) {
    return new Node(value);
}

Node* bstInsert(Node* root, Node* newNode);
void redblackTreeInsertFixup(Node*& root, Node* newNode);
Node* rotateLeft(Node* root, Node* x);
Node* rotateRight(Node* root, Node* y);

Node* insert(Node*& root, int value) {
    Node* newNode = createNode(value);

    root = bstInsert(root, newNode);
    redblackTreeInsertFixup(root, newNode);

    return root;
}

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
                    root = rotateLeft(root, newNode);
                }

                parent->color = BLACK;
                grandparent->color = RED;
                root = rotateRight(root, grandparent);
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
                    root = rotateRight(root, newNode);
                }

                parent->color = BLACK;
                grandparent->color = RED;
                root = rotateLeft(root, grandparent);
            }
        }
    }

    root->color = BLACK;
}

Node* rotateLeft(Node* root, Node* x) {
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

Node* rotateRight(Node* root, Node* y) {
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

// Function to print the tree in-order
void inOrderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }

    inOrderTraversal(root->left);
    std::cout << root->data << " ";
    inOrderTraversal(root->right);
}

int main() {
    int arr[] = {14, 17, 11, 7, 53, 4, 13, 12, 8, 60, 19, 16, 20};
    int n = sizeof(arr) / sizeof(arr[0]);

    Node* root = nullptr;

    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
    }

    std::cout << "In-order traversal of the Red-Black tree: ";
    inOrderTraversal(root);

    return 0;
}