#include <iostream>
#include <algorithm>

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;

    // Constructor to initialize the values
    Node(int data) : data(data), left(nullptr), right(nullptr), height(1) {}
};

Node* createNode(int data) {
    Node* newNode = new Node(data);
    return newNode;
}

int height(Node* r) {
    if (r == NULL)
        return -1;
    else {
        /* compute the height of each subtree */
        int lheight = height(r->left);
        int rheight = height(r->right);

        /* use the larger one */
        if (lheight > rheight)
            return (lheight + 1);
        else return (rheight + 1);
    }
}

void updateHeight(Node* node) {
    node->height = 1 + std::max(height(node->left), height(node->right));
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

Node* insert(Node* root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }

    if (key < root->data) {
        root->left = insert(root->left, key);
    } else if (key > root->data) {
        root->right = insert(root->right, key);
    } else {
        return root;  // Duplicate keys are not allowed
    }

    updateHeight(root);

    int balance = height(root->left) - height(root->right);

    // Left Heavy
    if (balance > 1) {
        if (key < root->left->data)
            return rightRotate(root);
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }

    // Right Heavy
    if (balance < -1) {
        if (key > root->right->data)
            return leftRotate(root);
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == nullptr)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);

    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    
    else {
        if (root->left == nullptr || root->right == nullptr) {
        
            Node* temp;
            if (root->left != nullptr) {
                temp = root->left;
                
            } else {
                temp = root->right;
            }

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } 

            else
                *root = *temp;
                delete temp;
            }

        else {
            Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == nullptr)
        return root;

    updateHeight(root);

    int balance = height(root->left) - height(root->right);

    // Left Heavy
    if (balance > 1) {
        if (height(root->left->left) >= height(root->left->right))
            return rightRotate(root);
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }

    // Right Heavy
    if (balance < -1) {
        if (height(root->right->right) >= height(root->right->left))
            return leftRotate(root);
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

// Function to print the tree in-order
void inOrderTraversal(Node* root) {
    if (root == nullptr)
        return;
    inOrderTraversal(root->left);
    std::cout << root->data << " ";
    inOrderTraversal(root->right);
}

int main() {
    int arr[] = {12, 3, 9, 4, 6, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    Node* root = nullptr;

    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
    }

    std::cout << "In-order traversal of the AVL tree: ";
    inOrderTraversal(root);
    std::cout << std::endl;

    // Delete node with value 9
    root = deleteNode(root, 9);

    std::cout << "In-order traversal after deletion: ";
    inOrderTraversal(root);

    return 0;
}
