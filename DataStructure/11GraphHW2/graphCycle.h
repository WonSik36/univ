//////////////////////////  graphCycle.h ////////////////////
#ifndef graphCycle_h
#define graphCycle_h
#include "graphQS.h"       // a simple queue and stack to support Graph.cpp

// a structure to represent an adjacency list node
typedef struct GNode *pGNode;
typedef struct GNode {
	int item;
	pGNode next;
} GNode;

// a structure to represent a graph.
// a graph is an array of adjacency lists.
// size of will be V (number of vertices in graph)

typedef struct Graph *pGraph;
typedef struct Graph {
	int V;				// number of vertices in the graph
	int E;				// number of edges in the graph
	pGNode adj;			// an array of adjacency lists 

	// the following DS's are allocated when used for the first time
	// These are set by depthFirstSearch(), 
	// breadthFirstSearch(), and connectedComponent()
	short *marked;		// marked[v] = is there an s->v path?
	int   *edgeTo;		// edgeTo[v] = last edge on shortest s->v path?
	pStack cycle;		// odd-length cycle, NULL if not found
}Graph;

pGNode newGNode(int item);				// create a new adjacency list node
pGraph newGraph(int V);					// create a graph of V vertices
int V(pGraph g);						// return the number of vertices in graph.
int E(pGraph g);						// return the number of edges in graph.
void addEdgeFromTo(pGraph g, int v, int w);	// add an edge to an undirected graph
void addEdge(pGraph g, int v, int w);	// add two edges, v-w & w-v, to the graph
void freeGraph(pGraph g);				// free graph
void printAdjList(pGraph g);			// print the adjacency list of  graph
void printEdgeTo(pGraph g);				// print the edgeTo of graph

int hasSelfLoop(pGraph g);
int hasParallelEdges(pGraph g);
int hasCycle(pGraph g);
pStack getCycle(pGraph g);

void graphCycle(pGraph g);				//Search cycle by using dfs
void dfs(pGraph g, int u, int v);		//Recursive DFS does the work

#endif graphCycle_h