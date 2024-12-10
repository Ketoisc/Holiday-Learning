#include <iostream>
#include <queue>
using namespace std;

void merge(int array[], int low, int middle, int high) {
    // queue is used because it is easy to compare and remove elements
    queue<int> elementHolder1; // holds left half of elements
    queue<int> elementHolder2; // holds right half of elements

    for (int i = low; i <= middle; i++) {
        elementHolder1.push(array[i]); // insert left half of elements in queue
    }

    for (int i = middle+1; i <= high; i++) {
        elementHolder2.push(array[i]); // insert right half of elements in queue
    }

    int index = low;
    while (!(elementHolder1.empty() || elementHolder2.empty())) { // while there are still elements in both of the queues
        if (elementHolder1.front() <= elementHolder2.front()) { // insert smaller element of both queues into array, remove from queue
            array[index++] = elementHolder1.front();
            elementHolder1.pop();
        }
        else {
            array[index++] = elementHolder2.front();
            elementHolder2.pop();
        }
    }
    while (!elementHolder1.empty()) { // if there is one element left in either elementHolder1 or 2, then also insert them
        array[index++] = elementHolder1.front();
        elementHolder1.pop();
    }

    while (!elementHolder2.empty()) { // if there is one element left in either elementHolder1 or 2, then also insert them
        array[index++] = elementHolder2.front();
        elementHolder2.pop();
    }
}



void merge_sort(int array[], int low, int high) {
    int middle; // middle element index

    if (low < high) {
        middle = (low + high) / 2; // determines middle section
        merge_sort(array, low, middle); // continues sectioning the left side
        merge_sort(array, middle+1, high); // continues sectioning the right side

        merge(array, low, middle, high); // for each section made, sort and merge them
        // array ends up sorted in O(n log n) time
    }
}