//
//  Node.h
//

#ifndef _NODE_H_
#define _NODE_H_

// Linked List Node (double)
template <class T>
class Node
{
public:
    // Constructor (private, only for friends)
    explicit Node(const T & theData = T(), Node * nnode = nullptr, Node * pnode = nullptr)
    : data(theData), next(nnode), prev(pnode) {}
    
    // (Private) members
    T data;
    Node *next;
    Node *prev;
};


#endif
