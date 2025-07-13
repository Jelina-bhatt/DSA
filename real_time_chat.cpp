#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord = false;
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children[c]) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;
    }

    bool search(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children[c]) return false;
            node = node->children[c];
        }
        return node->isEndOfWord;
    }

    // Optional: add delete method to remove banned words

    // Check if a substring starting at index i matches any banned word in the Trie
    // Returns length of matched banned word, or 0 if no match
    int matchFrom(const string& text, int start) {
        TrieNode* node = root;
        int length = 0;
        for (int i = start; i < text.size(); i++) {
            char c = text[i];
            if (!node->children[c]) break;
            node = node->children[c];
            length++;
            if (node->isEndOfWord) {
                return length;
            }
        }
        return 0;
    }

private:
    TrieNode* root;
};

// Replace banned words in a message using Trie
string filterMessage(const string& message, Trie& trie) {
    string filtered = message;
    for (int i = 0; i < (int)filtered.size(); i++) {
        int matchLen = trie.matchFrom(filtered, i);
        if (matchLen > 0) {
            // Replace banned word with stars
            for (int j = i; j < i + matchLen; j++) {
                filtered[j] = '*';
            }
            i += matchLen - 1; // skip matched part
        }
    }
    return filtered;
}

int main() {
    Trie bannedWordsTrie;

    // Add some banned words
    bannedWordsTrie.insert("bad");
    bannedWordsTrie.insert("ugly");
    bannedWordsTrie.insert("hate");

    cout << "Enter chat messages (type 'exit' to quit):\n";

    string message;
    while (true) {
        getline(cin, message);
        if (message == "exit") break;

        string filtered = filterMessage(message, bannedWordsTrie);
        cout << "Filtered: " << filtered << "\n";
    }

    return 0;
}
