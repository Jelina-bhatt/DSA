#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Define a node
struct Node {
    char data;
    struct Node *left, *right;
};

// Create a new node
struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Check if character is operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Build expression tree from postfix expression
struct Node* constructTree(char postfix[]) {
    struct Node* stack[100];
    int top = -1;
    
    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];
        
        if (isspace(ch)) continue;

        struct Node* newNode = createNode(ch);

        if (!isOperator(ch)) {
            stack[++top] = newNode;
        } else {
            newNode->right = stack[top--];
            newNode->left = stack[top--];
            stack[++top] = newNode;
        }
    }

    return stack[top];
}

// Inorder traversal (to get infix expression)
void inorder(struct Node* root) {
    if (root != NULL) {
        if (isOperator(root->data)) printf("(");
        inorder(root->left);
        printf("%c", root->data);
        inorder(root->right);
        if (isOperator(root->data)) printf(")");
    }
}

int main() {
    // Postfix of 3 + (2 * 5) is 3 2 5 * +
    char postfix[] = "3 2 5 * +";

    struct Node* root = constructTree(postfix);

    printf("Infix Expression is: ");
    inorder(root);  // Output: (3+(2*5))
    printf("\n");

    return 0;
}
