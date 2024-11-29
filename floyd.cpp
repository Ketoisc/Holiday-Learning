#include <iostream>
using namespace std;

struct adjacency_matrix {
    int weight[6][6]; // weight of x to y. a matrix containing the adjacency and weight info
    int numVertices; // num of vertices in graph. graph is n x n
};

// assuming the graph already contains 0s as diagonal and max_int values for non-direct edges. aka when k = 0
void floyd(adjacency_matrix* graph) {

    int dist_through_k;

    for (int k = 1; k <= graph->numVertices; k++) { // goes through each intermediate vertex (A1, A2, A3... it picks which vertex k is the connecting point)
        for (int i = 1; i <= graph->numVertices; i++) {
            for (int j = 1; j <= graph->numVertices; j++) {
                dist_through_k = graph->weight[i][k] + graph->weight[k][j]; // calculate distance of vertex x to y using k as a midpoint

                if (dist_through_k < graph->weight[i][j]) { // if this distance is smaller than what is currently in there
                    graph->weight[i][j] = dist_through_k; //replace it with this value
                }
            }
        }
    }
}
