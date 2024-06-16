#include <iostream>
#include <stack>
#include <string>
#include<cmath>
#include <cstdlib> // for atoi function

using namespace std;

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
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

int evaluatePrefixExpression(string prefixExpression) {
    stack<int> operandStack;

    // Scan the prefix expression from right to left
    for (int i = prefixExpression.length() - 1; i >= 0; i--) {
        char currentChar = prefixExpression[i];

        if (isOperator(currentChar)) {
            // Operator found, pop two operands from the stack
            int operand1 = operandStack.top();
            operandStack.pop();

            int operand2 = operandStack.top();
            operandStack.pop();

            // Perform the operation
            int result = performOperation(operand1, operand2, currentChar);

            // Push the result back to the stack
            operandStack.push(result);
        } else {
            // Operand found, convert it to integer and push it onto the stack
            int operand = currentChar - '0'; // Convert char to int
            operandStack.push(operand);
        }
    }

    // The final result will be at the top of the stack
    return operandStack.top();

}

int main() {
    string prefixExpression;
    cout << "Enter the prefix expression: ";
    getline(cin, prefixExpression);

    int result = evaluatePrefixExpression(prefixExpression);
    cout << "Evaluation result: " << result << endl;

    return 0;
}
