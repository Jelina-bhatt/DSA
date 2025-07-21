#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<int> lifoStack;

    // Pushing elements (Last In)
    lifoStack.push(10);
    lifoStack.push(20);
    lifoStack.push(30);

    cout << "Elements pushed: 10, 20, 30\n";
    cout << "Top element (last pushed): " << lifoStack.top() << endl;

    // Popping elements (First Out)
    cout << "Popping elements in LIFO order:\n";
    while (!lifoStack.empty()) {
        cout << lifoStack.top() << " ";
        lifoStack.pop();
    }
    cout << "\n";

    return 0;
}
