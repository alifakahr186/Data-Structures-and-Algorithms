#include <iostream>
using namespace std;

struct TreeNode {
    char val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* buildTreeHelper(
    const char preorder[],
    const char postorder[],
    int& preIdx,
    int postStart,
    int postEnd,
    int postIdx[]
) {
    if (preIdx >= strlen(preorder) || postStart > postEnd) {
        return nullptr;
    }

    TreeNode* root = new TreeNode(preorder[preIdx++]);

    if (postStart != postEnd) {
        int postIdxVal = postIdx[preorder[preIdx] - 'A'];
        root->left = buildTreeHelper(preorder, postorder, preIdx, postStart, postIdxVal, postIdx);
        root->right = buildTreeHelper(preorder, postorder, preIdx, postIdxVal + 1, postEnd - 1, postIdx);
    }

    return root;
}

TreeNode* buildTree(const char preorder[], const char postorder[]) {
    int postIdx[26] = {0}; // Assuming characters are from 'A' to 'Z'

    for (int i = 0; i < strlen(postorder); ++i) {
        postIdx[postorder[i] - 'A'] = i;
    }

    int preIdx = 0;
    return buildTreeHelper(preorder, postorder, preIdx, 0, strlen(postorder) - 1, postIdx);
}

void printInorder(TreeNode* node) {
    if (node == nullptr) {
        return;
    }

    printInorder(node->left);
    cout << node->val << " ";
    printInorder(node->right);
}

int main() {
    const char preorder[] = "FBA DC EG I H";
    const char postorder[] = "ACED HIG F";

    TreeNode* root = buildTree(preorder, postorder);

    cout << "Inorder traversal of the constructed tree: ";
    printInorder(root);
    cout << endl;

    return 0;
}
