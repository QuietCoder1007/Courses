#ifndef HISTOGRAM_H
#define HISTOGRAM_H

class Histogram {
private:
    // fields go here...
    int *m_counts;    // pointer to array of counters
    int m_numBuckets; // number of elements in the array

public:
    explicit Histogram(int numBuckets);
    Histogram(const Histogram &other);
    ~Histogram();

    Histogram& operator=(const Histogram &rhs);

    void increaseCount(int bucket);
    int getCount(int bucket) const;
};

#endif
