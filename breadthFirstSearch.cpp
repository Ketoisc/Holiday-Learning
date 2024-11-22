#include <iostream>
#include <queue>
using namespace std;


// adjacency lists can efficiently represent sparse graphs 
// using linked lists to store the neighbours adjacent to each vertex

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
    bool processed[6];
    bool discovered[6];
    int parent[6];
};

void initialise_graph(graph* graph, bool isDirected) {
    graph->numVertices = 0; // setting graph as empty
    graph->numEdges = 0;
    graph->isDirected = true;

    for (int i = 0; i < 6; i++) {
        graph->degree[i] = 0;
        graph->edges[i] = NULL;
    }
    return;
}

void insert_edge(graph* graph, int x, int y, bool isDirected) {
    edgenode* node; 
    node = new edgenode(); // allocate space for new node
    node->weight = 0; // initialise all values of the node to be inserted
    node->y = y; // ending vertex of the edge
    node->next = graph->edges[x]; // the node to be inserted now points to the pointer currently inhabiting edges[x]. will initially be null
    // this is so that the new node is inserted at the head of the list, since order does not matter when making edges
    // ensures the linked list is connected and no existing nodes are lost

    graph->edges[x] = node; // insert the new node
    graph->degree[x] += 1; // increment that vertex's degree by 1 (degree means number of edges)

    if (isDirected == false) { // if the graph is undirected, another edge needs to be added to the ending vertex to have a two-way edge connection
        insert_edge(graph, y, x, true); // recursively call itself to insert the right edge
    }
    else {
        graph->numEdges++; // increment number of edges
    }
    return;
}

void read_graph(graph* graph, bool isDirected) {
    int numEdges;
    int x; // starting vertex x in edge
    int y; // ending vertex y in edge

    initialise_graph(graph, isDirected); // initialises graph

    cout << "Enter the number of vertices and edges seperated by a space: ";
    cin >> (graph->numVertices) >> numEdges; // takes user input for num of vertices and edges

    // note: no input sanitation. assumes the inputs are valid
    for (int j = 0; j < graph->numVertices; j++) {
        cout << "Vertex " << j << endl;
        for (int i = 1; i <= numEdges; i++) { // repeatedly ask for user input
            cout << "Edge " << i << " - Enter the connecting vertex to create an edge: ";
            cin >> y;
            insert_edge(graph, j, y, isDirected); // insert the given edge
        }
    }
    return;
}

void print_graph(graph* graph) {
    edgenode* node; // temporary node holder to be used for printing

    for (int i = 0; i < graph->numVertices; i++) { // for each array index (num of vertices)
        cout << "Vertex " << i << ": " << endl; // print starting vertex
        node = graph->edges[i]; // set node to first index
        while (node != NULL) { // while the current node (in the list) has a vertex
            cout << node->y << " ";
            node = node->next; // go to next node in the list in that index
        }
        cout << "\n" << endl;
        // go to next index
    }
    return;
}

// initialising the graph so each vertex is initialised as undiscovered/unprocessed with no parents
void initialise_search(graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->processed[i] = false;
        graph->discovered[i] = false;
        graph->parent[i] = -1;
    }
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
void bfs(graph* graph, int start) {
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


int main() {
    graph graph;
    initialise_graph(&graph, true);
    read_graph(&graph, true);
    insert_edge(&graph, 1, 2, true);
    print_graph(&graph);

    initialise_search(&graph);
    bfs(&graph, 0);
}

