#include <iostream>
#include <stack>
#include <string>
#include <limits>

using namespace std;

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int getPrecedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    return 0;
}

bool isRightAssociative(char c) {
    return c == '^';
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

string getValidStringInput(string prompt) {
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
    string infixExpression = getValidStringInput("Enter an infix expression: ");
    string postfixExpression = infixToPostfix(infixExpression);

    if (!postfixExpression.empty()) {
        cout << "Postfix expression: " << postfixExpression << endl;
    }

    return 0;
}

