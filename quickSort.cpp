#include <iostream>
using namespace std;

int partition(int array[], int low, int high) {
    int pivotIndex;
    int firstHigh; // divider position for pivot element. this gets incremented every time an element less than the pivot is found
    // will eventually give the final position of the pivot

    pivotIndex = high; // pivot is last element
    firstHigh = low; // starts at first element

    for (int i = low; i < high; i++) { // go through the array/current partition
        if (array[i] < array[pivotIndex]) { 
            swap(array[i], array[firstHigh]); // swap elements less than the pivot
            firstHigh++; // increment
        }
    }
    swap(array[pivotIndex], array[firstHigh]); // ensures pivot is in correct final position
    return firstHigh;
}

void quicksort(int array[], int low, int high) { // creates all partitions recursively
    int partitionIndex;

    if (low < high) { // makes partitions until it only consists of one element
        partitionIndex = partition(array, low, high); // each partition "sorts" elements with respect to the pivot
        quicksort(array, low, partitionIndex - 1);
        quicksort(array, partitionIndex + 1, high);
    }
}

// takes O(n log n). log n for all partitioning/halving, n amount of work to go through all elements in the partition. across all partitioning levels, n work is done