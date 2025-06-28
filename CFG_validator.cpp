#include <iostream>
#include <string>
using namespace std;

string input;
int pos = 0;

// Function Prototypes
bool E();
bool T();
bool F();

bool match(char expected) {
    if (pos < input.size() && input[pos] == expected) {
        pos++;
        return true;
    }
    return false;
}

bool id() {
    if (input.substr(pos, 2) == "id") {
        pos += 2;
        return true;
    }
    return false;
}

// E → T { + T }
bool E() {
    if (!T()) return false;
    while (input[pos] == '+') {
        pos++;
        if (!T()) return false;
    }
    return true;
}

// T → F { * F }
bool T() {
    if (!F()) return false;
    while (input[pos] == '*') {
        pos++;
        if (!F()) return false;
    }
    return true;
}

// F → ( E ) | id
bool F() {
    if (match('(')) {
        if (!E()) return false;
        return match(')');
    } else {
        return id();
    }
}

int main() {
    cout << "Enter expression (use 'id' for identifier, no spaces): ";
    cin >> input;

    bool valid = E();
    if (valid && pos == input.length())
        cout << "✔️ Accepted: Input is valid as per CFG." << endl;
    else
        cout << "❌ Rejected: Invalid string." << endl;

    return 0;
}
