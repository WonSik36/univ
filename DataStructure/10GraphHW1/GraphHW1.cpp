/*On my honor, I pledge that I have neither received nor provided improper
assistance in the completion of this programming assignment. Signed: Wonsik Cheung*/
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

#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "graphQS.h"

// create a new adjacency list node
pGNode newGNode(int item) {
	pGNode node = (pGNode)malloc(sizeof(GNode));
	if (node == NULL) return NULL;
	node->item = item;
	node->next = NULL;
	return node;
}

// create a graph of V vertices
pGraph newGraph(int V) {
	pGraph g = (pGraph)malloc(sizeof(struct Graph));
	if (g == NULL) return NULL;
	g->V = V;
	g->E = 0;

	// create an array of adjacency list. size of array will be V
	g->adj = (pGNode)malloc(V * sizeof(GNode));
	if (g->adj == NULL) return NULL;

	// initialize each adjacency list as empty by making head as NULL;
	for (int i = 0; i < V; i++)
		g->adj[i].next = NULL;

	g->marked = NULL;	// allocate it when used for the first time
	g->edgeTo = NULL;	// allocate it when used for the first time
	g->compId = NULL;	// allocate it when used for the first time
	return g;
}

// return the number of vertices in the graph.
int V(pGraph g) { return g->V; }

// return the number of edges in the graph.
int E(pGraph g) { return g->E; }

// add an edge (from v to w) to an undirected graph
// A new node is added to the adjacency list of v. 
// The node is added at the beginning
void addEdgeFromTo(pGraph g, int v, Key w) {
	// instantiate a node with w and 
	// add it at the beginning of adj[v]
		
	pGNode node = newGNode(w);
	node->next = g->adj[v].next;
	g->adj[v].next = node;

	g->E++;
}

// add an edge to an undirected graph
void addEdge(pGraph g, int v, int w) {
	addEdgeFromTo(g, v, w);	// add an edge from v to w. 
	addEdgeFromTo(g, w, v);	// if graph is undirected, add both
}

// free graph data structure
void freeGraph(pGraph g) {
	pGNode curr, next;

	if (g == NULL) return;
	if (g->adj == NULL) return;

	// free graph's adjacency list
	for(int i = 0; i < g->V; i++){
		curr = g->adj[i].next;
		next = curr->next;
			while(next != NULL){
				free(curr);
				curr = next;
				next = curr->next;
			}
			free(curr);
	}
	free(g->adj);

	// free graph operation's reaults
	if (g->marked) free(g->marked);
	if (g->edgeTo) free(g->edgeTo);
	if (g->compId) free(g->compId);
	free(g);
}

// print graph's contents 
void printGraph(pGraph g){

	// print the adjacency list of graph
	pGNode curr;
	for(int i=0; i < g->V; i++){
		printf("Adj.List V[%d]: ",i);
		curr = g->adj[i].next;
		while(curr != NULL){
			printf("%d ", curr->item);
			if(curr->next != NULL)
				printf("-> ");
			curr = curr->next;
		}
		printf("\n");
	}

	// print graph operation's reaults
	if (g->edgeTo) {
		printf(" edgeTo[0..%d] = ", V(g) - 1);
		for (int v = 0; v < V(g); v++)
			printf("%d ", g->edgeTo[v]);
		printf("\n");
		printf(" distTo[0..%d] = ", V(g) - 1);
		for(int v = 0; v < V(g); v++)
			printf("%d ", distTo(g, 0, v));
		printf("\n");
	}
	if (g->compId) {
		printf(" compId[0..%d] = ", V(g) - 1);
		for (int v = 0; v < V(g); v++)
			printf("%d ", g->compId[v]);
		printf("\n");
	}
}

// Recursive DFS does the work
void dfs(pGraph g, int v, short *marked, int *edgeTo) {
	marked[v] = true;
	printf("%d ", v);
	
	for(pGNode node = g->adj[v].next; node ; node = node->next){
		if(!marked[node->item]){
			edgeTo[node->item] = v;
			dfs(g, node->item, marked, edgeTo);
		}
	}
}

// DFS - find vertices connected to v
void depthFirstSearch(pGraph g, int v){
	if (g->marked == NULL) g->marked = (short *)malloc(V(g) * sizeof(short));
	if (g->edgeTo == NULL) g->edgeTo = (int   *)malloc(V(g) * sizeof(int));
	if (g->marked == NULL || g->edgeTo == NULL) return;

	for (int i = 0; i < V(g); i++) {
		g->marked[i] = false;
		g->edgeTo[i] = -1;
	}

	printf("Depth First Search: ");
	dfs(g, v, g->marked, g->edgeTo);
	printf("\n");
}

// DFS for connected components
void connectedComponentDFS(pGraph g, int v, short *marked, int *edgeTo, int *compId, int id) {
	printf(" DFS CC: v=%d, id=%d\n", v, id);

	marked[v] = true;
	compId[v] = id;
	for (pGNode w = g->adj[v].next; w; w = w->next) {
		if (!marked[w->item]) {
			edgeTo[w->item] = v;
			connectedComponentDFS(g, w->item, marked, edgeTo, compId, id);
		}
	}
}

// connectedCompnenent() produces connected component ids
void connectedComponent(pGraph g) {
	int id = 0;
	if (g->marked == NULL) g->marked = (short *)malloc(V(g) * sizeof(short));
	if (g->edgeTo == NULL) g->edgeTo = (int   *)malloc(V(g) * sizeof(int));
	if (g->compId == NULL) g->compId = (int   *)malloc(V(g) * sizeof(int));
	if (g->marked == NULL || g->edgeTo == NULL || g->compId == NULL) return;

	for (int i = 0; i < V(g); i++) {
		g->marked[i] = false;
		g->edgeTo[i] = -1;
		g->compId[i] = -1;
	}

	for (int v = 0; v < V(g); v++) {
		if (!g->marked[v]) {
			printf("Starting a new component id=%d at vertex %d\n", id, v);
			connectedComponentDFS(g, v, g->marked, g->edgeTo, g->compId, id++);
		}
	}
}


void breadthFirstSearch(pGraph g, int v) {
	pQueue q = newQueue();
	int N = V(g);

	if (g->marked == NULL) g->marked = (short *)malloc(N * sizeof(short));
	if (g->edgeTo == NULL) g->edgeTo = (int   *)malloc(N * sizeof(int));
	if (g->marked == NULL || g->edgeTo == NULL) return;

	for (int i = 0; i < N; i++) {
		g->marked[i] = false;
		g->edgeTo[i] = -1;
	}

	printf("Breadth First Search: "); printf("%d ", v);
	g->marked[v] = true;
	enqueue(q, v);
	while (q->front != NULL) {
		v = dequeue(q);
		for(pGNode w = g->adj[v].next; w ; w = w->next){
			if(g->marked[w->item] == false){
				g->marked[w->item] = true;
				g->edgeTo[w->item] = v;
				enqueue(q, w->item);
				printf("%d ", w->item);
			}
		}
	}
	printf("\n");
	freeQueue(q);
}

// Find a path from s to v using the result of depthFirstSearch's edgeTo info.
// It has to use a stack to retrace the path back to the source.
// Once the client(caller) gets a stack returned, 
// he/she pops the paths and free the stack.
pStack hasPathTo(pGraph g, int s, int v) {
	if (g->edgeTo == NULL) depthFirstSearch(g, s);	// no edgeTo[]?, then do dfs.
	if(!g->marked[v]) return NULL;
	pStack path = newStack();
	// go through the edgeTo from v to s and push to the stack
	// the caller(client) needs to pop the stack the paths back.
	for(int i = v; i != s; i = g->edgeTo[i]){
		if(i == NULL)
			return NULL;
		push(path, i);
	}
	push(path, s);
	return path;
}
//
// distTo() returns the number of edges in a shortest path between the source 
// vertex s and vertex v
//
int distTo(pGraph g, int s, int v){
	if (g->distTo == NULL) breadthFirstSearch(g, s);
	if(!g->marked[v]) return NULL;
	pStack path = newStack();
	
	for(int i = v; i != s; i = g->edgeTo[i]){
		if(i == NULL)
			return NULL;
		push(path, i);
	}

	if(path == NULL) return false;
	int size = sizeStack(path);
	freeStack(path);
	return size;
}
//////////////////// Graph.cpp ///////////////////////////////////

///////////// helper function for Queue and Stack ///////////////
void freeNode(pNode curr) {
	pNode next;
	do {
		next = curr->next;
		free(curr);
		curr = next;
	} while (curr != NULL);
}

/////////////////////////// Queue ///////////////////////////////
pQueue newQueue() {
	pQueue q = (pQueue)malloc(sizeof(Queue));
	q->front = q->rear = NULL;
	q->size = 0;
	return q;
}

int sizeQueue(pQueue q) {
	return q->size;
}

void enqueue(pQueue q, Key key) {
	pNode t = (pNode)malloc(sizeof(Node));
	if (t == NULL) return;

	t->key = key;
	t->next = NULL;
	if (q->front == NULL)
		q->front = t;
	else
		q->rear->next = t;
	q->rear = t;
	q->size++;
}

Key dequeue(pQueue q) {
	pNode t = q->front;
	if (t == NULL) return NULL;

	Key key = t->key;
	q->front = t->next;
	free(t);
	q->size--;
	return key;
}

void freeQueue(pQueue q) {
	if (q == NULL) return;
	if (q->size == 0) return free(q);
	freeNode(q->front);
	free(q);
}

/////////////////////////// Stack ///////////////////////////////
pStack newStack() {
	pStack s = (pStack)malloc(sizeof(Stack));
	s->top = NULL;
	s->size = 0;
	return s;
}

int sizeStack(pStack s) {
	return(s->size);
}

void push(pStack s, Key key) {
	pNode t = (pNode)malloc(sizeof(Node));
	if (t == NULL) return;
	t->key = key;
	t->next = s->top;
	s->top = t;
	s->size++;
}

Key pop(pStack s) {
	pNode t = s->top;
	if (t == NULL) return NULL;
	Key key = t->key;
	s->top = t->next;
	free(t);
	s->size--;
	return key;
}

void freeStack(pStack s) {
	if (s == NULL) return;
	if (s->size == 0) return free(s);
	freeNode(s->top);
	free(s);
}
