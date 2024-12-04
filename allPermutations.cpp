#include <iostream>
using namespace std;

#define MAXCANDIDATES 5
bool finished = false; // allows for termination to happen early if needee

// permutations of an original set of {1.....n}

// tests if the first "index" elements of the vector "array" form a complete solution
// in this case, if the index has reached the last element of the set and therefore forms a complete solution
bool is_a_solution(int array[], int index, int n) {
    return (index == n);
}

// fills an array with the complete set of possible candidates for the "index" position of "array"

void construct_candidates(int array[], int index, int n, int candidates[], int *numCandidates) {
    bool in_permutation[50]; // tracks which elements are already included in the current permutation
    // therefore any element that is not in this array is a valid candidate

    for (int i = 1; i < 50; i++) {
        in_permutation[i] = false; // initialises array to be all false
    }

    for (int i = 1; i < index; i++) {
        in_permutation[array[i]] = true; // sets all current positions as true. array is the current permutation/partial solution
    }

    *numCandidates = 0; // starts filling array from index 0

    for (int i = 1; i <= n; i++) { // loops for all values from 1 to n in the original list of elements
        if (in_permutation[i] == false) {
            candidates[*numCandidates] = i; // candidates now holds the unused numbers and their count
            *numCandidates = *numCandidates + 1; // keeps count of candidates
        }
    }
}

// prints/counts/stores/processes a complete solution
// in this case, prints the current permutation (each value in the array)
void process_solution(int array[], int index, int input) {
    cout << "{";
    for (int i = 1; i <= index; i++) {
        cout << " " << array[i];
    }
    cout << " }" << endl;
}


void backtrack(int array[], int index, int input) {
    int candidates[MAXCANDIDATES];
    int numCandidates; // initially turns into n/input

    if (is_a_solution(array, index, input)) {
        process_solution(array, index, input); // print solution if complete
    }
    else {
        index = index + 1; // add another index
        construct_candidates(array, index, input, candidates, &numCandidates); // define candidates
        for (int i = 0; i < numCandidates; i++) { // loops through all available candidates through recursion
            array[index] = candidates[i]; // fills the array with available candidates
            //make_move(array, index, input); // allows data structures to be modified in response to the latest move if necessary
            backtrack(array, index, input); // continue looping to find all permutations by using combinations of many for loops
            //unmake_move(array, index, input); // allows data structure to be cleaned up if we want to take back the move
        }
    }

}

void generate_permutations(int n) {
    int solution[50];
    backtrack(solution, 0, n);
}

int main() {
    generate_permutations(5);
    return 0;
}