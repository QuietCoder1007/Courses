//
//  Tree.h
//

#ifndef _TREE_H_
#define _TREE_H_

#include <cstdlib>
#include <iostream>
#include <cassert>
#include <queue>
#include "Node.h"

template <class T>
class Tree
{
public:
    Tree()  { root = nullptr; };
    ~Tree() { /* This destructor was intentionally left blank. Yes, it is a memory leak. */ };

    static Tree<T> * makeRandomTree(int min, int max);
    static Node<T> * makeRandomTreeHelper(int min, int max);

    void printKeysPreOrder(Node<T> *node);
    void printKeysPostOrder(Node<T> *node);
    void printKeysInOrder(Node<T> *node);
    void printKeysLevelOrder(Node<T> *node);

    Node<T> *root;
};

#endif
