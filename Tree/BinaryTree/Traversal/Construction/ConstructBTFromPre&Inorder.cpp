#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* buildTreeHelper(int preorder[], int inorder[], int inStart, int inEnd, int preStart, int preEnd) {
    if (inStart > inEnd || preStart > preEnd) return nullptr;

    int rootValue = preorder[preStart];
    TreeNode* root = new TreeNode(rootValue);

    int rootIndex = -1;
    for (int i = inStart; i <= inEnd; ++i) {
        if (inorder[i] == rootValue) {
            rootIndex = i;
            break;
        }
    }

    int leftSubtreeSize = rootIndex - inStart;

    root->left = buildTreeHelper(preorder, inorder, inStart, rootIndex - 1, preStart + 1, preStart + leftSubtreeSize);
    root->right = buildTreeHelper(preorder, inorder, rootIndex + 1, inEnd, preStart + leftSubtreeSize + 1, preEnd);

    return root;
}

TreeNode* buildTree(int preorder[], int inorder[], int size) {
    if (size <= 0) return nullptr;
    return buildTreeHelper(preorder, inorder, 0, size - 1, 0, size - 1);
}

void printInorder(TreeNode* node) {
    if (node == nullptr) return;
    printInorder(node->left);
    cout << node->val << " ";
    printInorder(node->right);
}

int main() {
    int preorder[] = {1, 2, 4, 8, 9, 10, 11, 5, 3, 6, 7};
    int inorder[] = {8, 4, 10, 9, 11, 2, 5, 1, 6, 3, 7};
    int size = sizeof(inorder) / sizeof(inorder[0]);

    TreeNode* root = buildTree(preorder, inorder, size);

    cout << "Inorder Traversal of Constructed Tree: ";
    printInorder(root);
    cout << endl;

    return 0;
}
