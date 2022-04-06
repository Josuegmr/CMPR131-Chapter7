#pragma once
#ifndef STACK_H
#define STACK_H

#include <stdexcept>
#include <iostream>
using namespace std;

template <class T>
class Stack
{
private:
	T* stackArray;  // Pointer to the stack array
	int stackSize;   // The stack size
	int top;        // Indicates the top of the stack

public:
    // Constructor
    Stack();
    Stack(int size);

    //Destructor
    ~Stack();

    // Stack operations    
    void push(T element);           // Pushes the element onto the stack
    void pop(T& element);           // Pops the element at the top of the stack off
    bool isFull() const;            // Return true if the array is full or false otherwise
    bool isEmpty() const;           // Return true if the array is empty or false otherwise
    void printArray();              // Display the values in the array. 
    T getElement(int index) const;  // Get an specific element in the array
    T getTop() const;               // Get the top element in the array
    int getNumElements() const;    
    T getPeek() const;               // Get the top element - 1 in the array

};

template <class T>
Stack<T>::Stack() // Constructor
{
    stackArray = new T[100];
    stackSize = 100;
    top = -1;
}

template <class T>
Stack<T>::Stack(int size) // Constructor
{
    stackArray = new T[size];
    stackSize = size;
    top = -1;
}

template <class T>
Stack<T>::~Stack() //Destructor
{
    delete[] stackArray;
}

template <class T>
void Stack<T>::push(T element) // Pushes the element onto the stack
{
    if (isFull())
    {
        cout << "\n\tERROR: Cannot push an element. Stack is full.\n";
    }
    else
    {
        top++;
        stackArray[top] = element;
    }
}

template <class T>
void Stack<T>::pop(T& element) // Pops the element at the top of the stack off
{
    if (isEmpty())
    {
        cout << "\n\tERROR: Cannot pop an element. Stack is empty.\n";
    }
    else // Pop value off top of stack
    {
        element = stackArray[top];
        top--;
    }
}

template <class T>
bool Stack<T>::isFull() const // Return true if the array is full or false otherwise
{
    bool status;
    if (top == stackSize - 1)
        status = true;
    else
        status = false;

    return status;
}

template <class T>
bool Stack<T>::isEmpty() const // Return true if the array is empty or false otherwise
{
    bool status;
    if (top < 0)
        status = true;
    else
        status = false;

    return status;
}

template <class T>
void Stack<T>::printArray() // Display the values in the array. 
{
    cout << "These values are in the stack:\n";
    for (int i = 0; i < stackSize; i++)
        cout << stackArray[i] << " ";
    cout << endl;
}

template <class T>
T Stack<T>::getElement(int index) const // Get an specific element in the array
{
    return stackArray[index];
}

template <class T>
T Stack<T>::getTop() const // Get the top element in the array
{
    //if(!isEmpty())
    return stackArray[top];
}

template <class T>
T Stack<T>::getPeek() const // Get the top element in the array
{
    //if(!isEmpty())
    return stackArray[top - 1];
}


template <class T>
int Stack<T>::getNumElements() const // Get the top element in the array
{
    //if(!isEmpty())
    return top;
}

#endif // !STACK_H


