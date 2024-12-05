#include <iostream>
#define MAXN 50
#define MAXSUM 100
using namespace std;

//  we have a set of n positive integers
// this code checks if a subset of those elements add up to a given target k
// takes O(nk) to decide whether target k is realisable

// either

bool sum[MAXN+1][MAXSUM+1]; // table of realisable sums
int parent[MAXN+1][MAXSUM+1]; // table of parent pointers/subset of numbers that total to k

bool subset_sum(int s[], int n, int k) {
    sum[0][0] = true; // empty subset can achieve a sum of 0
    parent[0][0] = NULL; // no parents exist when there are no elements

    // initialise 
    for (int i = 1; i <= k; i++) {
        // i is elements, j is sum
        sum[0][i] = false; // no sum exists with no elements
        parent[0][i] = NULL; // therefore no parent exists when there are no elements
    }

    // build the table of sums
    // i is number of elements, j is the sum
    for (int i = 1; i <= n; i++) {  // loop through each element in the set (i)
        for (int j = 0; j <= k; j++) { // loop through each possible sum up to the target (0 to k). j is the target sum we want to check for achievability
            // case 1: exclude the current element s[i-1]
            // the nth integer is either part of a subset that adds to k, or it is not
            // here we can form the same subset without this current integer
            sum[i][j] = sum[i-1][j]; // if sum j was achievable without the current element, then we can equate this to the previous sum
            parent[i][j] = NULL; // no parent change since current element is not used

            // case 2: include the current element s[i-1]
            if ((j >= s[i-1]) && (sum[i-1][j-s[i-1]] == true)) { // if j can "fit" s[i-1], and if the remaining sum, being j-s[i-1], is achievable
                sum[i][j] = true; // then the sum j is achievable with up to the i'th element
                parent[i][j] = j - s[i-1]; // track previous sum to reconstruct subset
            }
        }
    }
    return (sum[n][k]); // bottom right cell determines is sum is achievable using the entirer set
}

// prints the subset itself
// takes O(n) to traverse the parent table
void report_subset(int n, int k) {
    if (k == 0) {
        return;
    }

    // walk up the matrix until we find an interesting parent (where sum[n][k] == true but does not use s(n) as an element when parent[n][k] is null)
    if (parent[n][k] == NULL) {
        report_subset(n-1, k);
    }
    else {
        report_subset(n-1, parent[n][k]);
        cout << " " << k-parent[n][k] << " ";
    }
}
