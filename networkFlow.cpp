#include <iostream>
#include <queue>
using namespace std;

struct edgenode {
    int v; // neighbouring vertex
    int capacity; // capacity of edge
    int flow; // flow through edge
    int residual; // residual capacity of edge
    edgenode* next; // next edge in list
};

struct flow_graph {
    edgenode* edges[6]; // array of pointers to edgenodes
    int degree[6]; // degrees of each vertex (number of edges)
    int numVertices; // num of vertices in the graph
    int numEdges; // num of edges in the graph
    bool isDirected; // is the graph directed? (edges only go from one to the other, not both ways)
    bool processed[6]; // arrays for traversal and search
    bool discovered[6];
    int parent[6];
};

void initialise_graph(flow_graph* graph, bool isDirected) {
    graph->numVertices = 0; // setting graph as empty
    graph->numEdges = 0;
    graph->isDirected = isDirected;

    for (int i = 1; i <= 6; i++) {
        graph->degree[i] = 0;
        graph->edges[i] = NULL;
    }
    return;
}
void process_vertex_early(int vertex) { // can be adjusted to have other functionality
    cout << "Processed vertex " << vertex << endl;
    return;
}

void process_vertex_late(int vertex) {} // can be adjusted to have other functionality

void process_edge(int x, int y) { // processes edges, counts num of edges traversed
    cout << "Processed edge " << x << " " << y << endl;
    static int edgesCount = 0;
    edgesCount++;
    cout << "Current edge count: " << edgesCount << "\n" << endl;
    return;
}

// breadth first search
void bfs(flow_graph* graph, int start) {
    queue<int> queue; // initialise queue (FIFO)
    int currVert; // current vertex being explored
    int successorVert; // neighbouring vertex connected to currVert
    edgenode* currNode; // points to the edges/connections of the current vertex currVert

    queue.push(start); // insert the starting vertex into the queue
    graph->discovered[start] = true; // first/starting vertex has been marked as discovered

    while (!queue.empty()) { // continue searching until queue is empty/no more vertices left to search
        currVert = queue.front(); // set current vertex as the first value in the queue
        queue.pop(); // remove value from queue
        process_vertex_early(currVert); // can be commented out. depending on the wanted functionality of bfs, you can process the node early or late
        graph->processed[currVert] = true; // set this node as processed
        currNode = graph->edges[currVert]; // check current node's edges/connections with other nodes by accessing its adjacency list
        //currNode is now one of the connected vertices to the current vertex

        while (currNode != NULL) { // while there are still neighbours to the node/s, traverse all neighbours of currVert using its adjacency list
            successorVert = currNode->y; // set successor vertex to check if it has been discovered/processed before
            
             // if the successor vertex has NOT been processed, or the graph is directed
             // condition 1 is to satisfy undirected graphs, because the same edge will appear twice. you don't want to process the same thing twice, so we check that
             // condition 2 is to ensure that every edge is only processed once, because direction matters in directed graphs. 
             // already processed vertices will never be processed again, because only undiscovered vertices are added to the queue
             // need to process every edge because direction matters in directed graphs. wont be an infinite loop since currNode changes
            if ((graph->processed[successorVert] == false) || graph->isDirected) {
            // focuses on processing edges
                process_edge(currVert, successorVert); // process the edge
            }

            // only undiscovered nodes are added to the queue
            if (graph->discovered[successorVert] == false) { // if successorVert has not been marked as discovered
            // focuses on node traversal
                queue.push(successorVert); // add successor to the queue to be checked
                graph->discovered[successorVert] = true; // mark as discovered
                graph->parent[successorVert] = currVert; // define the current vertex as the parent of the successor
            }
            // both if statements are called if the successorVert is undiscovered. ensures that the edge is processed and the node can be further explored

            // follow the adjacency list pointer to go to next one
            currNode = currNode->next; // go to next edge node, aka the next item in the adjaency list or the next neighbour/connection vertex
        }
        process_vertex_late(currVert); // process if wanted
    }

}

// only consider edges that have some capacity available (aka positive residual flow)
bool valid_edge(edgenode* edge) {
    if (edge->residual > 0) {
        return true;
    }
    else {
        return false;
    }
}

int path_volume(flow_graph* graph, int start, int end, int parents[]) {
    edgenode* e;

    if (parents[end] == -1) {
        return 0;
    }
    
    e = find_edge(graph, parents[end], end);

    if (start == parents[end]) {
        return e->residual;
    }
    else {
        return min(path_volume(graph, start, parents[end], parents), e->residual);
    }
}

edgenode* find_edge(flow_graph* graph, int x, int y) {
    edgenode* tempNode;

    tempNode = graph->edges[x];

    while (tempNode != NULL) {
        if (tempNode->v == y) {
            return tempNode;
        }
    }
    return NULL;
}


void augment_path(flow_graph* graph, int start, int end, int parents[], int volume) {
    edgenode* edge;

    if (start == end) {
        return;
    }

    edge = find_edge(graph, parents[end], end);
    edge->flow += volume;
    edge->residual -= volume;

    edge = find_edge(graph, end, parents[end]);
    edge->residual += volume;

    augment_path(graph, start, parents[end], parents, volume);
}

// use a bfs to look for any path from s to t that increases total flow. use this to augment the total flow
// terminate with the optimal flow when no such augmenting path exists

void netflow(flow_graph* graph, int source, int sink) {
    int volume;

    add_residual_edges(graph);

    initialise_search(graph);
    bfs(graph, source);

    volume = path_volume(graph, source, sink, parent);

    while (volume > 0) {
        augment_path(graph, source, sink, parent, volume);
        initialise_search(graph);
        bfs(graph, source);
        volume = path_volume(graph, source, sink, parent);
    }
}
