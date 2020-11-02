//
//  AATree.cpp
//

#include "AATree.h"
#include "Flags.h"

/* **************************************************************** */

#if CONSTRUCTOR || ALL
template <class T>
AATree<T>::AATree()
{
    // TODO: Create sentinel node (i.e. bottomNode)
    // assign the sentinel node to root, lastNode, and deletedNode
    root = bottomNode;
    bottomNode = bottomNode;
    lastNode = bottomNode;
    deletedNode = bottomNode;
    bottomNode->left = bottomNode;
    bottomNode->right = bottomNode;
    bottomNode->level = 0;
}
#endif

/* **************************************************************** */

#if DESTRUCTOR || ALL
template <class T>
AATree<T>::~AATree()
{
    // TODO: Remove any nodes
    // don't forget to deallocate bottomNode
    makeEmpty();
}
#endif

/* **************************************************************** */

#if ISEMPTY || ALL
// TODO: isEmpty() method
template<class T>
bool AATree<T>::isEmpty() const{
    return root == bottomNode && root->data == 0;
}
#endif

/* **************************************************************** */

#if FIND || ALL
// TODO: find() method
template <class T>
bool AATree<T>::find(const T & x){
    return findNode(root, x)->data == x;
}
#endif

/* **************************************************************** */

#if FINDNODE || ALL

// TODO: findNode() private method - iterative
template <class T>
Node<T> * AATree<T>::findNode(Node<T> * node, const T & x){
    while(node != bottomNode && node->data){
        if(x < node->data){
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return node;
}
#endif

/* **************************************************************** */

#if FINDMIN || ALL
// TODO: findMin() method
template <class T>
const T & AATree<T>::findMin(){
    return findMinNode(root)->data;
}
#endif

/* **************************************************************** */

#if FINDMINNODE || ALL
// TODO: findMinNode() private method
template <class T>
Node<T> * AATree<T>::findMinNode(Node<T> * node){
    while (node->left != bottomNode){
        node = node->left;
    }
    return node;
}
#endif

/* **************************************************************** */

#if FINDMAX || ALL
// TODO: findMax() method
template <class T>
const T & AATree<T>::findMax(){
    return findMaxNode(root)->data;
}
#endif

/* **************************************************************** */

#if FINDMAXNODE || ALL
// TODO: findMaxNode() private method
template <class T>
Node<T> * AATree<T>::findMaxNode(Node<T> * node){
    while (node->right != bottomNode){
        node = node->right;
    }
    return node;
}
#endif

/* **************************************************************** */

#if INSERT || ALL
// TODO: insert() method
template<class T>
void AATree<T>::insert(const T & x){
    if (!find(x)){
        insertNode(root, x);
    }
}
#endif

/* **************************************************************** */

#if INSERTNODE || ALL
// TODO: insertNode() private method
template<class T>
void AATree<T>::insertNode(Node<T> * & node, const T & x){
    if( !node ){
        node = new Node<T>(x);
    } else if( x < node->data ){
        insert( node->left, x );
    } else if( x > node->data  ){
        insert( node->right, x );
    }
    node = skew( node );
    node = split( node );
    return node;
}
#endif

/* **************************************************************** */

#if REMOVE || ALL
// TODO: remove() method
template<class T>
void AATree<T>::remove(const T & x){
    if (find(x)){
        removeNode(root, x);
    }
}
#endif

/* **************************************************************** */

#if REMOVENODE || ALL
// TODO: removeNode() private method
template<class T>
void AATree<T>::removeNode(Node<T> * & node, const T & x){
//    if( node->left->level < --node->level || node->right->level < node->level - 1 ) // check level of children{
//        if( node->right->level > --node->level ) {                                  // check level of right horizontal children
//            node->right->level = node->level;                                       // and decrement if necessary
//        }
//        node = skew( node );                                                    // First skew (may alter current root)
//        node->right = skew( node->right );                                      // Second skew
//        node->right->right = skew( node->right->right );                        // Third skew
//        node = split( node );                                                   // First split (may alter current root)
//        node->right = split( node->right );                                     // Second split
//    }

    if(node == bottomNode){
        lastNode = node;
        if (x < node->data){
            removeNode(node->left, x)
        } else {
            deletedNode = node;
            removeNode(node->right, x);
        }
    } else if (node == lastNode && deletedNode = bottomNode && deletedNode->data == x){
        deletedNode->data = node->data;
        deletedNode = bottomNode;
        node = node->right;
        delete lastNode;
    } else if node->left->level < --node->level || node->right->level < --node->level) {
        --node->level;
        if (node->right->level > node->level){
            node->right->level = node->level;
        }
        skew(node);
        skew(node->right);
        skew(node->right->right);
        split(node);
        split(node->right);
    }
}
#endif

/* **************************************************************** */

#if SKEW || ALL
// TODO: skew() private method
template<class T>
void AATree<T>::skew(Node<T> * & node){
    Node<T> * new_node;
    if( node->left->level == node->level ){
        new_node = node->left;
        node->left = new_node->right;
        new_node->right = node;
    } else {
        new_node = node->right;
        node->right = new_node->left;
        new_node->left = node;
    }
    return node;
}
#endif

/* **************************************************************** */

#if SPLIT || ALL
// TODO: split() private method
template<class T>
void AATree<T>::split(Node<T> * & node){
    if( node->right->right->level == node->level ) {
        node = rotateWithRightChild( node );
        node->level++;
    }
    return node;
}
#endif

/* **************************************************************** */

#if MAKEEMPTY || ALL
// TODO: makeEmpty() method
template<class T>
void AATree<T>::makeEmpty() {
    removeAllNodes(root);
}
#endif

/* **************************************************************** */

#if REMOVEALLNODES || ALL
// TODO: removeAllNodes() private method
template<class T>
void AATree<T>::removeAllNodes(Node<T> *node) {
    for (int i = 0; i < 3; i ++ ){

    }
}
#endif

/* **************************************************************** */



/* **************************************************************** */
/* Do NOT modify anything below this line                           */
/* **************************************************************** */

#ifndef BUILD_LIB
// Print tree
template <class T>
void AATree<T>::printTree(){
    if (root != bottomNode)
    {
        printNodesInOrder(root);
        std::cout << std::endl;
    } else {
        std::cout << "Empty Tree" << std::endl;
        std::cout << std::endl;
    }
}

// Print tree using level order traversal
template <class T>
void AATree<T>::printNodesInOrder(Node<T> * node)
{
    Node<T>* q[100];
    int head = 0;
    int tail = 0;
    q[0] = node;
    tail++;
    
    while (head != tail)
    {
        Node<T> *n = q[head];
        head++;
        std::cout << "Node " << n->data << " at level " << n->level << std::endl;
        if (n->left != bottomNode)
        {
            std::cout << "  " << n->data << " left child: " << n->left->data << std::endl;
            q[tail] = n->left;
            tail++;
        }
        if (n->right != bottomNode)
        {
            std::cout << "  " << n->data << " right child: " << n->right->data << std::endl;
            q[tail] = n->right;
            tail++;
        }
    }
}
#endif

template class AATree<int>;
