#include "SimpleCalculator.h"

// prototype
string postfixConvert(string infix);

// arithmetic check
bool check(string infix)
{
	int openParenthesis = 0;
	int closedParenthesis = 0;
	int len = infix.length();

	for (int i = 0; i < len; i++)
	{
		if (infix[i] == '(')
			openParenthesis++;
		else if (infix[i] == ')')
			closedParenthesis++;
		else if ((infix[i] >= '0' && infix[i] <= '9'))
			continue;
		else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^' || infix[i] == '.')
			continue;
		else
		{
			cout << "\n\t\tERROR: Invalid arithmetic expression.\n";
			return false;
		}
		// if there's more ')' than '(' at any given time, it's an imbalance parenthesis
		if (closedParenthesis > openParenthesis)
		{
			cout << "\n\t\tERROR: Imbalance parenthesis.\n";
			return false;
		}
	}
	if (closedParenthesis == openParenthesis)
		return true;
	else
	{
		cout << "\n\t\tERROR: Imbalance parenthesis.\n";
		return false;
	}
}

void SimpleCalculator::simpleCalculatorMain(string infix)
{
	// checks for arithmetic imbalances
	if (!check(infix))
	{
		return;
	}
	// converts the infix expression to a postfix expression
	string post_exp = postfixConvert(infix);
	cout << "\n\t\tPostfix expression: " << post_exp;

	stack <double> stack;
	int len = post_exp.length();

	for (int i = 0; i < len; i++)
	{
		// if the character is an operand, then it's pushed in the stack
		if (post_exp[i] >= '0' && post_exp[i] <= '9')
		{
			double value = post_exp[i] - '0'; // the " - '0'" makes it equal to a value and not the ASCII
			while (post_exp[i + 1] >= '0' && post_exp[i + 1] <= '9') // enters here if there is more than 1 digit
			{
				if (i < len && post_exp[i + 1] >= '0' && post_exp[i + 1] <= '9')
				{
					value *= 10;
					value += post_exp[i + 1] - '0';
					i++;
				}
			}
			stack.push(value);
		}

		else if (post_exp[i] == '.')
		{
			double temp = 10;
			i++;
			double value = post_exp[i] - '0'; // the " - '0'" makes it equal to a value and not the ASCII
			while (post_exp[i + 1] >= '0' && post_exp[i + 1] <= '9') // enters here if there is more than 1 digit after the decimal
			{
				if (i < len && post_exp[i + 1] >= '0' && post_exp[i + 1] <= '9')
				{
					temp *= 10;
					value *= 10;
					value += post_exp[i + 1] - '0';
					i++;
				}
			}
			// adding in the decimal value to the rest of the value
			value /= temp;
			value += stack.top();
			stack.pop();
			stack.push(value);
		}

		else if (post_exp[i] == ' ')
			continue;
		// enters here if the character is an operator
		else
		{
			// pop the top two elements from the stack and save them in two integers (defaults to '0' if a second number DNE)
			double a = stack.top();
			stack.pop();
			double b;
			if (stack.size() == 0)
				b = 0;
			else
			{
				b = stack.top();
				stack.pop();
			}
			// performing the operation on the operands
			switch (post_exp[i])
			{
			case '+': // addition
				stack.push(b + a);
				break;
			case '-': // subtraction
				stack.push(b - a);
				break;
			case '*': // multiplication
				stack.push(b * a);
				break;
			case '/': // division
				stack.push(b / a);
				break;
			case '^': // exponent
				stack.push(pow(b, a));
				break;
			}
		}
	}

	cout << "\n\t\tThe solution to this postfix expression is '" << stack.top() << "'.\n";
}

//////////////////// slightly altered code from infixToPostfix.cpp //////////////////////////////////
// returns the precedence based off the operators (PEMDAS)
int precedence(char c)
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
string postfixConvert(string infix)
{
	stack<char> st;
	string result;

	for (int i = 0; i < infix.length(); i++)
	{
		char c = infix[i];

		// If the scanned character is a digit, then it puts the digits together, then output to string
		if (c >= '0' && c <= '9')
		{
			string digit;
			digit += c;
			while (infix[i + 1] >= '0' && infix[i + 1] <= '9')
			{
				digit += infix[i + 1];
				i++;
			}
			result += digit;
			result += " ";
		}
		// if the scanned char is a '.'
		else if (c == '.')
		{
			if (result.length() > 0)
			{
				if (result[result.length() - 1] == ' ' && result[result.length() - 2] >= '0' && result[result.length() - 2] <= '9')
					result.erase(result.length() - 1);
			}
			if (result.length() > 0)
			{
				if (result[result.length() - 1] >= '0' && result[result.length() - 1] <= '9')
				{
					// continue on with the program and avoiding the else statement
				}
				else
				{
					result += "0";
				}
			}
			else
				result += "0";

			string digit;
			digit += c;
			if (infix[i + 1] >= '0' && infix[i + 1] <= '9')
			{
				while (infix[i + 1] >= '0' && infix[i + 1] <= '9')
				{
					digit += infix[i + 1];
					i++;
				}
			}
			else
			{
				digit += '0';
			}
			result += digit;
			result += " ";
		}

		// If the scanned character is an e(e, push it to the stack.
		else if (c == '(')
			st.push('(');

		// If the scanned character is an e)f, pop and output string from the stack until an e(e is encountered.
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
			while (!st.empty() && precedence(infix[i]) <= precedence(st.top()))
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

	return result;
}