//
//  IntArrayStack.cpp
//

#include "IntArrayStack.h"
#include "Flags.h"

/* **************************************************************** */

#if CONSTRUCTOR || ALL
// TODO: Constructor
#endif

/* **************************************************************** */

#if DESTRUCTOR || ALL
// TODO: Destructor
#endif

/* **************************************************************** */

#if PUSH || ALL
// TODO: push()
#endif

/* **************************************************************** */

#if POP || ALL
// TODO: pop()
#endif

/* **************************************************************** */

#if PEEK || ALL
// TODO: peek()
#endif

/* **************************************************************** */

#if ISEMPTY || ALL
// TODO: isEmpty()
#endif

/* **************************************************************** */

#if EMPTYSTACK || ALL
// TODO: emptyStack()
#endif

/* **************************************************************** */

#if RESIZE || ALL
// TODO: resize()
#endif

/* **************************************************************** */
// Do NOT modify anything below this line
// Do NOT use these methods in your implementation of your data
// structure.  They are included here to support the unit tests.
/* **************************************************************** */

#ifndef BUILD_LIB
void IntArrayStack::printStack()
{
    std::cout << std::endl;
    std::cout << "Current array size: " << capacity << std::endl;
    std::cout << "Number of ints in stack: " << top+1 << std::endl;
    for (int i=top; i >= 0; i--)
    {
        std::cout << stack[i] << " ";
    }
    std::cout << std::endl;
}


// Do NOT use this method in your implementation
int IntArrayStack::getCapacity()
{
    return capacity;
}


// Do NOT use this method in your implementation
int IntArrayStack::getSize()
{
    return top+1;
}


// Do NOT use this method in your implementation
int IntArrayStack::getTop()
{
    return top;
}


// Do NOT use this method in your implementation
void IntArrayStack::toArray(int* arr)
{
    for (int i=0; i < capacity; i++)
    {
        arr[i] = stack[i];
    }
}
#endif

/* **************************************************************** */


