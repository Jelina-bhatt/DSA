#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

class DFA {
    unordered_map<int, unordered_map<char, int>> transition;
    unordered_set<int> finalStates;
    int startState;

public:
    DFA(int start): startState(start) {}

    void addTransition(int from, char input, int to) {
        transition[from][input] = to;
    }

    void addFinalState(int state) {
        finalStates.insert(state);
    }

    bool isAccepted(const string& input) {
        int current = startState;
        for (char ch : input) {
            if (transition[current].count(ch)) {
                current = transition[current][ch];
            } else {
                return false;
            }
        }
        return finalStates.count(current) > 0;
    }
};

int main() {
    DFA dfa(0); // Starting at state 0

    // DFA for binary strings ending with '01'
    // States: 0 - start, 1 - seen '0', 2 - seen '01'
    dfa.addTransition(0, '0', 1);
    dfa.addTransition(0, '1', 0);
    dfa.addTransition(1, '0', 1);
    dfa.addTransition(1, '1', 2);
    dfa.addTransition(2, '0', 1);
    dfa.addTransition(2, '1', 0);

    dfa.addFinalState(2); // Accept if ends in state 2

    // Test strings
    string test;
    cout << "Enter binary string to test: ";
    cin >> test;

    if (dfa.isAccepted(test))
        cout << "✅ Accepted by DFA (ends with '01')\n";
    else
        cout << "❌ Rejected by DFA\n";

    return 0;
}
