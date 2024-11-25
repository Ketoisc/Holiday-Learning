#include <iostream>
#include <cmath>
using namespace std;
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
        return (floor(n/2));
    }
}

int pq_young_child(int n) {
    return (2*n);
}

// swapping current node with its parent
void pq_swap(priority_queue* queue, int currNode, int parentNode) {
    int temp = queue->queue[currNode];
    queue->queue[currNode] = queue->queue[parentNode];
    queue->queue[parentNode] = temp;
    return;
}


// bubbling up means comparing if parent of currNode is greater (for min heap). 
// If parent is greater, swap the nodes and recursively call again until currNode is in right spot
void bubble_up(priority_queue* p_queue, int currNode) {
    if (pq_parent(currNode) == -1) { // if at the root of heap with no parent
        return; 
    }

    // if parent is greater than currNode, swap (min heap)
    if (p_queue->queue[pq_parent(currNode)] > p_queue->queue[currNode]) {
        pq_swap(p_queue, currNode, pq_parent(currNode));
        bubble_up(p_queue, pq_parent(currNode)); // call again until node is in correct spot
    }
}

// one insertion takes O(log n) because we bubble up the height of the tree
void pq_insert(priority_queue* queue, int x) {
    if (queue->numElements >= 10) {
        cout << "Priority queue insertion overflow" << endl;
        return;
    }
    else {
        queue->numElements = queue->numElements + 1; // increment num of elements to have a reference of an empty index for element to go into
        queue->queue[queue->numElements] = x; // go to most recent available space
        bubble_up(queue, queue->numElements); // bubble up to correct position
    }
}

// initialise num elements as 0
void pq_init(priority_queue* queue) {
    queue->numElements = 0;
}

// insert all elements from a given array
void make_heap(priority_queue* queue, int array[], int size) {
    pq_init(queue);
    for (int i = 0; i < size; i++) {
        pq_insert(queue, array[i]);
    }
}


