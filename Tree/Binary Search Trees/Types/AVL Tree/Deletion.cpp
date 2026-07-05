#include <iostream>
#include <algorithm>
using namespace std;

class Tree
{
public:
    int data;
    int height;

    Tree* left;
    Tree* right;

    Tree(int value)
    {
        data = value;
        height = 1;

        left = nullptr;
        right = nullptr;
    }
};


class AVL
{
private:

    Tree* root;

    int height(Tree* node)
    {
        if(node == nullptr)
            return 0;

        return node->height;
    }

    int balanceFactor(Tree* node)
    {
        if(node == nullptr)
            return 0;

        return height(node->left) - height(node->right);
    }

    Tree* rightRotation(Tree* y)
    {
        Tree* x = y->left;
        Tree* T2 = x->right;

        // Rotation
        x->right = y;
        y->left = T2;

        // Update Heights
        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    }


    Tree* leftRotation(Tree* x)
    {
        Tree* y = x->right;
        Tree* T2 = y->left;

        y->left = x;
        x->right = T2;

        // Update Heights
        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }

    Tree* insertNode(Tree* node, int value)
    {
        if(node == nullptr)
        {
            return new Tree(value);
        }

        if(value < node->data)
        {
            node->left = insertNode(node->left, value);
        }
        else if(value > node->data)
        {
            node->right = insertNode(node->right, value);
        }
        else
        {
            // Duplicate values are not allowed
            return node;
        }

        // Update Height
        node->height = 1 + max(height(node->left),
                               height(node->right));

        int balance = balanceFactor(node);

        // LL 
        if(balance > 1 && value < node->left->data)
        {
            return rightRotation(node);
        }

        // RR 
        if(balance < -1 && value > node->right->data)
        {
            return leftRotation(node);
        }

        // LR 
        if(balance > 1 && value > node->left->data)
        {
            node->left = leftRotation(node->left);

            return rightRotation(node);
        }


        // RL 
        if(balance < -1 && value < node->right->data)
        {
            node->right = rightRotation(node->right);

            return leftRotation(node);
        }

        return node;
    }

        Tree* minValueNode(Tree* node)
    {
        Tree* current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    Tree* deleteNode(Tree* node, int value)
    {
        if (node == nullptr)
            return node;

        if (value < node->data)
        {
            node->left = deleteNode(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = deleteNode(node->right, value);
        }
        else
        {
            if (node->left == nullptr || node->right == nullptr)
            {
                Tree* temp;

                if (node->left != nullptr)
                    temp = node->left;
                else
                    temp = node->right;

                if (temp == nullptr)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                {
                    *node = *temp;
                }

                delete temp;
            }
            else
            {
                Tree* temp = minValueNode(node->right);

                node->data = temp->data;

                node->right = deleteNode(node->right, temp->data);
            }
        }

        if (node == nullptr)
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = balanceFactor(node);

        // LL Case
        if (balance > 1 && balanceFactor(node->left) >= 0)
            return rightRotation(node);

        // LR Case
        if (balance > 1 && balanceFactor(node->left) < 0)
        {
            node->left = leftRotation(node->left);
            return rightRotation(node);
        }

        // RR Case
        if (balance < -1 && balanceFactor(node->right) <= 0)
            return leftRotation(node);

        // RL Case
        if (balance < -1 && balanceFactor(node->right) > 0)
        {
            node->right = rightRotation(node->right);
            return leftRotation(node);
        }

        return node;
    }

    void inorder(Tree* node)
    {
        if(node == nullptr)
            return;

        inorder(node->left);

        cout << node->data << " ";

        inorder(node->right);
    }

    void destroy(Tree* node)
    {
        if(node == nullptr)
            return;

        destroy(node->left);
        destroy(node->right);

        delete node;
    }

public:

    AVL()
    {
        root = nullptr;
    }

    ~AVL()
    {
        destroy(root);
    }


    void insert(int value)
    {
        root = insertNode(root, value);
    }

    void remove(int value)
    {
        root = deleteNode(root, value);
    }

    void inorder()
    {
        cout << "Inorder : ";
        inorder(root);
        cout << endl;
    }

};


int main()
{
    AVL tree;

    int n;

    cout << "How many values do you want to insert : ";
    cin >> n;

    cout << endl;

    for(int i = 0; i < n; i++)
    {
        int value;

        cout << "Enter Value " << i + 1 << " : ";
        cin >> value;

        tree.insert(value);
    }

    cout << endl;

    tree.inorder();

    int value;
    cout << "\nEnter the node value to delete: ";
    cin >> value;

    tree.remove(value);

    cout << "\nInorder Traversal After Deletion: ";
    tree.inorder();


    return 0;
}