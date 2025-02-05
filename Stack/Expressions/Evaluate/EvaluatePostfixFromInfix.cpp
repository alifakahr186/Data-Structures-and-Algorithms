#include <iostream>
#include <stack>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <cmath>
#include <limits>
#include <set>

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

int performOperation(int operand1, int operand2, char op) {
    switch (op) {
        case '^':
            return pow(operand1 , operand2);
        case '*':
            return operand1 * operand2;
        case '/':
            return operand1 / operand2;
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        default:
            return 0;
    }
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

int evaluatePostfixExpression(string postfixExpression, unordered_map<char, int>& variables) {
    stack<int> operandStack;

    for (char currentChar : postfixExpression) {
        if (isOperator(currentChar)) {
            int operand2 = operandStack.top(); 
            operandStack.pop();
            
            int operand1 = operandStack.top(); 
            operandStack.pop();

            int result = performOperation(operand1, operand2, currentChar);
            operandStack.push(result);
        } else if (isalpha(currentChar)){
            int operand = variables[currentChar];
            operandStack.push(operand);
        }
    }

    return operandStack.top();
}

void getUserInputForVariables(string infix, unordered_map<char, int>& variables) {
    set<char> variablesInExpression;

    // Identify unique variables in the infix expression
    for (char c : infix) {
        if (isalpha(c)) {
            variablesInExpression.insert(c);
        }
    }

    // Prompt user for values for each variable
    for (char var : variablesInExpression) {
        int value;
        cout << "Enter value for " << var << ": ";
        cin >> value;
        variables[var] = value;
    }
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
    cout << "Postfix Expression: " << postfixExpression << endl;

    unordered_map<char, int> variables;
    getUserInputForVariables(infixExpression, variables);


    int result = evaluatePostfixExpression(postfixExpression, variables);

    cout << "Result: " << result << endl;

    return 0;
}