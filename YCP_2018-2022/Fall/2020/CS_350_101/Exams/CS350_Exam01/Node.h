//
//  Node.h
//

#ifndef _NODE_H_
#define _NODE_H_

template <class T>
class Node
{
public:
    explicit Node (T theData = T()) : data(theData), next(nullptr) { }

    T data;
    Node<T> *next;
};

#endif
