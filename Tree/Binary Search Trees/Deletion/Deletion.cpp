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

    Node* findMin(Node* root)
    {
        while (root->left != NULL)
        {
            root = root->left;
        }

        return root;
    }

    Node* deleteNode(Node* root, int value)
    {
        if (root == NULL)
        {
            return NULL;
        }

        if (value < root->data)
        {
            root->left = deleteNode(root->left, value);
        }
        else if (value > root->data)
        {
            root->right = deleteNode(root->right, value);
        }
        else
        {
            // Leaf Node
            if (root->left == NULL && root->right == NULL)
            {
                delete root;
                return NULL;
            }

            // Only Right Child
    
            else if (root->left == NULL)
            {
                Node* temp = root->right;
                delete root;
                return temp;
            }

            // Only Left Child
            else if (root->right == NULL)
            {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            // Two Children
            else
            {
                Node* temp = findMin(root->right);

                root->data = temp->data;

                root->right = deleteNode(root->right, temp->data);
            }
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


    void Delete(int value)
    {
        root = deleteNode(root, value);
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

    for (int key : keys)
    {
        tree.Insert(key);
    }

    cout << "Inorder Traversal Before Deletion: ";
    tree.Inorder();

    int value;
    cout << "\nEnter the node value to delete: ";
    cin >> value;

    tree.Delete(value);

    cout << "\nInorder Traversal After Deletion: ";
    tree.Inorder();

    return 0;
}