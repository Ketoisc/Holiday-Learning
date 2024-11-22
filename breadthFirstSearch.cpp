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

    for (int i = 0; i < numEdges; i++) { // repeatedly ask for user input
        cout << i << " - Enter the two vertices to create an edge: ";
        cin >> x >> y;
        insert_edge(graph, x, y, isDirected); // insert the given edge
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


void initialise_search(graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->processed[i] = false;
        graph->discovered[i] = false;
        graph->parent[i] = -1;
    }
}

void bfs(graph* graph, int start) {
    queue<int> queue;
    int currVert;
    int successorVert;
    edgenode* tempNode;

    init_queue(&queue);
    enqueue(&queue, start);
}

int main() {
    graph graph;
    initialise_graph(&graph, true);
    read_graph(&graph, true);
    insert_edge(&graph, 1, 2, true);
    print_graph(&graph);
}

