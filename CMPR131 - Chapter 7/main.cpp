// date: 04/03/2022
// description: Chapter 7 - Assignment

#include <iostream>
#include <string>
#include "input.h" // use for validate input
#include "SimpleCalculator.h"
#include "nQueens.h"
#include "InfixToPostfix.h"

using namespace std;

// Prototype
int menuOption();
void removeSpaces(string& infix);

int main()
{
    do
    {
        switch (menuOption())
        {
        case 0: exit(1); break;
        case 1:
        {
            cout << "\t1> Simple Calculator";
            cout << "\n\t=========================================================================";
            string infix;
            cout << "\n\tEnter a fully parenthesized arithmetic expression: ";
            getline(cin, infix);
            removeSpaces(infix);
            SimpleCalculator simp;
            simp.simpleCalculatorMain(infix);
        } break;
        case 2:
        {
            cout << "\t2> Translation of arithmetic expression";
            cout << "\n\t=========================================================================";
            InfixToPostfix i; 
            string infix = "a+b*(c^d-e)^(f+g*h)-i";
            i.infixToPostfixMain(infix);
            infix = "((a+b)*(c+e))";
            i.infixToPostfixMain(infix);
            cout << "\n\n\tInput a fully parenthesized infix expression: ";
            getline(cin, infix);
            removeSpaces(infix);
            i.infixToPostfixMain(infix);
        } break;
        case 3:
        {
            int numQ = inputInteger("\tEnter a number(1..100) of queens: ", 1, 100);
            int col = inputInteger("\tEnter the column(1.." + to_string(numQ) + ") to place the first queen: ", 1, numQ); // Does not work 
            nQueens queen(numQ, col - 1);
            queen.mainMenu();

        } break;
        default: cout << "\n\tERROR - Invalid option. Please re-enter.\n"; break;
        }
        /*cout << "\n";
        system("pause");*/
    } while (true);

    return EXIT_SUCCESS;
}

// return a valid option (0...n)
int menuOption()
{
    cout << "\n\t=========================================================================";
    cout << "\n\tCMPR131 Chapter 7: Applications using Stacks by:";
    cout << "\n\tAlavi, Eduardo, Matthew, and Victor";
    cout << "\n\t=========================================================================";
    cout << "\n\t\t1> Simple Calculator (problem 9, pg 391)";
    cout << "\n\t\t2> Translation of arithmetic expression (problem 10, pg 391)";
    cout << "\n\t\t3> n-Queens Problem (problem 11, pg 391-292)";
    cout << "\n\t-------------------------------------------------------------------------";
    cout << "\n\t\t0> Exit";
    cout << "\n\t=========================================================================\n";

    int option = inputInteger("\tOption: ", 0, 3);
    system("cls");

    cout << "\n";
    return option;
}

//removing spaces from the string
void removeSpaces(string& infix)
{
    infix.erase(remove(infix.begin(), infix.end(), ' '), infix.end());
}