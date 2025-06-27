#include <iostream>
#include <regex>
#include <queue>
#include <unordered_map>
using namespace std;

class LexicalAnalyzer {
private:
    queue<string> tokens;
    unordered_map<string, string> symbolTable;

public:
    void tokenize(string line) {
        regex pattern(R"(\w+|[=+*/-])");  // match words and operators
        sregex_iterator it(line.begin(), line.end(), pattern);
        sregex_iterator end;

        while (it != end) {
            tokens.push(it->str());
            ++it;
        }
    }

    void analyze() {
        while (!tokens.empty()) {
            string token = tokens.front();
            tokens.pop();

            if (isKeyword(token)) {
                cout << token << " : [Keyword]\n";
            } else if (regex_match(token, regex(R"(\d+)"))) {
                cout << token << " : [Number]\n";
            } else if (regex_match(token, regex(R"([=+*/-])"))) {
                cout << token << " : [Operator]\n";
            } else {
                cout << token << " : [Identifier]\n";
                symbolTable[token] = "ID";
            }
        }
    }

    bool isKeyword(string word) {
        string keywords[] = {"int", "float", "if", "else", "while", "return"};
        for (string k : keywords)
            if (word == k) return true;
        return false;
    }

    void displaySymbolTable() {
        cout << "\n📘 Symbol Table:\n";
        for (auto& entry : symbolTable)
            cout << entry.first << " => " << entry.second << "\n";
    }
};

// Driver
int main() {
    LexicalAnalyzer lexer;
    string line;
    cout << "Enter a line of code:\n";
    getline(cin, line);

    lexer.tokenize(line);
    lexer.analyze();
    lexer.displaySymbolTable();

    return 0;
}
