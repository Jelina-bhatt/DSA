#include <iostream>
#include <vector>
#include <string>

using namespace std;

string getTerm(int index, int vars) {
    string term = "";
    for (int i = vars - 1; i >= 0; i--) {
        char var = 'A' + (vars - 1 - i);
        if ((index >> i) & 1) {
            term += var;
        } else {
            term += var;
            term += '\'';
        }
    }
    return term;
}

int main() {
    int vars;
    cout << "Enter number of variables (2 to 4): ";
    cin >> vars;

    int rows = 1 << vars;
    vector<int> truthTable(rows);
    cout << "Enter output (0/1) for each input combination:\n";
    for (int i = 0; i < rows; i++) {
        cout << "Row " << i << " (binary ";
        for (int j = vars - 1; j >= 0; j--) cout << ((i >> j) & 1);
        cout << "): ";
        cin >> truthTable[i];
    }

    cout << "\nMinimized SOP Expression: F = ";
    bool first = true;
    for (int i = 0; i < rows; i++) {
        if (truthTable[i] == 1) {
            if (!first) cout << " + ";
            cout << getTerm(i, vars);
            first = false;
        }
    }

    if (first) cout << "0"; // No 1s
    cout << endl;

    return 0;
}
