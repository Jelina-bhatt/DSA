#include <iostream>
#include <stack>
#include <map>
#include <cctype>
using namespace std;

int precedence(char op) {
    if (op == '!') return 3;
    if (op == '&') return 2;
    if (op == '|') return 1;
    return 0;
}

string infixToPostfix(string infix) {
    stack<char> s;
    string postfix = "";
    for (char ch : infix) {
        if (isalpha(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            s.push(ch);
        } else if (ch == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top(); s.pop();
            }
            s.pop(); // remove '('
        } else {
            while (!s.empty() && precedence(s.top()) >= precedence(ch)) {
                postfix += s.top(); s.pop();
            }
            s.push(ch);
        }
    }
    while (!s.empty()) {
        postfix += s.top(); s.pop();
    }
    return postfix;
}

bool evaluatePostfix(string postfix, map<char, bool>& values) {
    stack<bool> s;
    for (char ch : postfix) {
        if (isalpha(ch)) {
            s.push(values[ch]);
        } else if (ch == '!') {
            bool val = s.top(); s.pop();
            s.push(!val);
        } else {
            bool b = s.top(); s.pop();
            bool a = s.top(); s.pop();
            if (ch == '&') s.push(a && b);
            else if (ch == '|') s.push(a || b);
        }
    }
    return s.top();
}

int main() {
    string infix;
    cout << "Enter boolean expression (use A,B,C... and operators !,&,|): ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    cout << "Postfix: " << postfix << endl;

    map<char, bool> values;
    for (char ch : infix) {
        if (isalpha(ch) && values.find(ch) == values.end()) {
            bool val;
            cout << "Enter value for " << ch << " (0 or 1): ";
            cin >> val;
            values[ch] = val;
        }
    }

    bool result = evaluatePostfix(postfix, values);
    cout << "Result: " << result << endl;

    return 0;
}
