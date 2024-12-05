#include <iostream>
#include <cstring>
using namespace std; 

#define MATCH 0
#define INSERT 1
#define DELETE 2

#define MAXLEN 50

struct cell {
    int cost;
    int parent;
};

cell m[MAXLEN + 1][MAXLEN+1];

// table initialisation (rows)
void row_init(int i, cell m[MAXLEN+1][MAXLEN+1]) {
    m[0][i].cost = i; // is used in a for loop. sets 0th row as the same incrementing value
    if (i > 0) {
        m[0][i].parent = INSERT; // sets 1st row's parents as 1
    }
    else {
        m[0][i].parent = -1; // first cell (top left) has no parent
    }
}

// column initialisation
void column_init(int i, cell m[MAXLEN+1][MAXLEN+1]) {
    m[i][0].cost = i; // used in a for loop. sets the 0th column as the same incrementing value
    if (i > 0) {
        m[i][0].parent = DELETE; // sets 1st column's parents as 2
    }
    else {
        m[i][0].parent = -1; // else it is in the top left corner
    }
}

// penalty costs for matching/substitution, and insertion/deletion 
int matchCost(char c, char d) {
    if (c == d) { // if it is a match, no work is done
        return 0;
    }
    else {
        return 1; // else it is a substitution, costs 1
    }
}

int insDelCost(char c) { // cost for insertion or deletion is 1
    return 1;
}

// location of final cell containing minimum number of changes
void goal_cell(char* string, char* target, int* i, int* j) {
    // returning indices of bottom right corner of matrix
    *i = strlen(string) - 1;
    *j = strlen(target) - 1;
    return;
}


// RECONSTRUCTING PATH, AKA FINDING ORDER OF CHANGES TO GET EDIT DISTANCE

void match_out(char* s, char* t, int i, int j) {
    if (s[i] == t[j]) {
        cout << "M";
    }
    else {
        cout << "S";
    }
}

void insert_out(char* t, int j) {
    cout << "I";
}

void delete_out(char*s, int i) {
    cout << "D";
}

void reconstruct_path(char* string, char* target, int i, int j, cell m[MAXLEN+1][MAXLEN+1]) {
    if (m[i][j].parent == -1) {
        return; // recursion will stop here when there are no more valid parents
    }

    // 

    if (m[i][j].parent == MATCH) {
        reconstruct_path(string, target, i-1, j-1, m); // go back to appropriate cell
        match_out(string, target, i, j); // check and output that it was a match/substitution
        return;
    }

    if (m[i][j].parent == INSERT) {
        reconstruct_path(string, target, i, j-1, m);
        insert_out(target, j); //output that it was an insertion
        return;
    }

    if (m[i][j].parent == DELETE) {
        reconstruct_path(string, target, i-1, j, m);
        delete_out(string, j); // output that it was a deletion
        return;
    }
}


//approximate string matching
// finds minimum number (aka edit distance) of changes made to characters to convert a string into the target, using a matrix of edit distances
int string_compare(char* string, char* target, cell m[MAXLEN+1][MAXLEN+1]) {
    int optionCost[3]; // cost of the three options (match/substitution, insertion, deletion)
    int i, j, k;

    // initialising matrix
    // dedicates the -th row and column of m to store the boundary values matching the empty prefix (the space)
    for (i = 0; i <= MAXLEN; i++) {
        row_init(i, m);
        column_init(i, m);
    }

    //NOTE. THIS CODE ASSUMES THE STRINGS HAVE A BLANK SPACE IN FRONT, WHICH IS WHY WE START FROM INDEX 1
    // can always change indices accordingly if we dont want to account for spaces in strings. just for clarity in reading
    // ENABLES THE MATRIX INDICES TO BE KEPT IN SYNC WITH THE STRING INDICES FOR CLARITY
    // for each letter in the source string
    for (i = 1; i < strlen(string); i++) {

        // for each letter in the target string
        for (j = 1; j < strlen(target); j++) {
            // calculate the costs of matching/substituting, inserting, or deleting for that matrix position
            // we use the previously filled cells to fill out the matrix, filling each row one by one
            
            // fills the array of the three possible costs
            // matrix m will show the cumulative edit distances
            optionCost[MATCH] = m[i-1][j-1].cost + matchCost(string[i], target[j]); // add the previous 
            optionCost[INSERT] = m[i][j-1].cost + insDelCost(target[j]);
            optionCost[DELETE] = m[i-1][j].cost + insDelCost(string[i]);

            // initially sets the cost to be MATCH, and the parent/change to be match. is written in the matrix
            m[i][j].cost = optionCost[MATCH];
            m[i][j].parent = MATCH;

            // loops from 1 to 2
            // checks if MATCH is the lowest costing option, if not then rewrite the correct operation in the matrix
            for (k = INSERT; k <= DELETE; k++) {
                if (optionCost[k] < m[i][j].cost) {
                    m[i][j].cost = optionCost[k];
                    m[i][j].parent = k;
                }
            }
        }
    }
    // after processing and filling out whole table, find indices of final cell containing the minimum edit distance
    goal_cell(string, target, &i, &j);
    reconstruct_path(string, target, i, j, m);
    cout << " ";
    // return that value
    return (m[i][j].cost);
}



int main() {
    char* string = " thou shalt";
    char* target = " you should";
    cout << string_compare(string, target, m) << endl;
    return 0;
}