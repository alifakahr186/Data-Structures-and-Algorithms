#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    int key;
    Node *left, *right;
    int height;
    int size;

    // Constructor to initialize the node with data and nullptr children
    Node(int k) {
        key = k;
        left = right = nullptr;
        height = 1;
        size = 1;
    }
};

class ScapegoatTree {
public:
    Node* root;
    double alpha;  // Balance factor, typically 2/3

    ScapegoatTree(double alpha = 2.0 / 3.0) {
        root = nullptr;
        this->alpha = alpha;
    }

    int getHeight(Node* node) {
        return (node == nullptr) ? 0 : node->height;
    }

    void updateHeight(Node* node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    //Calculate the size of a node's subtree
    int getSize(Node* node) {
        return (node == nullptr) ? 0 : node->size;
    }

    void updateSize(Node* node) {
        node->size = 1 + getSize(node->left) + getSize(node->right);
    }

    Node* insertBST(Node* root, int key) {
        if (root == nullptr) return new Node(key);

        if (key < root->key)
            root->left = insertBST(root->left, key);
        else if (key > root->key)
            root->right = insertBST(root->right, key);

        updateHeight(root);
        updateSize(root);
        return root;
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* deleteNode(Node* root, int key) {
        if (root == nullptr) return root;

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

        updateHeight(root);
        updateSize(root);
        return root;
    }

    void inorderTraversal(Node* root, vector<Node*>& nodeList) {
        if (root == nullptr) return;
        inorderTraversal(root->left, nodeList);
        nodeList.push_back(root);
        inorderTraversal(root->right, nodeList);
    }

    Node* buildBalancedTree(vector<Node*>& nodeList, int start, int end) {
        if (start > end) return nullptr;

        int mid = start + (end - start) / 2;
        Node* root = nodeList[mid];
        root->left = buildBalancedTree(nodeList, start, mid - 1);
        root->right = buildBalancedTree(nodeList, mid + 1, end);

        updateHeight(root);
        updateSize(root);
        return root;
    }

    Node* findScapegoat(Node* root, Node* newNode) {
        while (root) {
            if (getSize(root->left) > alpha * getSize(root) || getSize(root->right) > alpha * getSize(root)) {
                return root;
            }
            root = (newNode->key < root->key) ? root->left : root->right;
        }
        return nullptr;
    }

    Node* insert(Node* root, int key) {
        root = insertBST(root, key);  
        Node* scapegoat = findScapegoat(this->root, root);

        if (scapegoat != nullptr) {
            vector<Node*> nodeList;
            inorderTraversal(scapegoat, nodeList);
            Node* newSubtree = buildBalancedTree(nodeList, 0, nodeList.size() - 1);

            if (root == this->root) {
                this->root = newSubtree;  
            }
        }
        return root;
    }

    Node* deleteAndBalance(Node* root, int key) {
        root = deleteNode(root, key);
        Node* scapegoat = findScapegoat(this->root, root);

        if (scapegoat != nullptr) {
            vector<Node*> nodeList;
            inorderTraversal(scapegoat, nodeList);
            Node* newSubtree = buildBalancedTree(nodeList, 0, nodeList.size() - 1);

            if (root == this->root) {
                this->root = newSubtree;  
            }
        }
        return root;
    }

    // In-order traversal to print the tree
    void inorderTraversal(Node* root) {
        if (root != nullptr) {
            inorderTraversal(root->left);
            cout << root->key << " ";
            inorderTraversal(root->right);
        }
    }
};

int main() {
    ScapegoatTree tree; 
    int keys[] = {10, 6, 14, 5, 25, 15, 8, 11, 18};

    // Insert the keys into the tree
    for (int key : keys) {
        tree.root = tree.insert(tree.root, key);
    }

    cout << "Inorder traversal of the Scapegoat Tree after insertion: ";
    tree.inorderTraversal(tree.root);
    cout << endl;

    tree.root = tree.deleteAndBalance(tree.root, 14);
    
    cout << "Inorder traversal of the Scapegoat Tree after deletion: ";
    tree.inorderTraversal(tree.root);
    cout << endl;

    return 0;
}
