#include <iostream>
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

    bool finished = false;
    int time = 0;
    int entry_time[6];
    int exit_time[6];
};

void initialise_graph(graph* graph, bool isDirected) {
    graph->numVertices = 0; // setting graph as empty
    graph->numEdges = 0;
    graph->isDirected = isDirected;

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

void read_graph(graph* graph, bool isDirected) { // aka setting up the graph with values
    int numEdges;
    int x; // starting vertex x in edge
    int y; // ending vertex y in edge

    initialise_graph(graph, isDirected); // initialises graph

    cout << "Enter the number of vertices and edges seperated by a space: ";
    cin >> (graph->numVertices) >> numEdges; // takes user input for num of vertices and edges

    // note: no input sanitation. assumes the inputs are valid
        for (int i = 1; i <= numEdges; i++) { // repeatedly ask for user input
            cout << " - Enter the start and end vertex to create an edge: ";
            cin >> x >> y;
            insert_edge(graph, x, y, isDirected); // insert the given edge
        }
    
    return;
}

void print_graph(graph* graph) { // prints each vertices and their connections/edges with other vertices
    edgenode* node; // temporary node holder to be used for printing

    for (int i = 1; i <= graph->numVertices; i++) { // for each array index (num of vertices)
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


// Depth first search
// typically uses a stack instead of a queue (bfs)
// however, doesn't need a stack if you use recursion

// entry and exit times are tracked
// time is incremented on each vertex entry and vertex exit
// for undirected graphs, it organises edges into tree and back edges

// DFS USING RECURSION
void dfs(graph* graph, int currVert) {
    edgenode* tempNode;
    int successorVert;

    if (graph->finished == true) {
        return;
    }

    graph->discovered[currVert] = true; // set current vertex as discovered
    graph->time = graph->time + 1;
    graph->entry_time[currVert] = graph->time; // calculate and insert the entry/discovery time of the current vertex

    process_vertex_early(currVert); // processing if wanted
    tempNode = graph->edges[currVert]; // check edges/connecting vertices of the current vertex by making tempnode

    while (tempNode != NULL) { // while there are still vertices/edges to be discovered
        successorVert = tempNode->y; // sets successor node to be searched by using the temp edgenode. y is the next vertex
        // processing tree edges
        if (graph->discovered[successorVert] == false) { // if the next node hasnt been discovered
            graph->parent[successorVert] = currVert; // set the next node's parent as the old current vertex
            process_edge(currVert, successorVert); // process the edge between the current and successor vertex
            dfs(graph, successorVert); // recursively call dfs again
        }

        // processing back edges, handles the revisiting of nodes in directed graphs
        else if ((graph->processed[successorVert] == false && (graph->parent[currVert] != successorVert))  // if successor vertex hasn't been processed/directed graph
        || graph->isDirected == true) {
            process_edge(currVert, successorVert);
            if (graph->finished ==  true) {
                return;
            }
        }
        tempNode = tempNode->next; // go to next node to find more edges
    }

    process_vertex_late(currVert);
    graph->time = graph->time + 1;
    graph->exit_time[currVert] = graph->time; // indicates when the vertex has finished processing
    graph->processed[currVert] = true; // marks vertex (including all of its edges) as processed

    // graph->finished can be set to true during processing if we want to stop the traversal early 
    // (eg finding a target node, detecting cycle)

}

int main() {
    graph graph;
    read_graph(&graph, true);
    print_graph(&graph);

    initialise_search(&graph);
    dfs(&graph, 1);
}
