#include "InfixToPostfix.h"

bool parenthesisCheck(string s)
{
    int openParenthesis = 0, closedParenthesis = 0;
    int len = s.length();
    for (int i = 0; i < len; i++)
    {
        if (s[i] == '(')
            openParenthesis++;
        else if (s[i] == ')')
            closedParenthesis++;
        // if theres more ')' than '(' at any time, it's an imbalance parenthesis
        if (closedParenthesis > openParenthesis)
            return false;
    }
    if (closedParenthesis == openParenthesis)
        return true;
    else
        return false;
}

// returns the precedence based off the operators (PEMDAS)
int prec(char c)
{
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// function to convert the infix to a postfix expression
void infixToPostfixConversion(string s)
{
    if (!parenthesisCheck(s))
    {
        cout << "\n\t\tERROR: Imbalance parenthesis.\n";
        return;
    }

    stack<char> st;
    string result;

    for (int i = 0; i < s.length(); i++)
    {
        char c = s[i];

        // If the scanned character is
        // an operand, add it to output string.
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        {
            result += c;
            result += " ";
        }

        // If the scanned character is a digit
        // puts the digits together, then output to string
        else if (c >= '0' && c <= '9')
        {
            string digit;
            digit += c;
            while (s[i + 1] >= '0' && s[i + 1] <= '9')
            {
                digit += s[i + 1];
                i++;
            }
            result += digit;
            result += " ";
        }

        // If the scanned character is an
        // e(e, push it to the stack.
        else if (c == '(')
            st.push('(');

        // If the scanned character is an e)f,
        // pop and output string from the stack
        // until an e(e is encountered.
        else if (c == ')')
        {
            while (st.top() != '(')
            {
                result += st.top();
                result += " ";
                st.pop();
            }
            st.pop();
        }

        //If an operator is scanned
        else
        {
            while (!st.empty() && prec(s[i]) <= prec(st.top()))
            {
                result += st.top();
                result += " ";
                st.pop();
            }
            st.push(c);
        }
    }

    // Pop all the remaining elements from the stack
    while (!st.empty())
    {
        result += st.top();
        result += " ";
        st.pop();
    }

    cout << "\n\tpostfix: " << result << endl;
}

// main process for infixToPostfix
void InfixToPostfix::infixToPostfixMain(string infix)
{

    cout << "\n\tinfix: " << infix;
    infixToPostfixConversion(infix);
}