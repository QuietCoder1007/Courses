//
//  Queue.cpp
//

#include "Queue.h"
#include "Flags.h"


/* **************************************************************** */

#if ALL || CONSTRUCTOR
template<class T>
Queue<T>::Queue()
{
    // TODO: initialize fields so that queue is empty
    // 5 Points
    head = nullptr;
    tail = nullptr;
}
#endif

/* **************************************************************** */

#if ALL || DESTRUCTOR
template<class T>
Queue<T>::~Queue()
{
    // TODO: delete list nodes
    // 5 Points
    makeEmpty();
}
#endif

/* **************************************************************** */

#if ALL || ENQUEUE
template<class T>
void Queue<T>::enqueue(T data)
{
    // TODO: enqueue data
    // 5 Points
    Node<T> *node = new Node<T>(data);
    if(head != tail){
        tail = node;
        tail->next = nullptr;
    }else if(head == tail){
        head->next = node;
        tail = node;
        tail->next = nullptr;
    }
}
#endif

/* **************************************************************** */

#if ALL || DEQUEUE
template<class T>
T Queue<T>::dequeue()
{
    // TODO: dequeue data
    // 5 Points
    
    // This method is stubbed out, but does not return the
    // correct value.  Implement this method correctly.
    return -1;
}
#endif

/* **************************************************************** */

#if ALL || ISEMPTY
template<class T>
bool Queue<T>::isEmpty() const
{
    // TODO: return true if the list is empty, false otherwise
    // 5 Points
    
    // This method is stubbed out, but does not return the
    // correct value.  Implement this method correctly.
    return head==tail && head == nullptr;
}
#endif

/* **************************************************************** */

#if ALL || MAKEEMPTY
template<class T>
void Queue<T>::makeEmpty()
{
    // TODO: remove all data values from the queue
    // 5 Points
    head = nullptr;
    tail = nullptr;

}
#endif

/* **************************************************************** */

// DO NOT DELETE THE FOLLOWING LINE!!!
template class Queue<int>;
