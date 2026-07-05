#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node* left;
    Node* right;

    Node(int value)
    {
        data = value;
        left = NULL;
        right = NULL;
    }
};

class BST
{
private:
    Node* insert(Node* root, int value)
    {
        if (root == NULL)
        {
            return new Node(value);
        }

        if (value < root->data)
        {
            root->left = insert(root->left, value);
        }
        else if (value > root->data)
        {
            root->right = insert(root->right, value);
        }

        return root;
    }

    void inorder(Node* root)
    {
        if (root != NULL)
        {
            inorder(root->left);
            cout << root->data << " ";
            inorder(root->right);
        }
    }

public:

    Node* root;

    BST()
    {
        root = NULL;
    }

    void Insert(int value)
    {
        root = insert(root, value);
    }

    void Inorder()
    {
        inorder(root);
        cout << endl;
    }

};

int main()
{
    BST tree;

    int keys[] = {10, 6, 14, 5, 8, 11, 18};

    // Insert the keys into the BST
    for (int key : keys)
    {
        tree.Insert(key);
    }

    cout << "Inorder Traversal of BST: ";
    tree.Inorder();

    return 0;
}
