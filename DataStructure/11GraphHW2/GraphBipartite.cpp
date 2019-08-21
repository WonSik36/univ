/**
*  The GraphBipartite.cpp implements a data type for determining whether 
*  an undirected graph is bipartite or whether it has an odd-length cycle.
*  The isBipartite() operation determines whether the graph is bipartite.
*  If so, the color operation determines a bipartition; if not, the oddCycle
*  operation determines a cycle with an odd number of edges.
*
*  This implementation uses depth-first search.
*  The constructor takes time proportional to V + E (in the worst case),
*  where V is the number of vertices and E is the number of edges.
*  Afterwards, the isBipartite and color operation take constant time;
*  the oddCycle operation takes time proportional to the length of the cycle.
*
*  @author Youngsup Kim
*  2014/05/01     YSK creation
*/

#include <stdio.h>
#include <stdlib.h>
#include "graphBipartite.h"
#include "graphQS.h"
#include "verify.h"

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
	g->isBipartite = true;
	g->V = V;
	g->E = 0;

	// create an array of adjacency list. size of array will be V
	g->adj = (pGNode)malloc(V * sizeof(GNode));
	if (g->adj == NULL) return NULL;

	// initialize each adjacency list as empty by making head as NULL;
	for (int i = 0; i < V; i++)
		g->adj[i].next = NULL;

	g->marked = NULL;	// allocate it when used for the first time
	g->color = NULL;
	g->edgeTo = NULL;	// allocate it when used for the first time
	g->cycle = NULL;
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
	if(g->color) free(g->color);
	if (g->edgeTo) free(g->edgeTo);
	if (g->cycle) free(g->cycle);
	free(g);
}

//print the adjacency list of graph
void printAdjList(pGraph g) {
	for (int v = 0; v < V(g); v++) {
		pGNode curr = g->adj[v].next;
		printf(" Adj.List V[%d]: ", v);
		while(curr) {
			printf("%d ", curr->item);
			curr = curr->next;
			if(curr) printf("-> ");
			}
		printf("\n");
	}

#if 0
	for (int v = 0; v < V(g); ++v) {
		printf(" Adj,List V[%d]: ", v);
		for (pGNode w = g->adj[v].next; w; w = w->next) {
			printf("%d ", w->item);
			if (w->next == NULL) printf("\n");
			else				 printf("-> ");
		}
	}
#endif
}

void printBipartite(pGraph g) {
	printf("Bipartite(M) : ");
	for(int i = 0; i < V(g); i++)
		if(g->color[i] == BLACK) printf("%d ", i);
	printf("\n");

	printf("Bipartite(F) : ");
	for(int i = 0; i < V(g); i++)
		if(g->color[i] == WHITE) printf("%d ", i);
	printf("\n");
}

// verify that adj[v]'s color should be different from its adj[v]'s list vertices
// if it is bipartite.
int verifyBipartite(pGraph g){
	if (!g->isBipartite) return false;
	for (int v = 0; v < V(g); v++) {
		for(pGNode curr= g->adj[v].next; curr; curr = curr->next)
			if (g->color[v] == g->color[curr->item]) return false;
	}
	return true;
}

// graphBipartite() determines whether an undirected graph is bipartite and finds
// either a bipartition or an odd -length cycle.
void graphBipartite(pGraph g) {
	if (g->marked == NULL) g->marked = (short *)malloc(V(g) * sizeof(short));
	if (g->color == NULL) g->color = (short *)malloc(V(g) * sizeof(short));
	if (g->edgeTo== NULL) g->edgeTo= (int*)malloc(V(g) * sizeof(int));
	if (g->marked == NULL || g->color == NULL || g->edgeTo== NULL) return;
	for (int i = 0; i < V(g); i++) {
		g->marked[i] = false;
		g->color[i] = BLACK;// BLACK=0, WHITE=1
		g->edgeTo[i] = -1;
	}
	for (int v = 0; v < V(g); v++) {
		if (!g->marked[v])
			dfs(g, v);
	}
}

// Recursive DFS does the work
void dfs(pGraph g, int v) {
	g->marked[v] = true;
	for (pGNode w = g->adj[v].next; w; w = w->next) {
		if (g->cycle != NULL) return;
		if (!g->marked[w->item]) {
			g->edgeTo[w->item] = v;
			g->color[w->item] = !(g->color[v]);
			dfs(g, w->item);
		}
		else if (g->color[w->item] == g->color[v]) {
			g->isBipartite = false;
			g->cycle = newStack();
			for (int i = v; i != w->item; i = g->edgeTo[i]) 
				push(g->cycle, i);
			push(g->cycle, w->item);
			push(g->cycle, v);
		}
	}
}

int isBipartite(pGraph g){
	if(g->color == NULL) graphBipartite(g);

	if(g->isBipartite) return true;
	return false;
}

int hasCycle(pGraph g) {
	return g->cycle != NULL;
}

pStack getCycle(pGraph g) {
	return copyStack(g->cycle);
}

int color(pGraph g, int v){
	if(g->color == NULL) graphBipartite(g);

	return g->color[v];
}

///////////// helper function for Queue and Stack ///////////////
void freeNode(pNode curr) {
	pNode next;
	do {
		next = curr->next;
		free(curr);
		curr = next;
	} while (curr != NULL);
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
// a helper function for copyStack()
pNode newNode(Key key) {
	pNode node = (pNode)malloc(sizeof(Node));
	if(node == NULL) return NULL;
	node->key = key;
	node->next = NULL;
	return node;
}

// a helper function for getCycle()
pStack	copyStack(pStack s) {
	if(s == NULL) return NULL;
	pStack newS = newStack();

	newS->top = newNode(s->top->key);
	newS->size++;
	pNode node = s->top->next;
	pNode curr = newS->top;
	while(node) {
		curr->next = newNode(node->key);
		node = node->next;
		curr = curr->next;
		newS->size++;
	}

	verify((sizeStack(s) == sizeStack(newS)), "Copied stack size is invalid.\n");
	return newS;
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
