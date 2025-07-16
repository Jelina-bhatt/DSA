// vault.cpp - Smart Password Vault using DSA
#include <iostream>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Structure to store each password entry
struct PasswordEntry {
    string website;
    string username;
    string password;
    time_t timestamp;

    bool operator>(const PasswordEntry& other) const {
        return timestamp > other.timestamp; // Min-Heap based on timestamp
    }
};

unordered_map<string, PasswordEntry> vault; // HashMap for fast access
priority_queue<PasswordEntry, vector<PasswordEntry>, greater<>> minHeap; // Track oldest passwords

// Save to file
void saveToFile() {
    ofstream file("../data/vault_data.txt");
    for (auto it = vault.begin(); it != vault.end(); ++it) {
        PasswordEntry entry = it->second;
        file << entry.website << '|' << entry.username << '|' << entry.password << '|' << entry.timestamp << '\n';
    }
    file.close();
}

// Load from file
void loadFromFile() {
    ifstream file("../data/vault_data.txt");
    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos) continue;

        PasswordEntry entry;
        entry.website = line.substr(0, pos1);
        entry.username = line.substr(pos1 + 1, pos2 - pos1 - 1);
        entry.password = line.substr(pos2 + 1, pos3 - pos2 - 1);
        entry.timestamp = stoll(line.substr(pos3 + 1));

        vault[entry.website] = entry;
        minHeap.push(entry);
    }
    file.close();
}

// Add a password
void addPassword() {
    PasswordEntry entry;
    cout << "Website: ";
    cin >> entry.website;
    cout << "Username: ";
    cin >> entry.username;
    cout << "Password: ";
    cin >> entry.password;
    entry.timestamp = time(0);

    vault[entry.website] = entry;
    minHeap.push(entry);
    saveToFile();
    cout << "Password saved successfully!\n";
}

// View old passwords
void viewOldPasswords() {
    cout << "\n--- Passwords older than 30 days ---\n";
    time_t now = time(0);
    priority_queue<PasswordEntry, vector<PasswordEntry>, greater<>> tempHeap = minHeap;
    while (!tempHeap.empty()) {
        PasswordEntry top = tempHeap.top();
        if (difftime(now, top.timestamp) > 2592000) { // 30 days
            cout << "Website: " << top.website << ", Username: " << top.username << "\n";
        } else {
            break;
        }
        tempHeap.pop();
    }
    cout << "-----------------------------\n";
}

// Main menu
int main() {
    loadFromFile();
    int choice;
    while (true) {
        cout << "\n1. Add Password\n2. View Old Passwords\n3. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) addPassword();
        else if (choice == 2) viewOldPasswords();
        else break;
    }
    return 0;
}
