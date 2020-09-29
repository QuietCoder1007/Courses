//
//  LinkedList.cpp
//

#include "LinkedList.h"
#include "Flags.h"

/* **************************************************************** */

#if CONSTRUCTOR || ALL
// Constructor
template <class T>
LinkedList<T>::LinkedList()
{
    // TODO: Allocate dummy node
    dummy = new Node<T>(0);
    dummy->next = dummy;
    dummy->prev = dummy;
}
#endif

/* **************************************************************** */

#if DESTRUCTOR || ALL
// Destructor
template <class T>
LinkedList<T>::~LinkedList()
{
// TODO: Remove any nodes
    makeEmpty();

// TODO: Free dummy node
    free(dummy);
}
#endif

/* **************************************************************** */

#if ALL || GETFIRST
// TODO: getFirst
template <class T>
const T & LinkedList<T>::getFirst() const {
    return dummy->next->data;
}
#endif

/* **************************************************************** */

#if ALL || GETLAST
// TODO: getLast
template <class T>
const T & LinkedList<T>::getLast() const {
    return dummy->prev->data;
}
#endif

/* **************************************************************** */

#if ALL || FIND
// TODO: find
template <class T>
bool LinkedList<T>::find(const T &x) const {
    return findNode(x) != dummy;
}
#endif

/* **************************************************************** */

#if ALL || FINDNODE
// TODO: findNode
template <class T>
Node<T> * LinkedList<T>::findNode(const T &x) const {
    Node<T> *search = dummy->next;
    while(search != dummy && search->data != x){
        search = search->next;
    }
    return search;
}
#endif

/* **************************************************************** */

#if ALL || INSERT
// TODO: insert
template <class T>
void LinkedList<T>::insert(const T &x) {
    Node<T> *node = new Node<T>(x);
    node->next = dummy->next;
    node->prev = dummy;
    dummy->next->prev = node;
    dummy->next = node;
}
#endif

/* **************************************************************** */

#if ALL || REMOVE
// TODO: remove
template <class T>
void LinkedList<T>::remove(const T &x) {
    Node<T> *node = findNode(x);
    if (node != dummy){
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
    }
}
#endif

/* **************************************************************** */

#if ALL || ISEMPTY
// TODO: isEmpty
template <class T>
bool LinkedList<T>::isEmpty() const {
    return dummy->next == dummy;

}
#endif

/* **************************************************************** */

#if ALL || MAKEEMPTY
// TODO: makeEmpty
template <class T>
void LinkedList<T>::makeEmpty() {
    Node<T> *node = dummy->next;
    while(node != dummy){
        dummy->next = node->next;
        node->next->prev = dummy;
        delete node;
        node = dummy->next;
    }
}
#endif

/* **************************************************************** */

#if ALL || COPY_CONSTRUCTOR
// TODO: Copy constructor
template <class T>
LinkedList<T>::LinkedList(const LinkedList & lst){
    dummy = new Node<T>(0);
    dummy->next = dummy;
    dummy->prev = dummy;

    Node<T> *node = lst.dummy->prev;

    while (node != lst.dummy){
        insert(node->data);
        node = node->prev;
    }
}
#endif

/* **************************************************************** */

#if ALL || ASSIGN
// TODO: Assignment operator
template <class T>
const LinkedList<T> & LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    makeEmpty();
    Node<T> *node = rhs.dummy->prev;

    while (node != rhs.dummy){
        insert(node->data);
        node = node->prev;
    }
    return *this;
}
#endif

/* **************************************************************** */
// Do NOT modify anything below this line
/* **************************************************************** */

#ifndef BUILD_LIB
// Print list
template <class T>
void LinkedList<T>::printList()
{
    if(isEmpty())
    {
        // Empty list
        std::cout << "Empty List" << std::endl;
    } else {
        // Iterate to end
        Node<T> *p = dummy->next;

        // Loop to end
        while (p != dummy)
        {
            std::cout << p->data << " ";
            p = p->next;
        }
        std::cout << std::endl;
    }
}
#endif

template class LinkedList<int>;
