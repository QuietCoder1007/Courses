#include <iostream>
#include "Histogram.h"

// Constructor
Histogram::Histogram(int numBuckets)
{
    // TODO: create an array of int elements and
    // assign it to the global m_counts int* (int pointer)
    // provided in the Histogram.h header file

    m_counts = new int[numBuckets] ;

    for (int i = 0; i < numBuckets; i++) {
        m_counts[i] = 0;
    }

}

// Destructor
Histogram::~Histogram()
{
    // TODO: use the delete[] operator to de-allocate
    // the array of ints
    delete[] m_counts;
}

// TODO: define the other methods
// (the body of each method should only require a single line)
void Histogram::increaseCount(int bucket){
    m_counts[bucket]++;
};

int Histogram::getCount(int bucket){
    return m_counts[bucket];
};