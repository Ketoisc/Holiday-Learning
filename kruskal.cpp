#include <iostream>
using namespace std;

// edgenode struct to hold the edge weight (if applicable) and pointer to next edgenode
struct edge {
    int x;
    int y; // which vertex is being pointed to by the node
    int weight; // weighting of edge
};

struct graph {
    edge* edges[6]; // array of pointers to edgenodes
    int degree[6]; // degrees of each vertex (number of edges)
    int numVertices; // num of vertices in the graph
    int numEdges; // num of edges in the graph
    bool isDirected; // is the graph directed? (edges only go from one to the other, not both ways)
    bool processed[6]; // arrays for traversal and search
    bool discovered[6];
    int parent[6];
};


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

// code from adm
int kruskal(graph *g) {
    int i; /* counter */
    union_find s; /* union-find data structure */
    edge_pair e[MAXV+1]; /* array of edges data structure */
    int weight = 0; /* cost of the minimum spanning tree */

    union_find_init(&s, g->nvertices);
    to_edge_array(g, e);

    qsort(&e,g->nedges, sizeof(edge_pair), &weight_compare);

    for (i = 0; i < (g->nedges); i++) {
        if (!same_component(&s, e[i].x, e[i].y)) {
            printf("edge (%d,%d) in MST\n", e[i].x, e[i].y);
            weight = weight + e[i].weight;
            union_sets(&s, e[i].x, e[i].y);
        }
    }
return(weight)
}