//
//  AATree.h
//

#ifndef _AATREE_H_
#define _AATREE_H_

#include <iostream>
#include "Node.h"

// Binary search tree class
template <class T>
class AATree
{
public:
    // Constructor, destructor
    AATree();
    ~AATree();
    
    // Public interface
    bool find(const T & x);
    const T & findMin();
    const T & findMax();
    void insert(const T & x);
    void remove(const T & x);
    bool isEmpty();
    void makeEmpty();
    void printTree();
    
    // Node fields
    Node<T> *root;          // root node
    Node<T> *bottomNode;    // sentinel node
    Node<T> *lastNode;      // used for delete
    Node<T> *deletedNode;   // used for delete
    
    // Utility methods
    Node<T> * findNode(Node<T> * node, const T & x);
    Node<T> * findMinNode(Node<T> * node);
    Node<T> * findMaxNode(Node<T> * node);
    void insertNode(Node<T> * & node, const T & x);
    void removeNode(Node<T> * & node, const T & x);
    void skew(Node<T> * & node);
    void split(Node<T> * & node);
    void removeAllNodes(Node<T> * node);
    void printNodesInOrder(Node<T> * node);
};

#endif
