#include <iostream>
#include <stack>
#include <memory>
#include <string>
#include <limits>

using namespace std;

class Node {
public:
    char data;
    unique_ptr<Node> left, right;
    
    Node(char value) : data(value), left(nullptr), right(nullptr) {}
};


class BinaryTree {
public:
    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
    }

    int getPrecedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        if (op == '^') return 3;
        return 0;
    }

    bool isRightAssociative(char c) {
        return c == '^'; 
    }

    void performOperation(stack<unique_ptr<Node>>& nodes, char op) {
        auto right = move(nodes.top()); 
        nodes.pop();
        auto left = move(nodes.top()); 
        nodes.pop();
        auto newNode = make_unique<Node>(op);
        newNode->left = move(left);
        newNode->right = move(right);
        nodes.push(move(newNode));
    }

    string infixToPostfix(string infix) {
        stack<char> s;
        string postfix = "";

        for (char c : infix) {
            if (isalnum(c)) {
                postfix += c;  // Operand: directly add to postfix
            } 
            else if (c == '(') {
                s.push(c);  // Left parenthesis: push onto stack
            } 
            else if (c == ')') {
                // Right parenthesis: pop until '('
                while (!s.empty() && s.top() != '(') {
                    postfix += s.top();
                    s.pop();
                }
                if (!s.empty()) s.pop(); 
            } 
            else if (isOperator(c)) {
                while (!s.empty() && 
                    ((getPrecedence(c) < getPrecedence(s.top())) ||
                        (getPrecedence(c) == getPrecedence(s.top()) && !isRightAssociative(c)))) {
                    postfix += s.top();
                    s.pop();
                }
                s.push(c);  // Push the incoming operator
            }
        }

        // Pop remaining operators
        while (!s.empty()) {
            postfix += s.top();
            s.pop();
        }

        return postfix;
    }

    unique_ptr<Node> buildExpressionTree(string& postfix) {
        stack<unique_ptr<Node>> nodes;
        stack<char> s;
        
        for (char c : postfix) {
            if (c == ' ') {
                continue;
            }
                
            if (isalnum(c)) {  
                nodes.push(make_unique<Node>(c));
            } 
            else if (c == '(') {  
                s.push(c);
            } 
            else if (c == ')') { 
                // Right parenthesis: pop until '(' 
                while (!s.empty() && s.top() != '(') {
                    performOperation(nodes, s.top());
                    s.pop();
                }
                s.pop();  
            } 
            else if (isOperator(c)) {  
                while (!s.empty() && s.top() != '(' &&
                       (getPrecedence(c) < getPrecedence(s.top()) ||
                       (getPrecedence(c) == getPrecedence(s.top()) && !isRightAssociative(c)))) {
                    performOperation(nodes, s.top());
                    s.pop();
                }
                s.push(c);
            }
        }

        // Remaining operators
        while (!s.empty()) {
            performOperation(nodes, s.top());
            s.pop();
        }

        return move(nodes.top());  // Root of the tree
    }

    void preorderTraversal(unique_ptr<Node>& node) {
        if (node == nullptr) {
            return;
        }

        cout << node->data;
        preorderTraversal(node->left);
        preorderTraversal(node->right);

    }
};

string getValidStringInput(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (value.empty()) {
            cout << "Invalid input. Please enter a non-empty string.\n";
        } else {
            return value;
        }
    }
}

int main() {
    BinaryTree tree;
    string infixExpression = getValidStringInput("Enter an infix expression: ");
    string postfixExpression = tree.infixToPostfix(infixExpression);
    cout << "Postfix expression: " << postfixExpression << endl;
    
    auto root = tree.buildExpressionTree(postfixExpression);

    cout << "Preorder Traversal of the Infix expression: ";
    tree.preorderTraversal(root);  
    cout << endl;

    return 0;
}
