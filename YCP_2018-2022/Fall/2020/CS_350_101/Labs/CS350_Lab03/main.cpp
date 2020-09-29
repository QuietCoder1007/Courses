#include <iostream>
#include <cassert>
#include "Histogram.h"

void check(const Histogram &h);

int main()
{
    Histogram h1(10);

    // Initialize h1 so that the count in each bucket is the
    // same as its index
    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < j; i++) {
            h1.increaseCount(j);
        }
    }

    // Check contents of h1
    check(h1);

    // Use the copy constructor to make a copy of h1
    Histogram h2(h1);

    // It should be identical to h1
    check(h2);

    // Use the assignment operator to make a copy of h1
    Histogram h3(4);
    h3 = h1;

    // It should be identical to h1
    check(h3);

    // Make a copy of a copy
    Histogram h4(2);
    h4 = h3;

    // Now, modify h1.  h2 and h3 should not change
    h1.increaseCount(4);
    h1.increaseCount(7);

    check(h2);
    check(h3);
    check(h4);

    std::cout << "End of main: everything is OK?" << std::endl;

    return 0;
}

void check(const Histogram &h)
{
    for (int i = 0; i < 10; i++) {
        assert(h.getCount(i) == i);
    }
}
