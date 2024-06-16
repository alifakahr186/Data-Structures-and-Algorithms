#include <iostream>
#include <stack>
#include <string>

// Function to check if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to convert prefix to infix
std::string prefixToInfix(std::string prefix) {
    std::stack<std::string> stack;

    // Read the prefix expression from right to left
    for (int i = prefix.length() - 1; i >= 0; i--) {
        if (isOperator(prefix[i])) {
            // Pop two operands from the stack
            std::string operand1 = stack.top();
            stack.pop();
            std::string operand2 = stack.top();
            stack.pop();

            // Construct the infix expression
            std::string infix = "(" + operand1 + prefix[i] + operand2 + ")";
            stack.push(infix);
        } else {
            // Current character is an operand
            std::string operand(1, prefix[i]);
            stack.push(operand);
        }
    }

    return stack.top();
}

int main() {
    std::string prefixExpression;
    std::cout << "Enter a prefix expression: ";
    std::cin >> prefixExpression;

    std::string infixExpression = prefixToInfix(prefixExpression);
    std::cout << "Infix expression: " << infixExpression << std::endl;

    return 0;
}
