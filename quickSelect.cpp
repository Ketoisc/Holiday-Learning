#include <iostream>
#include <climits>
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

// recursively finds kth smallest element in an array without needing to sort the entire thing
int kthSmallest(int array[], int low, int high, int k) {
    int index;

    if (k > 0 && k <= high - low + 1) { // if k is a valid integer that can be indexed in the array
        index = partition(array, low, high); // make a partition

        if (index - low == k - 1) { // if the pivot is equal to the kth smallest then return the value at the index
            return array[index];
        }

        if (index - low > k - 1) { // if the pivot index is to the right of k
            return kthSmallest(array, low, index - 1, k); // partition the left side 
        }

        return kthSmallest(array, index + 1, high, k - index + low - 1); // else partition the right side
    }
    
    // if k is not valid
    return INT_MAX;
}