#include <iostream>
using namespace std;


struct set_union {
    int parent[6];
    int size[6]; // number of elements in subtree that are rooted at i. used to determine how the subtree get merged into the larger one
    int num; // total num of elements in the set_union. remains constant
};

// starts as its own set. each element is initially its own root, and each set holds one element
void set_union_init(set_union* s, int n) { // initialising union find
    for (int i = 1; i <= n; i++) { // initialise each element
        s->parent[i] = i; // in this case we have 6 roots
        s->size[i] = 1;
    }
    s->num = n;
}

// find the root of the set
int find(set_union* s, int x) { // find the root of the set
    if (s->parent[x] == x) {
        return x;
    }
    else {
        // keep going up until root is found

        // we could have used path compression which saves time when searching for root
        return (find(s,s->parent[x])); // can be adjusted to use path compression, where we change the parent of the current element to be its root during recursive calls
    }
}

// merge two components/sets together. union by size
int union_sets(set_union* s, int s1, int s2) {
    // define roots of sets
    int r1 = find(s,s1); // r1 and r2 are roots of their respective trees
    int r2 = find(s,s2);

    if (r1 == r2) { // if already in the same set, aka sets have same root 
        return;
    }

    if (s->size[r1] >= s->size[r2]) { // if r1's tree is bigger than or equal to r2
        s->size[r1] = s->size[r1] + s->size[r2]; // update size r1 tree to hold r2. size used for future comparisons
        s->parent[r2] = r1; // set r1 as the parent of r2. merge r2 into r1
    }
    else { // if r2's tree is bigger than r1
        s->size[r2] = s->size[r1] + s->size[r2]; // update r2 tree to hold r1
        s->parent[r1] = r2; //  // set r2 as parent of r1. merge r1 into r2
    }
}

// check if two trees are part of the same component/tree
bool same_component(set_union* s, int s1, int s2) {
    return (find(s,s1) == find(s,s2)); // return true or false if s1 and s2 share the same root
}
