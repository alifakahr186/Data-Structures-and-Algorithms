#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* buildTreeHelper(int inorder[], int postorder[], int inStart, int inEnd, int postStart, int postEnd) {
    if (inStart > inEnd || postStart > postEnd) 
    return nullptr;

    int rootValue = postorder[postEnd];
    TreeNode* root = new TreeNode(rootValue);

    int rootIndex = -1;

    for (int i = inStart; i <= inEnd; ++i) {
        if (inorder[i] == rootValue) {
            rootIndex = i;
            break;
        }
    }

    int leftSubtreeSize = rootIndex - inStart;

    root->left = buildTreeHelper(inorder, postorder, inStart, rootIndex - 1, postStart, postStart + leftSubtreeSize - 1);
    root->right = buildTreeHelper(inorder, postorder, rootIndex + 1, inEnd, postStart + leftSubtreeSize, postEnd - 1);

    return root;

}

TreeNode* buildTree(int inorder[], int postorder[], int size) {
    if (size <= 0) return nullptr;
    return buildTreeHelper(inorder, postorder, 0, size - 1, 0, size - 1);
}

void printInorder(TreeNode* node) {
    if (node == nullptr) return;
    printInorder(node->left);
    cout << node->val << " ";
    printInorder(node->right);
}

int main() {
    int inorder[] = {9, 5, 1, 7, 2, 12, 8, 4, 3, 11};
    int postorder[] = {9, 1, 2, 12, 7, 5, 3, 11, 4, 8};
    int size = sizeof(inorder) / sizeof(inorder[0]);

    TreeNode* root = buildTree(inorder, postorder, size);

    cout << "Inorder Traversal of Constructed Tree: ";
    printInorder(root);
    cout << endl;

    return 0;
}
