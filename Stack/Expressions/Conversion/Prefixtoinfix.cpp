#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

string prefixToInfix(string prefix) {
    stack<string> stack;

    // Traverse the prefix expression from right to left
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char c = prefix[i];
        
        if (c == ' ') {
            continue;
        }

        if (isalnum(c)) {
            stack.push(string(1, c));
        } 
        else if (isOperator(c)) {
            if (stack.size() < 2) {
                cerr << "Invalid prefix expression!" << endl;
                return "";
            }
            
            string operand1 = stack.top(); stack.pop();
            string operand2 = stack.top(); stack.pop();
            
            string infix = operand1 + c + operand2;
            
            stack.push(infix);
        } 
        else {
            cout << "Invalid character in prefix expression!" << endl;
            return "";
        }
    }

    if (stack.size() != 1) {
        cout << "Invalid prefix expression!" << endl;
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
    string prefixExpression = getValidStringInput("Enter a prefix expression: ");
    
    string infixExpression = prefixToInfix(prefixExpression);
    
    if (!infixExpression.empty()) {
        cout << "Infix expression: " << infixExpression << endl;
    }

    return 0;
}
