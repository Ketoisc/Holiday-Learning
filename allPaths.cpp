#include <iostream>
using namespace std;

#define MAXCANDIDATES 5
bool finished = false; // allows for termination to happen early if needed
int solution_count = 0;

struct edgenode {
    int y; // which vertex is being pointed to by the node
    int weight; // weighting of edge
    edgenode* next; // pointer to next edge node in list
};

struct graph {
    edgenode* edges[6]; // array of pointers to edgenodes
    int degree[6]; // degrees of each vertex (number of edges)
    int numVertices; // num of vertices in the graph
    int numEdges; // num of edges in the graph
    bool isDirected; // is the graph directed? (edges only go from one to the other, not both ways)
    bool processed[6]; // arrays for traversal and search
    bool discovered[6];
    int parent[6];
};

struct paths_data {
    int source;
    int target;
    graph g;
};


// find all paths from vertex s to vertex t

// tests if the first "index" elements of the vector "array" form a complete solution
// in this case, if the index has reached the last element of the set and therefore forms a complete solution
bool is_a_solution(int array[], int index, paths_data* g) {
    return (array[index] == g->target); // it is a solution if the most recent vertex in the path is the target vertex
}

// fills an array with the complete set of possible candidates for the "index" position of "array"

void construct_candidates(int array[], int index, paths_data* g, int candidates[], int *numCandidates) {
    int *numCandidates;
    bool in_solution[51];
    edgenode* tempNode;
    int lastNode;

    for (int i = 1; i <= g->g.numVertices; i++) { // initialises all values of index 1 and onwards as false, up to num of vertices since we are traversing vertices
        in_solution[i] = false;
    }

    for (int i = 0; i <= index; i++) {
        in_solution[array[i]] = true; // first index value (0) will always be true, because s is always the starting point
        // will set others as true if they are in the current path in array
    }

    if (index == 1) {
        candidates[0] = g->source; // sets first candidate as s vertex. only for first iteration
        *numCandidates = 1;
    }
    else {
        *numCandidates = 0;
        lastNode = array[index-1]; // assigns to the most recent node
        tempNode = g->g.edges[lastNode]; // assign to the outgoing edges of the most recent node
        while (tempNode != NULL) {
            if (in_solution[tempNode->y] == false) { // if the node has not been visited in the current path yet
                candidates[*numCandidates] = tempNode->y; // include it as a candidate
                *numCandidates = *numCandidates + 1;
            }
            tempNode = tempNode->next; // go to next adjacent node to the current vertex
        }
    }
}

// prints/counts/stores/processes a complete solution
// in this case, prints the current path (each value in the array)
void process_solution(int array[], int index, paths_data* g) {
    solution_count++;
    cout << "{";
    for (int i = 1; i <= index; i++) {
        cout << " " << array[i];
    }
    cout << " }" << endl;
}


void backtrack(int array[], int index, paths_data* g) {
    int candidates[MAXCANDIDATES];
    int numCandidates; // initially turns into n/input

    if (is_a_solution(array, index, g)) {
        process_solution(array, index, g); // print solution if complete
    }
    else {
        index = index + 1; // add another index
        construct_candidates(array, index, g, candidates, &numCandidates); // define candidates
        for (int i = 0; i < numCandidates; i++) { // loops through all available candidates through recursion
            array[index] = candidates[i]; // fills the array with available candidates
            //make_move(array, index, input); // allows data structures to be modified in response to the latest move if necessary
            backtrack(array, index, g); // continue looping to find all permutations by using combinations of many for loops
            //unmake_move(array, index, input); // allows data structure to be cleaned up if we want to take back the move
        }
    }

}

void generate_permutations(paths_data* g) {
    int solution[50];
    backtrack(solution, 0, g);
}

int main() {
    paths_data* g = new paths_data;
    generate_permutations(g);
    return 0;
}