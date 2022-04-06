#pragma once
#ifndef NQUEENS_H
#define NQUEENS_H

#include <iostream>
#include "Stack.h"
using namespace std;

class nQueens
{
private:
    int N;
    Stack<char> *board;
    int column;
    bool colZero = true;
public:
    // Constructor
    nQueens(int numQueens, int col) : N(numQueens), column(col)
    {
        board = new Stack<char>[numQueens];
        if (col != 0)
            colZero = false;
    }

    void mainMenu()
    {
        solveNQ();
    }

    // Mutator
    void setNQueens(int numQueens)
    {
        N = numQueens;
    }
    void setColumn(int col)
    {
        column = col;
    }

    // Precondition: board pointer Stack<char> 
    // Postcondition: return the board of the n-Queens game
    void printSolution(Stack<char> *board)
    {
        cout << "\t ";
        for (int i = 0; i < N * 2; i++)
        {
            cout << "- ";
        }

        cout << '\n';
        for (int i = 0; i < N; i++) {
            cout << "\t|";
            for (int j = 0; j < N; j++)
                cout << " " << board[i].getElement(j) << " |";
            cout << "\n";
        }

        cout << "\t ";
        for (int i = 0; i < N * 2; i++)
        {
            cout << "- ";
        }
    }

    // Precondition: board pointer (Stack<char>), row (int) and col (int)
    /* Postcondition: A utility function to check if a queen can
       be placed on board[row] in a specified col. Note that this
       function is called when "col" queens are
       already placed in columns from 0 to col -1.
       So we need to check only left side for attacking queens */
    bool isSafeS(Stack<char>* board, int row, int col)
    {
        int i, j;

        /* Check this row on left side */
        for (i = 0; i < col; i++)
            if (board[row].getElement(i) == 'Q')
            {
                return false;
            }
        /* Check this row on right side */
        for (i = col; i < N; i++)
            if (board[row].getElement(i) == 'Q')
            {
                return false;
            }

        /* Check upper diagonal on left side */
        for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
            if (board[i].getElement(j) == 'Q')
            {
                return false;
            }

        /* Check upper diagonal on right side */
        for (i = row, j = N; i >= col && j >= col; i--, j--)
            if (board[i].getElement(j) == 'Q')
            {
                return false;
            }

        /* Check lower diagonal on left side */
        for (i = row, j = N; j >= col && i < 0; i++, j--)
            if (board[i].getElement(j) == 'Q')
            {
                return false;
            }

        /* Check lower diagonal on right side */
        for (i = row, j = col; j >= 0 && i < N; i++, j--)
            if (board[i].getElement(j) == 'Q')
            {
                return false;
            }

        return true;
    }

    // Precondition: board pointer (Stack<char>), row (int) and col (int)
    // Postcondition: Return true if the N-Queen game can be solve or false otherwise
    bool solveNQUtil(Stack<char>* board, int col)
    {
        /* base case: If all queens are placed
          then return true */
        if (col >= N)
        {
            return true;
        }

        /* Consider this column and try placing
           this queen in all rows one by one */
        for (int i = 0; i < N; i++) {
            /* Check if the queen can be placed on
              board[i] in the specified column */
            if (isSafeS(board, i, col)) {
                /* Place this queen in board[i] into col */
                do
                {
                    if (board[i].getNumElements() == col)
                    {
                        // Replace '_' for 'Q'
                        char catchElemChar;
                        board[i].pop(catchElemChar);
                        board[i].push('Q');
                        break;
                    }
                    else
                    {
                        // Pop elements until reach the column
                        char catchElemChar;
                        board[i].pop(catchElemChar);
                    }
                } while (true);
                // Pushing back '_'
                for (int k = col; k < N; k++)
                {
                    board[i].push('_');
                }
                /* recur to place rest of the queens */
                if (solveNQUtil(board, col + 1))
                    return true;

                /* If placing queen in board[i] and col
                   doesn't lead to a solution, then
                   remove queen from board[i] in col */
                // BACKTRACK
                do
                {
                    if (board[i].getNumElements() == col)
                    {
                        // Replace 'Q' for '_'
                        char catchElemChar;
                        board[i].pop(catchElemChar);
                        board[i].push('_');
                        break;
                    }
                    else
                    {
                        // Pop elements until reach the column
                        char catchElemChar;
                        board[i].pop(catchElemChar);
                    }

                } while (true);

                // Pushing back
                for (int k = col; k < N; k++)
                {
                    board[i].push('_');
                }
            }
        }
        /* If the queen cannot be placed in any row in
            this column col  then return false */
        return false;
    }

    // Precondition: 
    /* Postcondition: This function solves the N Queen problem using
       Backtracking. It mainly uses solveNQUtil() to
       solve the problem. It returns false if queens
       cannot be placed, otherwise, return true and
       prints placement of queens in the form of 1s.
       Please note that there may be more than one
       solutions, this function prints one  of the
       feasible solutions.*/
    bool solveNQ()
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                board[i].push('_');
            }
        }

        if (solveNQUtil(board, 0) == false) {
            cout << "\tSolution does not exist.\n";
            return false;
        }
        printSolution(board);
        
        return true;
    }

};

#endif // !NQUEENS_H


