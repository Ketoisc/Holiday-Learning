#include <iostream>
#include <climits>
using namespace std;

// edgenode struct to hold the edge weight (if applicable) and pointer to next edgenode
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

void prim(graph* graph, int start) {
    edgenode* tempNode; // temporary pointer
    bool inTree[6]; // is the vertex in the tree yet?
    int distance[6]; // cost of adding vertex to tree (distance/weight of edge)
    int currVert; // current vertex to process
    int potentialNextVert; // candidate next vertex
    int weight; // edge weight
    int dist; // best current distance from start

    for (int i = 1; i <= graph->numVertices; i++) { // initialising array values
        inTree[i] = false;
        distance[i] = INT_MAX; // infinity
        graph->parent[i] = -1;
    }

    distance[start] = 0;
    currVert = start;

    while (inTree[currVert] == false) { // while the current vertex is not in the prim tree yet
        inTree[currVert] = true; // insert into tree
        tempNode = graph->edges[currVert]; // check edges of the current vertex

        while (tempNode != NULL) { // while there are still edges on this vertex, traverse the adjacency list of currVert
            potentialNextVert = tempNode->y; // set potential next vertex as the target node (aka ending vertex of edge)
            weight = tempNode->weight; // check edge weight

            if ((distance[potentialNextVert] > weight) && (inTree[potentialNextVert] == false)) { // if current node's weight is smaller than the next vertex's weight, and the next one is not in the tree
                distance[potentialNextVert] = weight; // set the next vertex's weight
                graph->parent[potentialNextVert] = currVert; // set its parent
            }
            tempNode = tempNode->next; // go to next node to loop for all edges
        }

        // selecting the next vertex to process
        currVert = 1; // set to 1 in case no valid vertex is found
        int dist = INT_MAX; // tracks smallest distance so far. any edge weight will replace it bc of infinity
        for (int i = 1; i <= graph->numVertices; i++) { // for each vertex
            if ((inTree[i]) == false && (dist > distance[i])) { // check it is not in the tree & the weight of the edge is smaller than dist
                dist = distance[i]; // sets new minimum distance for this vertex's adjacent nodes, ensures the lowest adjacent edge weight is found from all 
                currVert = i; // picks next vertex for loop to continue making the MST
            }
        }
    }
}