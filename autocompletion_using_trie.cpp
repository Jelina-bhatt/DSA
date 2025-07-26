#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Trie Node Definition
class TrieNode {
public:
    bool isEnd;
    unordered_map<char, TrieNode*> children;

    TrieNode() {
        isEnd = false;
    }
};

// Trie Class
class Trie {
private:
    TrieNode* root;

    void dfs(TrieNode* node, string prefix, vector<string>& suggestions) {
        if (node->isEnd) suggestions.push_back(prefix);

        for (auto& pair : node->children) {
            dfs(pair.second, prefix + pair.first, suggestions);
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (!current->children[ch])
                current->children[ch] = new TrieNode();
            current = current->children[ch];
        }
        current->isEnd = true;
    }

    vector<string> autocomplete(string prefix) {
        TrieNode* current = root;
        for (char ch : prefix) {
            if (!current->children[ch])
                return {};  // No suggestions
            current = current->children[ch];
        }
        vector<string> suggestions;
        dfs(current, prefix, suggestions);
        return suggestions;
    }
};

// Mock Transformer Function (Contextual Prediction)
vector<string> mockTransformerPrediction(string context) {
    // Very basic simulation of transformer output
    if (context.find("for") != string::npos) {
        return { "int i = 0;", "i < n;", "i++" };
    } else if (context.find("if") != string::npos) {
        return { "(x > 0)", "(arr[i] == target)", "(n != 0)" };
    } else if (context.find("while") != string::npos) {
        return { "(true)", "(x < y)", "(ptr != NULL)" };
    }
    return { "return 0;", "cout << \"Hello\";", "exit(0);" };
}

// Main Application
int main() {
    Trie trie;

    // Load some code-related words/snippets
    vector<string> keywords = {
        "for", "foreach", "function", "float", "if", "int", "include",
        "init", "input", "insert", "index", "increment", "iterator"
    };

    for (string word : keywords) {
        trie.insert(word);
    }

    cout << "=== Code Autocomplete System ===\n";
    string input;
    cout << "\nStart typing code (type 'exit' to quit):\n";

    while (true) {
        cout << "\n>> ";
        getline(cin, input);
        if (input == "exit") break;

        cout << "📌 Trie Autocomplete Suggestions:\n";
        vector<string> trieSuggestions = trie.autocomplete(input);
        for (string s : trieSuggestions)
            cout << " - " << s << '\n';

        cout << "🧠 Mock Transformer Predictions:\n";
        vector<string> transformer = mockTransformerPrediction(input);
        for (string s : transformer)
            cout << " - " << s << '\n';
    }

    return 0;
}
