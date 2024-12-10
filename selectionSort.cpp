#include <iostream>
using namespace std;

void selectionSort(int array[], int size) {
    int min_index;
    for (int i = 0; i < size; i++) { // loops for all elements
        min_index = i;

        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[min_index]) { // compares current element to all other elements
                min_index = j; // finds minimum
            }
        }
        swap(array[i], array[min_index]); // brings smallest value to the front of the array, repeats until sorted
    }
}

// takes O(n^2) where n is size of array