//
//  SkipList.cpp
//

#include "SkipList.h"
#include "Flags.h"

/* **************************************************************** */

#if CONSTRUCTOR || ALL
// TODO: constructor
template<class T>
SkipList<T>::SkipList() {
    head = new Node<T>(T(), maxHeight);
    height = 1;

}
#endif

/* **************************************************************** */

#if DESTRUCTOR || ALL
// TODO: destructor
template<class T>
SkipList<T>::~SkipList() {
    makeEmpty();
    delete head;
}
#endif

/* **************************************************************** */

#if FIND || ALL
// TODO: find() method
template<class T>
bool SkipList<T>::find(const T &x) const {
    Node<T> *currentNode = head;
    for (int i = maxHeight - 1; i >= 0; --i) {
        while (currentNode->next[i] != nullptr && currentNode->next[i]->data < x){
            currentNode = currentNode->next[i];
        }
        // -- x->data < x && x <= x->next[i]->data
    }
    currentNode = currentNode->next[0];
    return currentNode->data == x;
}
#endif

/* **************************************************************** */

#if INSERT || ALL
// TODO: insert() method
template<class T>
void SkipList<T>::insert(const T &x) {
    Node<T> *update[maxHeight];
    Node<T> *currentNode = head;
    for (int i = maxHeight - 1; i >= 0; --i) {
        while (currentNode->next[i] != nullptr && currentNode->next[i]->data < x){
            currentNode = currentNode->next[i];
        }
        // -- x->data < x && x <= x->next[i]->data
    }
    currentNode = currentNode->next[0];

    if(currentNode->data == x){
        currentNode->data = x;
    } else {
        int lvl = randomLevel();
        if(lvl > head->height){
            for (int i = head->height + 1; i < lvl; ++i) {
               update[i] = head;
            }
            head->height = lvl;
        }
        currentNode = new Node<T>(x, lvl);
        for (int i = 1; i < lvl; ++i) {
            currentNode->next[i] = update[i]->next[i];
            update[i]->next[i] = currentNode;
        }
    }
}
#endif
#if REMOVE || ALL

/* **************************************************************** */

// TODO: remove() method
template<class T>
void SkipList<T>::remove(const T &x) {
    find(x);

}
#endif

/* **************************************************************** */

#if ISEMPTY || ALL
// TODO: isEmpty() method
template<class T>
bool SkipList<T>::isEmpty() const {
    Node<T> *currentNode = nullptr;
    for (int i = maxHeight - 1; i >= 0; --i) {
        if (head->next[i] != nullptr){
            currentNode = head->next[i];
        }
    }
    return currentNode == nullptr;
}
#endif

/* **************************************************************** */

#if MAKEEMPTY || ALL
// TODO: makeEmpty() method
template<class T>
void SkipList<T>::makeEmpty() {
    Node<T> *node = head;

    while (node->next != nullptr){
        node = head->next[0];
        node->next[0] = head->next[0];
        delete node;
    }
    head->data = 0;
    for (int i = maxHeight - 1; i >= 0; --i) {
        head->next[i] = nullptr;
    }
    height = 1;
}
#endif

/* **************************************************************** */

#if RANDOMLEVEL || ALL
// TODO: randomLevel() method
template<class T>
int SkipList<T>::randomLevel() {
    int lvl = 1;
    while(getRandomNumber() < 0.5 && lvl < maxHeight &&  lvl < height + 1){
        lvl++;
    }
    return lvl;
}
#endif

/* **************************************************************** */



/* **************************************************************** */
// Do NOT modify anything below this line
/* **************************************************************** */

#ifndef BUILD_LIB
// random number generator
template <class T>
double SkipList<T>::getRandomNumber()
{
    static int i = 0;
    static double a[10] = {0.32945,0.15923,0.12982,0.16250,0.36537,0.64072,0.27597,0.83957,0.75531,0.22502};
    
    return a[(i++)%10];
}


// printList() method
template <class T>
void SkipList<T>::printList()
{
    Node<T> *n = head;
    
    if (isEmpty())
    {
        std::cout << "Empty List" << std::endl;
    } else {
        while(n->next[0] != nullptr)
        {
            n = n->next[0];
            // Print node data
            std::cout << "Node " << n->data << " height " << n->height << ": ";
            
            // Print levels
            for (int i=(n->height - 1); i >= 0; i--) {
                std::cout << "Level " << i << " -> ";
                if (n->next[i] != nullptr) {
                    std::cout << n->next[i]->data;
                } else {
                    std::cout << "nullptr";
                }
                std::cout << ",";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
#endif

template class SkipList<int>;


