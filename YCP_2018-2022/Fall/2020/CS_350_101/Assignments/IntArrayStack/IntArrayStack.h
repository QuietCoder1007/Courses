//
//  IntArrayStack.h
//

#ifndef _INTARRAYSTACK_H_
#define _INTARRAYSTACK_H_

#include <iostream>

class IntArrayStack
{
private:
    // Class variables
    int *stack;
    int capacity;
    int top;

    // (Private) utility methods
    void resize(int newCapacity);
    
public:
    IntArrayStack();
    ~IntArrayStack();
    
    // Public interface
    void push(int x);
    int pop();
    int peek();
    void emptyStack();
    bool isEmpty();

    // The following methods are used for testing only
    void printStack();
    int getCapacity();
    int getSize();
    int getTop();
    void toArray(int* arr);
};

#endif 
