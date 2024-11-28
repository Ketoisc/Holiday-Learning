#include <iostream>
#include <stack>
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

    int reachable_ancestor[6]; // earliest reachable ancestor of vertex, USING A BACK EDGE
    int tree_out_degree[6]; // dfs tree outdegree of vertex

    stack<int> dfsStack;

    stack<int> activeStack; // keeps track of vertices in the current dfs tree
    int low[6]; // oldest vertex in component of v
    int scc[6]; // strong component number for each vertex for iedntification
    int components_found;
};

void initialise_graph(graph* graph, bool isDirected) {
    graph->numVertices = 0; // setting graph as empty
    graph->numEdges = 0;
    graph->isDirected = isDirected;

    for (int i = 1; i <= 6; i++) {
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

void process_vertex_early(graph* graph, int vertex) {
    graph->activeStack.push(vertex);
}

void pop_component(graph* graph, int vertex) {
    int currVert; // vertex placeholder
    graph->components_found = graph->components_found + 1; // add 1, new component has been found
    graph->scc[vertex] = graph->components_found; // labelling the vertex with its component number

    while (currVert != vertex) { // going through all nodes in the stack until it reaches the root of the SCC (vertex)
        currVert = graph->activeStack.top();
        graph->scc[currVert] = graph->components_found; // label all of the current vertex's children to be in the same component
        graph->activeStack.pop(); // remove from stack
    }
}

void process_vertex_late(graph* graph, int vertex) { 
    if (graph->low[vertex] == vertex) { // if the edge from parent[v] to v cuts off a strongly connected component, it means that vertex is the ROOT of a new SCC
        pop_component(graph, vertex); // identifies component by removing/popping vertices from the stack. forms SCCs and labels components
    }

    if (graph->parent[vertex] > 0) { // only if vertex is not the root
        if (graph->entry_time[graph->low[vertex]] < graph->entry_time[graph->low[graph->parent[vertex]]]) { // if the entry time of the oldest reachable vertex of the current vertex is less than that of its parent
            graph->low[graph->parent[vertex]] = graph->low[vertex]; // set the parent's oldest reachable vertex to its child (vertex)
        }
    }
} 

// classifying edges
//
string edge_classification(graph* graph, int x, int y) {
    if (graph->parent[y] == x) { // if x is the parent of y, for edge x to y
        return "TREE"; // tree edge
    }

    if ((graph->discovered[y] == true) && (graph->processed[y] == false)) { // if y has been discovered but not processed, for edge x to y
        return "BACK"; // back edge
    }

    if ((graph->processed[y] == true) && (graph->entry_time[y] > graph->entry_time[x])) { // if y has been processed and has an entry time greater than x (x was discovered first before y), for edge x to y
        return "FORWARD"; // forward edge
    }

    if ((graph->processed[y] == true) && (graph->entry_time[y] < graph->entry_time[x])) { // if y has been processed and has an entry time lower than x (y was discovered first before x)
        return "CROSS";
    }

    cout << "Unclassified edge" << endl; // else unclassified
    return "";
}


void process_edge(graph* graph, int x, int y) { // processes edges 
    string edgeClass; // edge class
    edgeClass = edge_classification(graph, x, y); // classify the edge

    if (edgeClass == "BACK") { // if it is a back edge, it is a cycle
        if (graph->entry_time[y] < graph->entry_time[graph->low[x]]) { // if y was discovered before x, set the oldest reachable vertex of x to y (back edge)
            graph->low[x] = y;
        }
    }

    if (edgeClass == "CROSS") {
        if (graph->scc[y] == -1) { // if a component has not been assigned to the vertex
            if (graph->entry_time[y] < graph->entry_time[graph->low[x]]) { // if y was discovered before x, set the oldest reachable vertex of x to y (back edge)
                graph->low[x] = y;
            }
        }
    }
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
    graph->low[currVert] = graph->time; // low is set to discovery time

    process_vertex_early(graph, currVert); // vertex has been discovered, push onto active stack
    tempNode = graph->edges[currVert]; // check edges/connecting vertices of the current vertex by making tempnode

    while (tempNode != NULL) { // while there are still vertices/edges to be discovered
        successorVert = tempNode->y; // sets successor node to be searched by using the temp edgenode. y is the next vertex
        // processing tree edges
        if (graph->discovered[successorVert] == false) { // if the next node hasnt been discovered
            graph->parent[successorVert] = currVert; // set the next node's parent as the old current vertex
            process_edge(graph, currVert, successorVert); // process the edge between the current and successor vertex
            dfs(graph, successorVert); // recursively call dfs again
        }

        // processing back edges, handles the revisiting of nodes in directed graphs
        else if ((graph->processed[successorVert] == false && (graph->parent[currVert] != successorVert))  // if successor vertex hasn't been processed/directed graph
        || graph->isDirected == true) {
            process_edge(graph, currVert, successorVert);
            if (graph->finished ==  true) {
                return;
            }
        }
        tempNode = tempNode->next; // go to next node to find more edges
    }

    process_vertex_late(graph, currVert); // add to stack for top sort
    graph->time = graph->time + 1;
    graph->exit_time[currVert] = graph->time; // indicates when the vertex has finished processing
    graph->processed[currVert] = true; // marks vertex (including all of its edges) as processed

    // graph->finished can be set to true during processing if we want to stop the traversal early 
    // (eg finding a target node, detecting cycle)

}

void strong_components(graph* graph) {
    for (int i = 1; i <= graph->numVertices; i++) {
        graph->low[i] = i;
        graph->scc[i] = -1;
    }
    graph->components_found = 0;
    initialise_search(graph);
    for (int i = 1; i <= graph->numVertices; i++) {
        if (graph->discovered[i] == false) {
            dfs(graph, i);
        }
    }

    for (int i = 1; i <= graph->numVertices; i++) {
        if (graph->scc[i] != -1) {
            cout << "Vertex " << i << " is in SCC #" << graph->scc[i] << endl;
        }
    }
    return;
}

int main() {
    graph graph;
    read_graph(&graph, true);
    print_graph(&graph);

    initialise_search(&graph);
    strong_components(&graph);
}
