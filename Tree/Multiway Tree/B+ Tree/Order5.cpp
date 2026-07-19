#include <iostream>
using namespace std;

static const int m = 5;
static const int n = m - 1;

class Node
{
public:
    int key[n];
    int keyCount;
    Node* child[m];
    bool isLeaf;
    Node* next;        // ← Linked list pointer for leaf nodes

    Node()
    {
        keyCount = 0;
        isLeaf = true;
        next = nullptr;
        for (int i = 0; i < m; i++)
            child[i] = nullptr;
    }
};

class BPlusTree
{
private:
    Node* root;

    void splitChild(Node* parent, int index)
    {
        Node* left = parent->child[index];
        Node* right = new Node();

        right->isLeaf = left->isLeaf;
        right->keyCount = n / 2;

        // Copy second half keys
        for (int i = 0; i < n / 2; i++)
        {
            right->key[i] = left->key[i + (n / 2) + 1];
        }

        // If internal node, copy children
        if (!left->isLeaf)
        {
            for (int i = 0; i <= n / 2; i++)
            {
                right->child[i] = left->child[i + (n / 2) + 1];
            }
        }

        left->keyCount = n / 2 + 1;   // Middle key stays in left (B+ Tree)

        // Link the leaves
        if (left->isLeaf)
        {
            right->next = left->next;
            left->next = right;
        }

        // Shift parent's children
        for (int i = parent->keyCount; i >= index + 1; i--)
        {
            parent->child[i + 1] = parent->child[i];
        }

        parent->child[index + 1] = right;

        // Shift parent's keys
        for (int i = parent->keyCount - 1; i >= index; i--)
        {
            parent->key[i + 1] = parent->key[i];
        }

        // Promote middle key (copy up)
        parent->key[index] = left->key[n / 2];
        parent->keyCount++;
    }

    void insertNonFull(Node* node, int value)
    {
        int i = node->keyCount - 1;

        if (node->isLeaf)
        {
            while (i >= 0 && value < node->key[i])
            {
                node->key[i + 1] = node->key[i];
                i--;
            }
            node->key[i + 1] = value;
            node->keyCount++;
        }
        else
        {
            while (i >= 0 && value < node->key[i])
                i--;
            i++;

            if (node->child[i]->keyCount == n)
            {
                splitChild(node, i);

                if (value > node->key[i])
                    i++;
            }
            insertNonFull(node->child[i], value);
        }
    }

    Node* Insert(Node* rootNode, int value)
    {
        if (rootNode == nullptr)
        {
            Node* newNode = new Node();
            newNode->key[0] = value;
            newNode->keyCount = 1;
            return newNode;
        }

        if (rootNode->keyCount == n)
        {
            Node* newRoot = new Node();
            newRoot->isLeaf = false;
            newRoot->child[0] = rootNode;

            splitChild(newRoot, 0);

            int i = 0;
            if (value > newRoot->key[0])
                i++;

            insertNonFull(newRoot->child[i], value);
            return newRoot;
        }
        else
        {
            insertNonFull(rootNode, value);
            return rootNode;
        }
    }

    void inorder(Node* node)
    {
        if (node == nullptr) return;

        for (int i = 0; i < node->keyCount; i++)
        {
            if (!node->isLeaf)
                inorder(node->child[i]);

            if (node->isLeaf)
                cout << node->key[i] << " ";
        }
        if (!node->isLeaf)
            inorder(node->child[node->keyCount]);
    }

    // Print all leaves using linked list (B+ Tree style)
    void printLeaves()
    {
        if (root == nullptr) return;
        
        Node* curr = root;
        // Go to leftmost leaf
        while (!curr->isLeaf)
            curr = curr->child[0];

        cout << "Leaf Nodes (Linked List): ";
        while (curr != nullptr)
        {
            for (int i = 0; i < curr->keyCount; i++)
                cout << curr->key[i] << " ";
            curr = curr->next;
        }
        cout << endl;
    }

public:
    BPlusTree() : root(nullptr) {}

    void insert(int value)
    {
        root = Insert(root, value);
    }

    void inorderTraversal()
    {
        inorder(root);
        cout << endl;
    }

    void printLeafLinkedList()
    {
        printLeaves();
    }
};

int main()
{
    BPlusTree tree;

    int total;
    cout << "How many values do you want to insert: ";
    cin >> total;

    for (int i = 0; i < total; i++)
    {
        int value;
        cout << "Enter Value " << i + 1 << ": ";
        cin >> value;
        tree.insert(value);
    }

    cout << "\nInorder Traversal (B+ Tree):\n";
    tree.inorderTraversal();

    cout << "\n";
    tree.printLeafLinkedList();

    return 0;
}