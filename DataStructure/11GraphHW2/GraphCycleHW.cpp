/**
* The GraphCycle.cpp implements a data type for determining whether
* an undirected graph has a cycle and, if so, the cycle operation returns one.
*
* This implementation uses depth-first search.
* The graphCycle() takes time proportional to V + E (in the worst case),
* where V is the number of vertices and E is the number of edges.
* Afterwards, the hasCycle operation takes constant time;
* the cycle operation takes time proportional to the length of the cycle.
*
* @author Youngsup Kim
* 2014/05/01	YSK	Creation
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "graphCycle.h"
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
	if (g->edgeTo) free(g->edgeTo);
	if (g->cycle) free(g->cycle);
	free(g);
}

// does this graph have a self loop?
// side effect: initialize cycle to be self loop
int hasSelfLoop(pGraph g) {
	for (int v = 0; v < V(g); v++) {
		for(pGNode w = g->adj[v].next; w; w = w->next) {
			if(v == w->item) {
				g->cycle = newStack();
				push(g->cycle, v);
				push(g->cycle, v);
				return true;
			}
		}
	}
	return false;
}

// does this graph have two parallel edges?
// side effect: initialize cycle to be two parallel edges
int hasParallelEdges(pGraph g) {
	if (g->marked == NULL) g->marked = (short*)malloc(V(g) * sizeof(short));
	for (int i = 0; i < V(g); i++)
		g->marked[i] = false;

	for (int v = 0; v < V(g); v++) {
		//check for parallel edges incident to v
		for (pGNode w = g->adj[v].next; w; w = w->next) {
			if (g->marked[w->item]) {
				g->cycle = newStack();
				push(g->cycle, v);
				push(g->cycle, w->item);
				push(g->cycle, v);
				return true;
			}
			g->marked[w->item] = true;
		}
		//reset so marked[v] = false for all v
		for(pGNode w = g->adj[v].next; w; w = w->next) {
			g->marked[w->item] = false;
		}
	}
	return false;
}

int hasCycle(pGraph g) {
	return g->cycle != NULL;
}

// It returns a cycle if the graph has a cycle, and NULL otherwise.
// Potential problem: Once  it is popped, the stack is gone.
pStack getCycle(pGraph g) {
	return copyStack(g->cycle);
}

// This implementation uses depth - first search.
// The graphCycle() takes time proportional to V + E(in the worst case),
// where V is the number of vertices and E is the number of edges.
void graphCycle(pGraph g) {
	if (hasSelfLoop(g)) return;
	if (hasParallelEdges(g)) return;


	if (g->marked == NULL) g->marked = (short*)malloc(V(g) * sizeof(short));
	if (g->edgeTo == NULL) g->edgeTo = (int  *)malloc(V(g) * sizeof(int));
	for (int i = 0; i < V(g); i++) {
		g->marked[i] = false;
		g->edgeTo[i] = -1;
	}

	for (int v = 0; v < V(g); v++) {
		if(!g->marked[v])
			dfs(g, -1, v);
	}
}

// Recursive DFS does the work
// @param  g: the graph, u: vertex visited previously, v: visiting vertex
void dfs(pGraph g, int u, int v) {
	g->marked[v] = true;
	printf("Visit(%d) marked\n", v);		//visit vertex v

	for (pGNode w = g->adj[v].next; w; w = w->next) { //check all vertices in adj.list
		//short circuit if cycle already found
		if(g->cycle != NULL) return;

		if(!g->marked[w->item]) {			//check vertex w->item
			g->edgeTo[w->item] = v;
			printf(" marked(%d), now go to next = unmarked(%d)\n", v, w->item);
			dfs(g, v, w->item);
		}
		//check for cycle (but disregard reverse of edge leading to v)
		else if(w->item != u) {
			g->cycle = newStack();
			for(int i = v; i != w->item; i = g->edgeTo[i]) 
				push(g->cycle, i);
			push(g->cycle, w->item);
			push(g->cycle, v);
		}
	}
	printf("%d done\n", v);
}

void printEdgeTo(pGraph g) {
	if(!g->edgeTo) return;
	printf(" edgeTo[0..%d] = ", V(g) - 1);
	for(int v = 0; v < V(g); v++)
		printf("%d ", g->edgeTo[v]);
	printf("\n");
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

//print the adjacency list and other info of graph
void printGraph(pGraph g) {
	printAdjList(g);
	printEdgeTo(g);
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

	verify((sizeStack(s) == sizeStack(newS)), "Copied stack size is invalid.");
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
