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

    return 0;
}
