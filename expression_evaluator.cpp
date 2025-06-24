#include <iostream>
#include <stack>
#include <cctype>
#include <string>
#include <cmath>
using namespace std;

int precedence(char op) {
    if(op == '+'||op == '-') return 1;
    if(op == '*'||op == '/') return 2;
    if(op == '^') return 3;
    return 0;
}

string infixToPostfix(string infix) {
    stack<char> st;
    string postfix;
    
    for(char ch : infix) {
        if(ch == ' ') continue;
        if(isdigit(ch)) {
            postfix += ch;
        } else {
            postfix += ' ';
            while(!st.empty() && precedence(st.top()) >= precedence(ch)) {
                postfix += st.top();
                postfix += ' ';
                st.pop();
            }
            st.push(ch);
        }
    }

    while(!st.empty()) {
        postfix += ' ';
        postfix += st.top();
        st.pop();
    }

    return postfix;
}

int evaluatePostfix(string postfix) {
    stack<int> st;
    int i = 0;

    while(i < postfix.size()) {
        if(postfix[i] == ' ') {
            i++;
            continue;
        }

        if(isdigit(postfix[i])) {
            int num = 0;
            while(i < postfix.size() && isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            st.push(num);
        } else {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();

            switch(postfix[i]) {
                case '+': st.push(a + b); break;
                case '-': st.push(a - b); break;
                case '*': st.push(a * b); break;
                case '/': st.push(a / b); break;
                case '^': st.push(pow(a, b)); break;
            }
            i++;
        }
    }

    return st.top();
}

int main() {
    string infix;
    cout << "Enter infix expression (e.g., 3+4*2): ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    cout << "Postfix Expression: " << postfix << endl;

    int result = evaluatePostfix(postfix);
    cout << "Evaluated Result: " << result << endl;

    return 0;
}
