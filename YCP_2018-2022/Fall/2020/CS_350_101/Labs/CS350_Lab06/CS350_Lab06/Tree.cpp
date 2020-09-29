//
//  Tree.cpp
//

#include "Tree.h"


/* **************************************************************** */
/* **************************************************************** */


template <class T>
void Tree<T>::printKeysPreOrder(Node<T> *node) {

    // TODO: Implement method to print keys using PreOrder traversal
    std::cout << "Method printKeysPreOrder: Not yet implemented!" << std::endl;

}


template <class T>
void Tree<T>::printKeysPostOrder(Node<T> *node) {

    // TODO: Implement method to print keys using PostOrder traversal
    std::cout << "Method printKeysPostOrder: Not yet implemented!" << std::endl;

}


template <class T>
void Tree<T>::printKeysInOrder(Node<T> *node) {

    // TODO: Implement method to print keys using InOrder traversal
    std::cout << "Method printKeysInOrder: Not yet implemented!" << std::endl;

}


template <class T>
void Tree<T>::printKeysLevelOrder(Node<T> *node) {

    // TODO: Implement method to print keys using LevelOrder traversal
    std::cout << "Method printKeysLevelOrder: Not yet implemented!" << std::endl;

//    Use the following line to define your queue
//    std::queue<Node<T> *> nodeQueue;
    
}


/* **************************************************************** */
/* **************************************************************** */


template <class T>
Tree<T> * Tree<T>::makeRandomTree(int min, int max) {
    Tree<T> *t = new Tree<T>();
    t->root = Tree<T>::makeRandomTreeHelper(min, max);
    return t;
}


template <class T>
Node<T> * Tree<T>::makeRandomTreeHelper(int min, int max) {
    // Base case
    if (min == max) {
        return new Node<T>(min);
    }

    // Adjust min and max to narrow the range.
    // This will leave gaps in the range of keys.
    // (If we don't do this, the tree will contain every
    // key between min and max inclusive.)
    int r = (max-min);
    int x = 0;
    while (r/2 > 0) {
        r /= 2;
        x++;
    }
    if (min + x < max - x) {
        min += x;
        max -= x;
    }

    int mid = min + (rand() % (max-min+1));
    assert(mid >= min);
    assert(mid <= max);

    Node<T> *n = new Node<T>(mid);
    if (mid > min) {
        n->left = Tree<T>::makeRandomTreeHelper(min, mid-1);
    }
    if (mid < max) {
        n->right = Tree<T>::makeRandomTreeHelper(mid+1, max);
    }
    return n;
}


/* **************************************************************** */
/* **************************************************************** */

template class Tree<int>;
