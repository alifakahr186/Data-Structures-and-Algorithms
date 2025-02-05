#include <iostream>
#include <limits>

using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    // Constructor to initialize the node with data and nullptr children
    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
private:
    Node* root;

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
                if (x == -1) { // Check for no node condition
                    return nullptr;
                }
                break; // Valid input received, exit the loop
            }
        }

        Node* newNode = new Node(x);
        
        // Recursively creating left and right children
        cout << "Enter left child of " << x << ": ";
        newNode->left = createNode();

        cout << "Enter right child of " << x << ": ";
        newNode->right = createNode();

        return newNode;
    }

public:
    // Constructor initializes an empty tree
    BinaryTree() {
        root = nullptr;
    }

    // Public function to start the tree creation
    void createTree() {
        cout << "Creating the binary tree.\n";
        root = createNode();
    }

    // Function to return the root node (optional)
    Node* getRoot() {
        return root;
    }

    // Destructor to free up memory when the tree is destroyed
    ~BinaryTree() {
        deleteTree(root);
    }

    void deleteTree(Node* node) {
        if (node == nullptr) {
            return;
        }
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

};

int main() {
    BinaryTree tree;  // Create a tree object
    tree.createTree();  // Create the binary tree through user input

    return 0;
}
