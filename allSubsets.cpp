#include <iostream>
using namespace std;

#define MAXCANDIDATES 5
bool finished = false; // allows for termination to happen early if needee

// subsets for an original set of {1.....n}
// will find all subsets in the order of the original subset, including and excluding for all possibilities
// NOT permutations

// tests if the first "index" elements of the vector "array" form a complete solution
// in this case, we test for subsets, if the index has reached the last element of the set and therefore forms a complete solution
bool is_a_solution(int array[], int index, int n) {
    return (index == n);
}

// fills an array with the complete set of possible candidates for the "index" position of "array"
// in this case, we have a true or false condition on whether or not to include a value in the array
void construct_candidates(int array[], int index, int n, int candidates[], int *numCandidates) {
    candidates[0] = 0;
    candidates[1] = 1;
    *numCandidates = 2;
}

// prints/counts/stores/processes a complete solution
// in this case, prints the subset
void process_solution(int array[], int index, int input) {
    cout << "{";
    for (int i = 1; i <= index; i++) {
        if (array[i] == 1) {
            cout << " " << i; // i is the element in the set
        }
    }
    cout << " }" << endl;
}


void backtrack(int array[], int index, int input) {
    int candidates[MAXCANDIDATES];
    int numCandidates; // turns into 2 when put into construct_candidates() function

    if (is_a_solution(array, index, input)) {
        process_solution(array, index, input); // print solution if complete
    }
    else {
        index = index + 1; // add another index
        construct_candidates(array, index, input, candidates, &numCandidates); // define candidates
        for (int i = 0; i < numCandidates; i++) { // goes from 0 to 1
            array[index] = candidates[i]; // sets the current element of the set as true or false (included or excluded)
            //make_move(array, index, input); // allows data structures to be modified in response to the latest move if necessary
            backtrack(array, index, input); // continue looping through all elements in the set, assigning true or false values in loop order 
            //unmake_move(array, index, input); // allows data structure to be cleaned up if we want to take back the move
        
        // since true comes before false, the empty subset is generated first
        }
    }

}

void generate_subsets(int n) {
    int solution[50];
    backtrack(solution, 0, n);
}

int main() {
    generate_subsets(5);
    return 0;
}