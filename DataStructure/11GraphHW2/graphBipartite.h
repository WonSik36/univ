#ifndef graphBipartite_h
#define graphBipartite_h
#include "graphQS.h"// a simple queue and stack to support Graph.cpp

#define BLACK 0// used for graph coloring
#define WHITE 1// (BLACK = !WHITE)

// a structure to represent an adjacency list node
typedef struct GNode *pGNode;
typedef struct GNode{
int item;
pGNode next;
} GNode;

// a structure to represent a graph.
typedef struct Graph *pGraph;
typedef struct Graph {
int isBipartite;		// is the graph bipartite?
int V;					// number of vertices in the graph
int E;					// number of edges in the graph
pGNode adj;				// an array of adjacency lists
short *marked;			// marked[v] = is there an s->v path?
short *color;			// color[v] gives vertices on one side of bipartition
int*edgeTo;				// edgeTo[v] = last edge on shortest s->v path
pStack cycle;			// odd-length cycle, NULL if not found
} Graph;

pGNode newGNode(int item);// create a new adjacency list node
pGraph newGraph(int V);// create a graph of V vertices
int V(pGraph g);// return the number of vertices in graph.
int E(pGraph g);// return the number of edges in graph.
void addEdgeFromTo(pGraph g, int v, int w);// add an edge to an undirected graph
void addEdge(pGraph g, int v, int w);// add two edges, v-w & w-v, to the graph
void freeGraph(pGraph g);// free graph
void printAdjList(pGraph g);// print the adjacency list of graph

void printBipartite(pGraph g);// print the vertices by its bipartition group
int verifyBipartite(pGraph g);// verify the validiyof bipartition
void graphBipartite(pGraph g);// Bipartite using dfs()
void dfs(pGraph g, int v);// Recursive DFS does the work
int isBipartite(pGraph g);// return true if it is bigraph
int hasCycle(pGraph g);// return true if it has a cycle
pStack getCycle(pGraph g);// return odd cycle (copied, keep the original)
int color(pGraph g, int v);// return the side of the bipartite that vertex v is on.
#endif graphBipartite_h