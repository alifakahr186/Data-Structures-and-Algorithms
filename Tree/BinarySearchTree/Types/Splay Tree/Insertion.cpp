#include <iostream>

struct Node {
    int key;
    Node* left;
    Node* right;
};

Node* createNode(int key) {
    Node* newNode = new Node();
    newNode->key = key;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
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

Node* splay(Node* root, int key) {
    if (root == nullptr || root->key == key) {
        return root;
    }

    if (root->key > key) {
        if (root->left == nullptr) {
            return root;
        }
        if (root->left->key > key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        } 
        else if (root->left->key < key) {
            root->left->right = splay(root->left->right, key);
            
            if (root->left->right != nullptr) {
                root->left = leftRotate(root->left);
            }
        }

        return (root->left == nullptr) ? root : rightRotate(root);
    } 
    
    else {
        if (root->right == nullptr) {
            return root;
        }
        if (root->right->key > key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != nullptr) {
                root->right = rightRotate(root->right);
            }
        } else if (root->right->key < key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }

        return (root->right == nullptr) ? root : leftRotate(root);
    }
}

Node* insert(Node* root, int key) {
    if (root == nullptr) {
        return createNode(key);
    }

    root = splay(root, key);

    if (root->key == key) {
        return root;
    }

    Node* newNode = createNode(key);

    if (root->key > key) {
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

void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        std::cout << root->key << " ";
        inorder(root->right);
    }
}

int main() {
    Node* root = nullptr;
    int elements[] = {25, 18, 30, 10, 40, 12, 35, 22, 45, 9, 21, 50};
    int size = sizeof(elements) / sizeof(elements[0]);

    for (int i = 0; i < size; ++i) {
        root = insert(root, elements[i]);
    }

    std::cout << "Inorder traversal of the splay tree after insertions: ";
    inorder(root);
    std::cout << std::endl;

    return 0;
}