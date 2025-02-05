#include <iostream>
#include <limits>

using namespace std;

class Node {
public:
    int data;
    Node *left, *right;
    
    // Constructor to initialize the node with data and nullptr children
    Node(int value) {
        data = value;
        left = right = nullptr;
    }
};

class BinaryTree {
public:
    Node* root;

    BinaryTree() {
        root = nullptr;
    }

    Node* createNode() {
        int x;
        cout << "Enter data (-1 for no node): ";

        while (true) { 
            cin >> x;
            if (cin.fail()) { 
                cin.clear(); 
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
                cout << "Invalid input. Please enter an integer: ";
            } else {
                if (x == -1) { 
                    return nullptr;
                }
                break; 
            }
        }

        Node* newNode = new Node(x);

        cout << "Enter left child of " << x << ": ";
        newNode->left = createNode();

        cout << "Enter right child of " << x << ": ";
        newNode->right = createNode();

        return newNode;
    }

    void inorderTraversal(Node* node) {
        if (node == nullptr) {
            return;
        }

        inorderTraversal(node->left);
        cout << node->data << " ";
        inorderTraversal(node->right);
    }

};

int main() {
    BinaryTree tree;

    cout << "Creating the binary tree.\n";
    tree.root = tree.createNode();

    cout << "Inorder traversal: ";
    tree.inorderTraversal(tree.root);

    return 0;
}
