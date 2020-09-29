#include <iostream>
#include "Histogram.h"

Histogram::Histogram(int numBuckets)
{
    // TODO: create an array of int elements,
    // assign a pointer to it to the int* field (i.e. m_counts)
    m_counts = new int[numBuckets];

    // TODO: store numBuckets in the int field (i.e., m_numBuckets)
    m_numBuckets = numBuckets;

    for (int i = 0; i < numBuckets; i++) {
        m_counts[i] = 0;
    }
}

Histogram::Histogram(const Histogram &other)
{
    // TODO: allocate new int array, copy contents from other's int array
    m_counts = new int[other.m_numBuckets];

    m_numBuckets = other.m_numBuckets;

    // TODO: copy other's bucket count
    for (int i = 0; i < other.m_numBuckets; i++) {
        m_counts[i] = other.getCount(i);
    }
}

Histogram::~Histogram()
{
    // TODO: use the delete[] operator to de-allocate
    // the array of ints
    delete[] m_counts;
}

Histogram& Histogram::operator=(const Histogram &rhs)
{
    // TODO: delete old array
    delete[] m_counts;

    // TODO: create new array, copy contents from rhs
    m_counts = new int[rhs.m_numBuckets];

    m_numBuckets = rhs.m_numBuckets;

    for (int i = 0; i < rhs.m_numBuckets; i++) {
        m_counts[i] = rhs.getCount(i);
    }

    return *this;
}

// TODO: define the other methods
void Histogram::increaseCount(int bucket)
{
    // TODO: increase the count in the specified bucket
    m_counts[bucket]++;
}

int Histogram::getCount(int bucket) const
{
    // TODO: return the count in the specified bucket
    return m_counts[bucket];
}
