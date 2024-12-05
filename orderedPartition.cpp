#include <iostream>
#include <climits>
using namespace std;

#define MAXN 50
#define MAXK 55

// the ordered partition problem
// we have a set of numbers, and we want to split it into a number of partitions so that their sums are similar
// aka the maximum sum of any partition is minimised


void print_books(int set[], int start, int end) {
    cout << "\{";
    for (int i = start; i <= end; i++) {
        cout << " " << set[i];
    }
    cout << "}\n";
}

void reconstruct_partition(int set[], int dividers[MAXN+1][MAXK+1], int size, int partitions) {
    if (partitions == 1) {
        print_books(set, 1, size); // print elements up to size, just one partition so its whole set
    }
    else {
        reconstruct_partition(set, dividers, dividers[size][partitions], partitions-1); // find the split position, use recursion up to partitions-1
        print_books(set, dividers[size][partitions]+1, size);
    }
}

// takes O(kn^2), where k is the number of partitions. we select the best of up to n points to place the divider, each requiring the sum of up to n terms

void partition(int set[], int size, int partitions) {
    int prefixSums[MAXN + 1]; // the sum of the first i elements of the array
    int values[MAXN+1][MAXK+1]; // the minimum possible maximum sum achievable when dividing the first i elements of the set into j partitions
    int dividers[MAXN+1][MAXK+1]; // records position where the last partition starts when dividing the first i elements into j partitions

    int cost;

    prefixSums[0] = 0;
    for (int i = 1; i <= size; i++) {
        // i is elements up to i, j is number of partitions
        prefixSums[i] = prefixSums[i-1] + set[i]; // computes sum of the first i elements of the set, fills out array. e.g. 3rd element is sum of 1st and 2nd
        values[i][1] = prefixSums[i]; // initialise boundaries. if there is only 1 partition, all elements up to i go into the partition
    }

    for (int j = 1; j <= partitions; j++) {
        values[1][j] = set[1]; // if there is only one element, its value is the maximum sum for any number of partitions
        // if theres only one element in j partitions, each partition holds that element?
    }

    // evaluate main recurrence
    for (int i = 2; i <= size; i++) { // loops through num of elements
        for (int j = 2; j <= partitions; j++) { // loops through num of partitions
            values[i][j] = INT_MAX;
            for (int x = 1; x <= (i-1); x++) { // testing all possible POSITIONS to split the array, from index 1 to i-1 (i is current element of set)
                cost = max(values[x][j-1], prefixSums[i] - prefixSums[x]); // for each split position, compute cost of the worst/max value partition
                // compare the maximum sum from dividing x elements into j-1 partitions, vs the sum of the last partition from x+1 to i
                if (values[i][j] > cost) { // if the calculated partition cost is lower, update values[i][j] and record the position in dividers array
                    values[i][j] = cost;
                    dividers[i][j] = x;
                }
            }
        }
    }
    reconstruct_partition(set, dividers, size, partitions);
}