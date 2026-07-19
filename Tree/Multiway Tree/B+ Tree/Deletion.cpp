#include <iostream>
using namespace std;

static const int m = 5;
static const int n = m - 1;   // Max keys = 4

class Node {
public:
    int key[n];
    int keyCount;
    Node* child[m];
    bool isLeaf;
    Node* next;          // For leaf linked list

    Node() {
        keyCount = 0;
        isLeaf = true;
        next = nullptr;
        for (int i = 0; i < m; i++)
            child[i] = nullptr;
    }
};

class BPlusTree {
private:
    Node* root;

    // ===================== INSERTION =====================
    void splitChild(Node* parent, int index) {
        Node* left = parent->child[index];
        Node* right = new Node();

        right->isLeaf = left->isLeaf;
        right->keyCount = n / 2;

        for (int i = 0; i < n / 2; i++)
            right->key[i] = left->key[i + (n / 2) + 1];

        if (!left->isLeaf) {
            for (int i = 0; i <= n / 2; i++)
                right->child[i] = left->child[i + (n / 2) + 1];
        }

        left->keyCount = n / 2 + 1;   // Middle key stays in left leaf

        if (left->isLeaf) {
            right->next = left->next;
            left->next = right;
        }

        // Shift parent children
        for (int i = parent->keyCount; i >= index + 1; i--)
            parent->child[i + 1] = parent->child[i];

        parent->child[index + 1] = right;

        for (int i = parent->keyCount - 1; i >= index; i--)
            parent->key[i + 1] = parent->key[i];

        parent->key[index] = left->key[n / 2];   // Copy up
        parent->keyCount++;
    }

    void insertNonFull(Node* node, int value) {
        int i = node->keyCount - 1;

        if (node->isLeaf) {
            while (i >= 0 && value < node->key[i]) {
                node->key[i + 1] = node->key[i];
                i--;
            }
            node->key[i + 1] = value;
            node->keyCount++;
        } else {
            while (i >= 0 && value < node->key[i]) i--;
            i++;

            if (node->child[i]->keyCount == n) {
                splitChild(node, i);
                if (value > node->key[i]) i++;
            }
            insertNonFull(node->child[i], value);
        }
    }

    Node* Insert(Node* rootNode, int value) {
        if (rootNode == nullptr) {
            Node* newNode = new Node();
            newNode->key[0] = value;
            newNode->keyCount = 1;
            return newNode;
        }

        if (rootNode->keyCount == n) {
            Node* newRoot = new Node();
            newRoot->isLeaf = false;
            newRoot->child[0] = rootNode;

            splitChild(newRoot, 0);

            int i = 0;
            if (value > newRoot->key[0]) i++;

            insertNonFull(newRoot->child[i], value);
            return newRoot;
        } else {
            insertNonFull(rootNode, value);
            return rootNode;
        }
    }

    // ===================== DELETION =====================
    void removeFromLeaf(Node* node, int idx) {
        for (int i = idx + 1; i < node->keyCount; i++)
            node->key[i - 1] = node->key[i];
        node->keyCount--;
    }

    void borrowFromLeft(Node* parent, int idx) {
        Node* child = parent->child[idx];
        Node* leftSibling = parent->child[idx - 1];

        for (int i = child->keyCount - 1; i >= 0; i--)
            child->key[i + 1] = child->key[i];

        child->key[0] = leftSibling->key[leftSibling->keyCount - 1];
        parent->key[idx - 1] = child->key[0];   // Update separator

        child->keyCount++;
        leftSibling->keyCount--;
    }

    void borrowFromRight(Node* parent, int idx) {
        Node* child = parent->child[idx];
        Node* rightSibling = parent->child[idx + 1];

        child->key[child->keyCount] = rightSibling->key[0];
        parent->key[idx] = rightSibling->key[1] ? rightSibling->key[1] : rightSibling->key[0];

        for (int i = 1; i < rightSibling->keyCount; i++)
            rightSibling->key[i - 1] = rightSibling->key[i];

        child->keyCount++;
        rightSibling->keyCount--;
    }

    void mergeLeaves(Node* parent, int idx) {
        Node* left = parent->child[idx];
        Node* right = parent->child[idx + 1];

        for (int i = 0; i < right->keyCount; i++)
            left->key[left->keyCount + i] = right->key[i];

        left->keyCount += right->keyCount;
        left->next = right->next;

        // Shift parent
        for (int i = idx + 1; i < parent->keyCount; i++)
            parent->key[i - 1] = parent->key[i];

        for (int i = idx + 2; i <= parent->keyCount; i++)
            parent->child[i - 1] = parent->child[i];

        parent->keyCount--;
        delete right;
    }

    void deleteKey(Node* node, int value) {
        int idx = 0;
        while (idx < node->keyCount && node->key[idx] < value)
            idx++;

        if (node->isLeaf) {
            if (idx < node->keyCount && node->key[idx] == value)
                removeFromLeaf(node, idx);
            return;
        }

        bool last = (idx == node->keyCount);

        if (node->child[idx]->keyCount < (n / 2 + 1)) {
            if (idx > 0 && node->child[idx - 1]->keyCount >= (n / 2 + 1))
                borrowFromLeft(node, idx);
            else if (idx < node->keyCount && node->child[idx + 1]->keyCount >= (n / 2 + 1))
                borrowFromRight(node, idx);
            else
                mergeLeaves(node, idx > 0 ? idx - 1 : idx);
        }

        if (last && idx > node->keyCount)
            deleteKey(node->child[idx - 1], value);
        else
            deleteKey(node->child[idx], value);
    }

    void inorder(Node* node) {
        if (!node) return;
        for (int i = 0; i < node->keyCount; i++) {
            if (!node->isLeaf)
                inorder(node->child[i]);
            if (node->isLeaf)
                cout << node->key[i] << " ";
        }
        if (!node->isLeaf)
            inorder(node->child[node->keyCount]);
    }

public:
    BPlusTree() : root(nullptr) {}

    void insert(int value) {
        root = Insert(root, value);
    }

    void remove(int value) {
        if (root == nullptr) {
            cout << "Tree is empty!\n";
            return;
        }
        deleteKey(root, value);

       if (root->keyCount == 0) {
            Node* temp = root;
            if (root->isLeaf) {
                root = nullptr;
            } else {
                root = root->child[0];
            }
            delete temp;
        }
    }

    void inorderTraversal() {
        inorder(root);
        cout << endl;
    }

    void printLeafLinkedList() {
        if (!root) return;
        Node* curr = root;
        while (!curr->isLeaf) curr = curr->child[0];

        cout << "Leaf Nodes (Linked): ";
        while (curr) {
            for (int i = 0; i < curr->keyCount; i++)
                cout << curr->key[i] << " ";
            curr = curr->next;
        }
        cout << endl;
    }
};

int main() {
    BPlusTree tree;

    int total;
    cout << "How many values do you want to insert: ";
    cin >> total;

    for (int i = 0; i < total; i++) {
        int value;
        cout << "Enter Value " << i + 1 << ": ";
        cin >> value;
        tree.insert(value);
    }

    cout << "\nInorder Traversal:\n";
    tree.inorderTraversal();

    tree.printLeafLinkedList();

    int del;
    cout << "\nEnter value to delete: ";
    cin >> del;
    tree.remove(del);

    cout << "\nAfter Deletion:\n";
    tree.inorderTraversal();
    tree.printLeafLinkedList();

    return 0;
}