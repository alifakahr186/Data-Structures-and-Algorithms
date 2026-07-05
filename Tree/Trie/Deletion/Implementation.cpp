#include <iostream>
using namespace std;

struct TrieNode {
    TrieNode* children[26]; 
    bool isEndOfWord;

    TrieNode() {
        for (int i = 0; i < 26; i++) {
            children[i] = NULL;
        }
        isEndOfWord = false;
    }
};

void insertWord(TrieNode* root, string word) {
    TrieNode* curr = root;

    for (char ch : word) {
        int index = ch - 'a'; // 'a'->0, 'b'->1, ... 'z'->25

        if (curr->children[index] == NULL) {
            curr->children[index] = new TrieNode();
        }

        curr = curr->children[index];
    }

    curr->isEndOfWord = true;
    cout << word << " inserted successfully!\n";
}

bool hasChildren(TrieNode* node) {
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != NULL) {
            return true;
        }
    }
    return false;
}

bool deleteWord(TrieNode* root, string word, int depth = 0) {
    if (root == NULL) return false;

    // Base case: end of word
    if (depth == word.size()) {
        if (!root->isEndOfWord) {
            return false; // word not found
        }

        // Unmark the end of word
        root->isEndOfWord = false;

        // If node has no children, it can be deleted
        return !hasChildren(root);
    }

    int index = word[depth] - 'a';
    if (root->children[index] == NULL) {
        return false; 
    }

    bool shouldDeleteChild = deleteWord(root->children[index], word, depth + 1);

    if (shouldDeleteChild) {
        delete root->children[index];
        root->children[index] = NULL;

        return !root->isEndOfWord && !hasChildren(root);
    }

    return false;
}

int main() {
    TrieNode* root = new TrieNode();
    int n;
    cout << "How many words do you want to insert? ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        string word;
        cout << "Enter word " << i + 1 << ": ";
        cin >> word;
        insertWord(root, word);
    }

    string delWord;
    cout << "\nEnter a word to delete: ";
    cin >> delWord;

    if (deleteWord(root, delWord)) {
        cout << delWord << " deleted successfully (and cleaned up extra nodes).\n";
    } else {
        cout << delWord << " deleted (unmarked as word), or not found.\n";
    }

    return 0;
}
