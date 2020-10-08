//
//  BST.cpp
//

#include "BST.h"
#include "Flags.h"

/* **************************************************************** */

#if ALL || CONSTRUCTOR
template <class T>
BST<T>::BST()
{
    // TODO: Initialize root
    root = nullptr;
    numNodes = 0;
}
#endif

/* **************************************************************** */

#if ALL || DESTRUCTOR
template <class T>
BST<T>::~BST()
{
    // TODO: Remove any nodes
    root = nullptr;
    numNodes = 0;
    delete root;
}
#endif

/* **************************************************************** */

#if ALL || ISEMPTY
// TODO: isEmpty() method
template <class T>
bool BST<T>::isEmpty(){
    return root == nullptr && numNodes == 0;
}
#endif

/* **************************************************************** */

#if ALL || FIND
// TODO: find() method
template <class T>
bool find(const T & x){
    return findNode(root, x)-> data == x;
}

#endif

/* **************************************************************** */

#if ALL || FINDMIN
// TODO: findMin() method
template <class T>
const T & BST<T>::findMin(){
    return findMinNode(root)->data;
}
#endif

/* **************************************************************** */

#if ALL || FINDMAX
// TODO: findMax() method
template <class T>
const T & BST<T>::findMax(){
    return findMaxNode(root)->data;
}
#endif

/* **************************************************************** */

#if ALL || INSERT
// TODO: insert() method
template <class T>
void BST<T>::insert(const T & x){
    insertNode(root, x);
}
#endif

/* **************************************************************** */

#if ALL || REMOVE
// TODO: remove() method
template <class T>
void BST<T>::remove(const T &x) {
    Node<T> *currentNode = findNode(root, x);
    Node<T> *successorNode = findSuccessor(currentNode->right);
    Node<T> *parentNode = findParentOf(x);

    if(currentNode->left == nullptr && currentNode->right == nullptr){
        if (parentNode->left->data == x){
            parentNode->left = nullptr;
        }

        if (parentNode->right->data == x){
            parentNode->right = nullptr;
        }
    } else if(currentNode->left != nullptr && currentNode->right == nullptr){
        currentNode->data = currentNode->left->data;
        currentNode->left = nullptr;
    } else if(currentNode->left == nullptr && currentNode->right != nullptr){
        currentNode->data = currentNode->right->data;
        currentNode->right = nullptr;
    } else{
        currentNode->data = successorNode->data;
        if (successorNode->right == nullptr){
            successorNode = nullptr;
        } else{
            successorNode->data = successorNode->right->data;
            successorNode->right = nullptr;
        }
    }
    numNodes--;
}
#endif

/* **************************************************************** */

#if ALL || MAKEEMPTY
// TODO: makeEmpty() method
template <class T>
void BST<T>::makeEmpty(){
    root = nullptr;
    numNodes = 0;
}
#endif

/* **************************************************************** */



/* **************************************************************** */
/*  Private methods                                                 */
/* **************************************************************** */
#if ALL || FINDNODE
// TODO: findNode() private method
template <class T>
Node<T> * BST<T>::findNode(Node<T> * node, const T & x){
    if (node == nullptr || x == node->data){
        return node;
    } else if (x < node->data){
        return findNode(node->left, x);
    } else if (x > node->data){
        return findNode(node->right, x);
    }
}
#endif

/* **************************************************************** */

#if ALL || FINDMINNODE
// TODO: findMinNode() private method
template <class T>
Node<T> * BST<T>::findMinNode(Node <T> *node){
    if (node->left != nullptr){
        findMinNode(node->left);
    }
    return node;
}
#endif

/* **************************************************************** */

#if ALL || FINDMAXNODE
// TODO: findMaxNode() private method
template <class T>
Node<T> * BST<T>::findMaxNode(Node <T> *node){
    if (node->right != nullptr){
        findMaxNode(node->right);
    }
    return node;
}
#endif

/* **************************************************************** */

#if ALL || INSERTNODE
// TODO: insertNode() private method
template <class T>
Node<T> * BST<T>::insertNode(Node<T> * node, const T & x){
    if(node == nullptr){
        node = new Node<T>(x);
    }
    else if (x < node->data){
        return insertNode(node->left, x);
    } else if (x > node->data){
        return insertNode(node->right, x);
    }
    return node;
}
#endif

/* **************************************************************** */

#if ALL || FINDSUCCESSOR
// TODO: findSuccessor() private method
template <class T>
Node<T> * BST<T>::findSuccessor(Node<T> *node) {
    Node<T> * currentNode = node->right;
    while(currentNode->left != nullptr){
        currentNode = currentNode->left;
    }
    return currentNode;
}
#endif

/* **************************************************************** */

#if ALL || FINDPARENTOF
// TODO: findParentOf() private method
template <class T>
Node<T> * BST<T>::findParentOf(const T &x) {
    Node<T> * currentNode = root;
    while (currentNode->right->data != x || currentNode->left->data != x){
        if (currentNode->left->data < x){
            currentNode = currentNode->left;
        }
        else if (currentNode->right->data > x){
            currentNode = currentNode->right;
        }
    }
    return currentNode;
}
#endif

/* **************************************************************** */

#if ALL || REMOVEALLNODES
// TODO: removeAllNodes() private method
#endif

/* **************************************************************** */



/* **************************************************************** */
/* Do NOT modify anything below this line                           */
/* **************************************************************** */

#ifndef BUILD_LIB
// Print tree
template <class T>
void BST<T>::printTree()
{
    if (!isEmpty())
    {
        printNodesInOrder(root);
        std::cout << std::endl;
    } else {
        std::cout << "Empty Tree" << std::endl;
    }
}

// Print tree using level order traversal
template <class T>
void BST<T>::printNodesInOrder(Node<T> * node)
{
    Node<T>*q[100];
    int head = 0;
    int tail = 0;
    q[0] = root;
    tail++;
    
    while (head != tail) {
        Node<T> *n = q[head];
        head++;
        std::cout << "Node " << n->data << " ";
        if (n->left != nullptr) {
            std::cout << " left child: " << n->left->data;
            q[tail] = n->left;
            tail++;
        }
        if (n->right != nullptr) {
            std::cout << " right child: " << n->right->data;
            q[tail] = n->right;
            tail++;
        }
        
        if (n->left == nullptr && n->right == nullptr) {
            std::cout << " no children";
        }
        std::cout << std::endl;
    }
}
#endif

template class BST<int>;
