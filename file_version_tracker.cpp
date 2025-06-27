#include <iostream>
#include <stack>
#include <list>
#include <unordered_map>
using namespace std;

class VersionTracker {
private:
    stack<string> undoStack;
    stack<string> redoStack;
    list<string> versionHistory;
    unordered_map<int, string> versionMap;
    int versionCount = 0;

public:
    void addVersion(string content) {
        undoStack.push(content);
        versionHistory.push_back(content);
        versionMap[++versionCount] = content;
        // Clear redo stack since we made a new change
        while (!redoStack.empty()) redoStack.pop();
        cout << "✅ Version " << versionCount << " added.\n";
    }

    void undo() {
        if (undoStack.empty()) {
            cout << "⚠️ Nothing to undo.\n";
            return;
        }
        string last = undoStack.top();
        undoStack.pop();
        redoStack.push(last);
        cout << "↩️ Undo performed.\n";
    }

    void redo() {
        if (redoStack.empty()) {
            cout << "⚠️ Nothing to redo.\n";
            return;
        }
        string content = redoStack.top();
        redoStack.pop();
        undoStack.push(content);
        cout << "🔁 Redo performed.\n";
    }

    void showHistory() {
        cout << "🕓 Version History:\n";
        int i = 1;
        for (const auto &v : versionHistory) {
            cout << "  Version " << i++ << ": " << v << "\n";
        }
    }

    void searchByVersion(int version) {
        if (versionMap.find(version) != versionMap.end()) {
            cout << "🔍 Version " << version << ": " << versionMap[version] << "\n";
        } else {
            cout << "❌ Version not found.\n";
        }
    }
};

// Driver code
int main() {
    VersionTracker tracker;
    int choice;
    string content;
    int version;

    do {
        cout << "\n===== File Version Tracker =====\n";
        cout << "1. Add New Version\n2. Undo\n3. Redo\n4. Show History\n5. Search Version\n0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // clear newline

        switch (choice) {
            case 1:
                cout << "Enter file content: ";
                getline(cin, content);
                tracker.addVersion(content);
                break;
            case 2:
                tracker.undo();
                break;
            case 3:
                tracker.redo();
                break;
            case 4:
                tracker.showHistory();
                break;
            case 5:
                cout << "Enter version number to search: ";
                cin >> version;
                tracker.searchByVersion(version);
                break;
            case 0:
                cout << "👋 Exiting...\n";
                break;
            default:
                cout << "❗ Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
