//
//  Node.h
//

#ifndef _NODE_H_
#define _NODE_H_


template <class T>
class Node
{
public:
    // Constructor (private, only for friends)
    explicit Node(const T & theData = T(), Node * lch = nullptr, Node * rch = nullptr)
        : data(theData), left(lch), right(rch) {}
        
    T data;
    Node *left;
    Node *right;
};

#endif
