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
        color = RED;  // New nodes are red by default
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

    void rotateLeft(Node*& root, Node* x) {
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
    }

    void rotateRight(Node*& root, Node* y) {
        Node* x = y->left;
        y->left = x->right;

        if (x->right != nullptr) {
            x->right->parent = y;
        }

        x->parent = y->parent;

        if (y->parent == nullptr) {
            root = x;
        } else if (y == y->parent->right) {
            y->parent->right = x;
        } else {
            y->parent->left = x;
        }

        x->right = y;
        y->parent = x;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    void fixDoubleBlack(Node*& root, Node* x) {
        if (x == root) return;

        Node* sibling;
        if (x->parent->left == x) {
            sibling = x->parent->right;  // x is the left child, so the sibling is the right child
        } else {
            sibling = x->parent->left;   // x is the right child, so the sibling is the left child
        }
        Node* parent = x->parent;

        // Case III: If the DB's sibling is black and both its children are black
        if (sibling == nullptr) {
            fixDoubleBlack(root, parent);
        } 
        
        else if (sibling->color == RED) {
            // Case IV: If the DB's sibling is red
            sibling->color = BLACK;
            parent->color = RED;
            if (sibling == parent->left) {
                rotateRight(root, parent);  // Rotate to restore Red-Black properties
            } else {
                rotateLeft(root, parent);   // Rotate to restore Red-Black properties
            }
            fixDoubleBlack(root, x);  // Re-apply cases to the new tree configuration.
        } 
        
        else {
            if ((sibling->left == nullptr || sibling->left->color == BLACK) && 
                (sibling->right == nullptr || sibling->right->color == BLACK)) {
                // Case III: Sibling's children are black, recolor and move problem up
                sibling->color = RED;
                if (parent->color == BLACK) {
                    fixDoubleBlack(root, parent);  // Move double black up
                } else {
                    parent->color = BLACK;  // If the parent is red, recolor to black
                }
            } else {
                // Case VI: If the DB's sibling is black and its far child is red
                if (sibling == parent->left && (sibling->left != nullptr && sibling->left->color == RED)) {
                    sibling->left->color = sibling->color;
                    sibling->color = parent->color;
                    rotateRight(root, parent);  // Right rotation to restore balance
                } else if (sibling == parent->right && (sibling->right != nullptr && sibling->right->color == RED)) {
                    sibling->right->color = sibling->color;
                    sibling->color = parent->color;
                    rotateLeft(root, parent);  // Left rotation to restore balance
                }
                parent->color = BLACK;
            }
        }
    }

    Node* deleteNodeHelper(Node*& root, Node* node, int data) {
        if (node == nullptr) return node;

        if (data < node->data) {
            node->left = deleteNodeHelper(root, node->left, data);
        } else if (data > node->data) {
            node->right = deleteNodeHelper(root, node->right, data);
        } else {
            // Node found, now handle deletion
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = (node->left) ? node->left : node->right;

                // Case I: If the node to be deleted is red, simply delete it
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }

                delete temp;
            } else {
                // Node has two children, find in-order successor
                Node* temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = deleteNodeHelper(root, node->right, temp->data);
            }
        }

        if (node == nullptr) return node;

        // Case II: If the root becomes double black, remove double black by recoloring the root
        if (node->color == BLACK) {
            fixDoubleBlack(root, node);  // Fix double black if it exists
        }

        return node;
    }

public:
    RedBlackTree() {
        root = nullptr;
    }

    void insert(int data) {
        Node* newNode = new Node(data);
        root = bstInsert(root, newNode);
        redblackTreeInsertFixup(root, newNode);
    }

    void deleteNode(int data) {
        root = deleteNodeHelper(root, root, data);
    }

    void inorderTraversal() {
        inorderTraversalHelper(root);
        cout << endl;
    }

    void inorderTraversalHelper(Node* root) {
        if (root == nullptr) return;

        inorderTraversalHelper(root->left);
        cout << root->data << " ";
        inorderTraversalHelper(root->right);
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

    tree.deleteNode(40);

    cout << "In-order traversal after deletion: ";
    tree.inorderTraversal();

    return 0;
}
