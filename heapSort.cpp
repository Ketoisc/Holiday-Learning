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


// FOR MIN HEAP, EXTRACT THE MINIMUM

// bubbling down means comparing if child of currNode is lesser (for min heap). 
// If child is lesser, swap the nodes and recursively call again until currNode is in right spot
// ALSO KNOWN AS HEAPIFY
void bubble_down(priority_queue* p_queue, int currNode) {
    int childIndex;
    int minIndex;

    childIndex = pq_young_child(currNode); // the left child
    minIndex = currNode;

    for (int i = 0; i < 2; i++) { // for loop to compare BOTH left and right children by adding 0 and then 1 (children are next to each other in array)
    // ensures that both children are checked and the smaller is bubbled up
        if ((childIndex + i) <= p_queue->numElements) { // if the child index is within the priority queue
            if (p_queue->queue[minIndex] > p_queue->queue[childIndex + i]) { // check if current index is greater than the child
                minIndex = childIndex + i; // change min to that child
            }
        }
    }

    // if a swap has been discovered, make the swap in the priority queue
    if (minIndex != currNode) {
        pq_swap(p_queue, currNode, minIndex); // swap current node 
        bubble_down(p_queue, minIndex); // call again until node is in correct spot
    }
}

// get minimum from top of heap (min heap)
int extract_min(priority_queue* queue) {
    int min;

    if (queue->numElements <= 0) {
        cout << "Empty priority queue" << endl;
    }
    else {
        min = queue->queue[1]; // take the first element since min is at the top of heap
        queue->queue[1] = queue->queue[queue->numElements]; // replace old min with the last element in the heap
        queue->numElements = queue->numElements - 1; // decrement num of elements
        bubble_down(queue, 1);

    }
    return min;

}

// heapsort
int* heapsort(int array[], int size) {
    priority_queue queue;
    make_heap(&queue, array, size); // make a priority queue and turn it into a min heap

    for (int i = 0; i < size; i++) {
        array[i] = extract_min(&queue); // repeatedly extract minimum and calling heapify to get a sorted array
    }
    return array;
}

int main() {
    int array[4] = {3,6,2,8};
    int size = 4;

    heapsort(array, size);

    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}