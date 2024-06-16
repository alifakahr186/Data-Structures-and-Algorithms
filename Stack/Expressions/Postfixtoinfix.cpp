#include <iostream>
#include <stack>
#include <string>

// Function to check if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to convert postfix to infix
std::string postfixToInfix(std::string postfix) {
    std::stack<std::string> stack;

    // Read the postfix expression from left to right
    for (int i = 0; i < postfix.length(); i++) {
        if (isOperator(postfix[i])) {
            // Pop two operands from the stack
            std::string operand2 = stack.top();
            stack.pop();
            std::string operand1 = stack.top();
            stack.pop();

            // Construct the infix expression
            std::string infix = "(" + operand1 + postfix[i] + operand2 + ")";
            stack.push(infix);
        } else {
            // Current character is an operand
            std::string operand(1, postfix[i]);
            stack.push(operand);
        }
    }

    return stack.top();
}

int main() {
    std::string postfixExpression;
    std::cout << "Enter a postfix expression: ";
    std::cin >> postfixExpression;

    std::string infixExpression = postfixToInfix(postfixExpression);
    std::cout << "Infix expression: " << infixExpression << std::endl;

    return 0;
}
