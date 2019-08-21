/**
*  The Graph.cpp implements an undirected/directed graph of vertices
*  named 0 through V - 1.
*  It supports the following two primary operations:
*  1) add an edge to the graph,
*  2) iterate over all of the vertices adjacent to a vertex.
*  It also provides functions for returning the number of vertices V and
*  the number of edges E. Parallel edges and self-loops are permitted.
*
*  This implementation uses an adjacency-lists representation, which
*  is a vertex-indexed array of nodes or singly-linked list.
*  All operations take constant time (in the worst case) except
*  iterating over the vertices adjacent to a given vertex, which takes
*  time proportional to the number of such vertices.
*
*  @author Youngsup Kim
*
*  2014/05/01	YSK	Creation
*
*/

#ifndef graph_h
#define graph_h

#include "graphQS.h"		// a simple queue and stack to support Graph.cpp

// a structure to represent an adjacency list node
typedef struct GNode *pGNode;
typedef struct GNode {
	int item;
	// int weight;			// for weighted graph - network
	pGNode next;
} GNode;

// a structure to represent a graph. 
// a graph is an array of adjacency lists. 
// size of will be V (number of vetices in graph)

typedef struct Graph *pGraph;
typedef struct Graph {
	int V;				// number of vertices in the graph
	int E;				// number of edges in the graph
	pGNode adj;			// an array of adjacency lists 

	// the following DS's are allocated when used for the first time
	// These are set by depthFirstSearch(), 
	// breadthFirstSearch(), and connectedComponent()
	short *marked;		// marked[v] = is there an s->v path?
	int   *edgeTo;		// edgeTo[v] = last edge on shortest s->v path
	int	  *distTo;		// distTo[v] = length of shortest s->v path
	int   *compId;		// Connected Component id
}Graph;

pGNode newGNode(int item);				// create a new adjacency list node
pGraph newGraph(int V);					// create a graph of V vertices
int V(pGraph g);						// return the number of vertices in graph.
int E(pGraph g);						// return the number of edges in graph.
void addEdgeFromTo(pGraph g, int v, int w);	// add an edge to an undirected graph
void addEdge(pGraph g, int v, int w);	// add two edges, v-w & w-v, to the graph
void freeGraph(pGraph g);				// free graph
void printGraph(pGraph g);				// print the adjacency list of graph

int distTo(pGraph g, int s, int v);		// the number of edges in a shortest path from s to v

void depthFirstSearch(pGraph g, int v);	// DFS - find vertices connected to v
void dfs(pGraph g, int v, short *marked, int *edgeTo);	// Recursive DFS does the work

void connectedComponent(pGraph g);		// produce connected component's ids and edgeTo
void connectedComponentDFS(pGraph g, int v, short *marked, int *edgeTo, int *compId, int id);

void breadthFirstSearch(pGraph g, int v);	// queue required

// Find a path from s to v using the result of depthFirstSearch's edgeTo info.
// It uses a stack to retrace the path back to the source.
pStack hasPathTo(pGraph g, int s, int v);	// results of dfs or bfs, stack required
#endif graph_h