#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<string> typingStack;
    int choice;
    string word;

    while (true) {
        cout << "\n1. Type Word\n2. Undo Last Word\n3. Show Current Text\n4. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter word: ";
            cin >> word;
            typingStack.push(word);
            cout << "\"" << word << "\" added to the text.\n";
        }
        else if (choice == 2) {
            if (!typingStack.empty()) {
                cout << "Undo: \"" << typingStack.top() << "\" removed.\n";
                typingStack.pop();
            } else {
                cout << "Nothing to undo!\n";
            }
        }
        else if (choice == 3) {
            if (typingStack.empty()) {
                cout << "Text is empty.\n";
            } else {
                stack<string> tempStack = typingStack;
                cout << "Current Text (from first to last): ";
                string sentence = "";
                while (!tempStack.empty()) {
                    sentence = tempStack.top() + " " + sentence;
                    tempStack.pop();
                }
                cout << sentence << endl;
            }
        }
        else if (choice == 4) {
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
