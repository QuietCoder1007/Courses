//
//  LinkedList.h
//

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include "Node.h"

// Linked List Class (double)
template <class T>
class LinkedList
{
public:
    // Constructor, copy constructor, destructor
    LinkedList();
    LinkedList(const LinkedList & lst);
    ~LinkedList();
    
    // Public interface
    void insert(const T & x);
    void remove(const T & x);
    const T & getFirst() const;
    const T & getLast() const;
    bool find(const T & x) const;
    bool isEmpty() const;
    void makeEmpty();
    void printList();
    
    // Operators
    const LinkedList<T> & operator=(const LinkedList<T> & rhs);
    
    // (Private) Dummy node
    Node<T> *dummy;
    
    // (Private) utility method
    Node<T> * findNode(const T & x) const;
};


#endif
