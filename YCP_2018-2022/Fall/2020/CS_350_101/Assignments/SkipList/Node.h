//
//  Node.h
//

#ifndef _NODE_H_
#define _NODE_H_

// Skiplist node class
template <class T>
class Node
{
public:
    // Constructor
    explicit Node(const T & data = T(), int height = 1)
        : data(data), height(height)
    {
        // Allocate pointer array
        next = new Node*[height];
        
        // Initialize pointers
        for(int i=0; i<height; i++)
        {
            next[i] = nullptr;
        }
    }
        
    // Destructor
    ~Node()
    {
        // Deallocate pointer array
        delete[] next;
    }
        
    // Private members
    T data;
    int height;
    Node **next;
};

#endif
