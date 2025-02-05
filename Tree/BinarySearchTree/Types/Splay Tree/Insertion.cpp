#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = right = nullptr;
    }
};

class SplayTree {
private:
    Node* root;

    Node* createNode(int key) {
        return new Node(key);
    }

    Node* bstInsert(Node* root, int key) {
        if (root == nullptr) {
            return createNode(key);
        }

        root = splay(root, key); 

        if (root->data == key) {
            return root; // Key already exists
        }

        Node* newNode = createNode(key); 

        if (root->data > key) {
            newNode->right = root;
            newNode->left = root->left;
            root->left = nullptr;
        } else {
            newNode->left = root;
            newNode->right = root->right;
            root->right = nullptr;
        }

        return newNode;
    }

    Node* splay(Node* root, int key) {
        if (root == nullptr || root->data == key) {
            return root;
        }

        // For the left subtree
        if (root->data > key) {
            if (root->left == nullptr) {
                return root;
            }
            // Zig-Zig (Left Left)
            if (root->left->data > key) {
                root->left->left = splay(root->left->left, key);
                root = rightRotate(root);
            }
            // Zig-Zag (Left Right)
            else if (root->left->data < key) {
                root->left->right = splay(root->left->right, key);
                if (root->left->right != nullptr) {
                    root->left = leftRotate(root->left);
                }
            }

            return (root->left == nullptr) ? root : rightRotate(root);
        }
        // For the right subtree
        else {
            if (root->right == nullptr) {
                return root;
            }
            // Zig-Zag (Right Left)
            if (root->right->data > key) {
                root->right->left = splay(root->right->left, key);
                if (root->right->left != nullptr) {
                    root->right = rightRotate(root->right);
                }
            }
            // Zig-Zig (Right Right)
            else if (root->right->data < key) {
                root->right->right = splay(root->right->right, key);
                root = leftRotate(root);
            }

            return (root->right == nullptr) ? root : leftRotate(root);
        }
    }

    Node* rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    void inorder(Node* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << root->data << " ";
            inorder(root->right);
        }
    }

public:
    // Constructor to initialize root to nullptr
    SplayTree() {
        root = nullptr;
    }

    void insert(int key) {
        root = bstInsert(root, key);
    }

    void inorderTraversal() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    SplayTree tree;
    
    int elements[] = {25, 18, 30, 10, 40, 12, 35, 22, 45, 9, 21, 50};
    int size = sizeof(elements) / sizeof(elements[0]);

    for (int i = 0; i < size; i++) {
        tree.insert(elements[i]);
    }

    cout << "In-order traversal of the Splay Tree: ";
    tree.inorderTraversal();

    return 0;
}
