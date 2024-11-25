#include <iostream>

// supports priority queue operations (insert, min/max)
// maintains a partial order, aka a less strict binary search tree
// can be min heap or max heap

// pointers not used, instead uses position of array indices for constant time access
// assume array starts at 1 for simplicity

struct priority_queue {
    int queue[11];
    int numElements;
};

int pq_parent(int n) {
    if (n == 1) {
        return -1;
    }
    else {
        return (n/2);
    }
}