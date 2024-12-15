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

    int reachable_ancestor[6]; // earliest reachable ancestor of vertex, USING A BACK EDGE
    int tree_out_degree[6]; // dfs tree outdegree of vertex
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

void process_vertex_early(graph* graph, int vertex) { //function is called whenever we encounter a back edge that takes us to an earlier ancestor than we have previously seen
// age of ancestors can be determined from their entry times
    graph->reachable_ancestor[vertex] = vertex;
    return;
}

void process_vertex_late(graph* graph, int vertex) { // evaluates three conditions to identify articulation vertices (root, bridge or parent cut-nodes)
    bool isRoot; // is the vertex the root of the DFS tree?
    int earliest_time_v; // earliest reachable time for vertex v
    int earliest_time_parent; // earliest reachable time for parent of v / parent[v]

    if (graph->parent[vertex] < 1) { // test if vertex v is the root, if curr vertex has no parent it is the root
        if (graph->tree_out_degree[vertex] > 1) { // if it has more than 1 child/edges
            cout << "Root articulation vertex: " << vertex << endl; // root is always articulation vertex if it has more than 1 child
        }
        return;
    }

    // test if parent[vertex] is root
    isRoot = (graph->parent[graph->parent[vertex]] < 1); // tests if parent of the vertex has no parent aka less than 1 parent. therefore parent[vertex] is a root

    if (isRoot == false) { // if parent isnt a root

    // CHECKS FOR PARENT ARTICULATION VERTICES
    // undirected graph. basically no back edge exists that goes above the parent
    // therefore that parent is important
        if (graph->reachable_ancestor[vertex] == graph->parent[vertex]) { // if current vertex's earliest reachable ancestor is its parent
            // the only way for the subtree of vertex to connect to the rest of the graph is through its parent
            cout << "Parent articulation vertex: " << graph->parent[vertex] << endl; // therefore the parent vertex is a parent articulation vertex
        }

    // CHECKS FOR BRIDGE ARTICULATION VERTICES
        if (graph->reachable_ancestor[vertex] == vertex) { // if the current vertex's earliest reachable ancestor is itself
        // then deleting the edge from parent[vertex] to vertex disconnects the graph
            cout << "Bridge articulation vertex: " << graph->parent[vertex] << endl; // therefore the parent is a bridge articulation vertex because it cuts off vertex and its subtree

            // test if vertex is not a leaf
            if (graph->tree_out_degree[vertex] > 0) { // if vertex has no children, aka if it is a leaf, then it is also a bridge articulation vertex
                cout << "Bridge articulation vertex: " << vertex << endl; // 
            }            
        }
    }

    earliest_time_v = graph->entry_time[graph->reachable_ancestor[vertex]]; // set earliest time for VERTEX as the entry time of earliest reachable ancestor
    earliest_time_parent = graph->entry_time[graph->reachable_ancestor[graph->parent[vertex]]]; // set earliest time for the PARENT as the entry time of its earliest reachable ancestor

    if (earliest_time_v < earliest_time_parent) { // if vertex can reach a node earlier than its parent
        graph->reachable_ancestor[graph->parent[vertex]] = graph->reachable_ancestor[vertex]; // set the parent's earliest reachable ancestor as the vertex's earliest reachable ancestor
    }
} 

// classifying edges
//
char* edge_classification(graph* graph, int x, int y) {
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
}


void process_edge(graph* graph, int x, int y) { // processes edges 
    char* edgeClass; // edge class
    edgeClass = edge_classification(graph, x, y); // classify the edge

    if (edgeClass == "TREE") {
        graph->tree_out_degree[x] = graph->tree_out_degree[x] + 1; // if it is tree edge, add another tree_out_degree to x since edge is from x to y
    }

    if ((edgeClass == "BACK") && (graph->parent[x] != y)) { // if it is a back edge and y is not the parent of x, for edge x to y (y did not discover x)
        if (graph->entry_time[y] < graph->entry_time[graph->reachable_ancestor[x]]) { // if y was discovered before x's earliest reachable ancestor
            graph->reachable_ancestor[x] = y; // set x's earliest reachable ancestor as y
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

    process_vertex_early(graph, currVert); // processing if wanted
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

    process_vertex_late(graph, currVert);
    graph->time = graph->time + 1;
    graph->exit_time[currVert] = graph->time; // indicates when the vertex has finished processing
    graph->processed[currVert] = true; // marks vertex (including all of its edges) as processed

    // graph->finished can be set to true during processing if we want to stop the traversal early 
    // (eg finding a target node, detecting cycle)

}

int main() {
    graph graph;
    read_graph(&graph, false);
    print_graph(&graph);

    initialise_search(&graph);
    dfs(&graph, 1);
}
