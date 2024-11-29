#include <iostream>
using namespace std;


struct set_union {
    int parent[6];
    int size[6];
    int num;
};

void set_union_init(set_union* s, int n) { // initialising union find
    for (int i = 1; i <= n; i++) { // initialise each element
        s->parent[i] = i;
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
        return (find(s,s->parent[x]));
    }
}

// merge two components/sets together
int union_sets(set_union* s, int s1, int s2) {
    // define roots of sets
    int r1 = find(s,s1);
    int r2 = find(s,s2);

    if (r1 == r2) { // if already in the same set, aka sets have same root 
        return;
    }

    if (s->size[r1] >= s->size[r2]) { // if r1's tree is bigger than or equal to r2
        s->size[r1] = s->size[r1] + s->size[r2]; // resize r1 tree to hold r2
        s->parent[r2] = r1; // set r1 as the parent of r2
    }
    else { // if r2's tree is bigger than r1
        s->size[r2] = s->size[r1] + s->size[r2]; // resize r2 tree to hold r1
        s->parent[r1] = r2; //  // set r2 as parent of r1
    }
}

// check if two trees are part of the same component/tree
bool same_component(set_union* s, int s1, int s2) {
    return (find(s,s1) == find(s,s2)); // return true or false if s1 and s2 share the same root
}
