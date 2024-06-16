#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isOperator(char c){
    
    return (c == '+' || c == '-' || c == '*' || c == '/' || c ==  '^');

}

int getPrecedence(char c){
    if (c == '+' || c == '-')
        return 1;

    else if (c == '*' || c == '/')
        return 2;

    else if (c == '^')
        return 3;

    else
        return 0;
}

string infixToPostfix(string infix) {
    stack<char> s;
    string postfix = "";

    for (char c : infix)
    {
        if (isalnum(c))
        {
            postfix += c;
        }
        
        else if (c == '(')
        {
            s.push(c);
        } 
        
        else if (c == ')')
        {
            while (!s.empty() && s.top() != '(')
            {
                postfix += s.top();
                s.pop();
            }
            s.pop();

            if (!s.empty() && s.top() != '(')
                return "Invalid Expression"; 

        }
        
        else if (isOperator(c))
        {
            while (!s.empty() && getPrecedence(c) <= getPrecedence(s.top()))
            {
                postfix += s.top();
                s.pop();
            }

            s.push(c);
        }
    }

    while (!s.empty())
    {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}

int main(){

    string infix;
    cout << "Enter an infix expression: ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    cout << "Postfix expression: " << postfix << endl;

    return 0;
}

