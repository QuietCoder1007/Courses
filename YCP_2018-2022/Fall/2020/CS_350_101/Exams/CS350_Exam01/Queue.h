//
//  Queue.h
//

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <cassert>
#include "Node.h"

// Queue class
template <class T>
class Queue
{
public:
    /* **************************************************************** */
    // Fields
    /* **************************************************************** */
    Node<T> *head;
    Node<T> *tail;
    
    /* **************************************************************** */
    // Methods
    /* **************************************************************** */
    Queue();
    ~Queue();
    
    void enqueue(T value);
    T dequeue();
    bool isEmpty() const;
    void makeEmpty();
};

#endif
