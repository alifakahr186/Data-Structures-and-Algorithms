#include <iostream>
#include <stack>
#include <algorithm>

bool isOperator(char c){

    return (c == '+' || c == '-' || c == '*' || c == '/');

}

int getPrecedence(char c) {
    if (c == '+' || c == '-')
        return 1;

    else if (c == '*' || c == '/')
        return 2;

    else if(c == '^')
        return 3;

    return 0;
}

// Function to convert infix to prefix
std::string infixToPrefix(std::string infix){
    std::stack<char> stack;
    std::string prefix = "";

    std::reverse(infix.begin(), infix.end());

    for (size_t i = 0; i < infix.length(); i++) {
        
        if (isalpha(infix[i]) || isdigit(infix[i]))
        {
            prefix += infix[i];
        }

        else if(infix[i] == ')')
        {
            stack.push(infix[i]);
        }

        else if(infix[i] == '(')
        {
            while (!stack.empty() && stack.top() != ')')
            {
                prefix += stack.top();
                stack.pop();
            }

            if (!stack.empty())
            {
                stack.pop(); // Pop the closing bracket
            }
        }

        else if(isOperator(infix[i]))
        {
            while (!stack.empty() && getPrecedence(stack.top()) > getPrecedence(infix[i]))
            {
                prefix += stack.top();
                stack.pop();
            }

            stack.push(infix[i]);
        
        }
    
    }

    while (!stack.empty())
    {
        prefix += stack.top();
        stack.pop();
    }

    std::reverse(prefix.begin(), prefix.end());
    return prefix;
}

int main() {
    std::string infixExpression;
    std::cout << "Enter an infix expression: ";
    std::cin >> infixExpression;

    std::string prefixExpression = infixToPrefix(infixExpression);
    std::cout << "Prefix expression: " << prefixExpression << std::endl;

    return 0;
}
