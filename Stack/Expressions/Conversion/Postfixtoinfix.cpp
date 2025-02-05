#include <iostream>
#include <stack>
#include <string>
#include <limits>

using namespace std;

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

std::string postfixToInfix(const std::string& postfix) {
    std::stack<std::string> stack;

    for (char c : postfix) {
        if (isOperator(c)) {
            if (stack.size() < 2) {
                cerr << "Invalid postfix expression!" << endl;
                return "";
            }
            std::string operand2 = stack.top();
            stack.pop();
            std::string operand1 = stack.top();
            stack.pop();

            std::string infix = operand1 + c + operand2;
            stack.push(infix);
        } else {
            stack.push(std::string(1, c));
        }
    }

    if (stack.size() != 1) {
        cout << "Invalid postfix expression!" << endl;
        return "";
    }

    return stack.top();
}

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
    string postfixExpression = getValidStringInput("Enter a postfix expression: ");
    string infixExpression = postfixToInfix(postfixExpression);

    if (!infixExpression.empty()) {
        cout << "Infix expression: " << infixExpression << endl;
    }

    return 0;
}
