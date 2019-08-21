#include <stdio.h>
#include "graphCycle.h"
#include "graphQS.h"

void testGraph0() {
	printf(">testGraph0 begins...dfs:03421\n");
	pGraph g = newGraph(5);
	addEdge(g, 0, 1);
	addEdge(g, 0, 3);
	addEdge(g, 1, 2);
	addEdge(g, 2, 3);
	addEdge(g, 3, 4);
	printAdjList(g);

	graphCycle(g);
	printEdgeTo(g);
	if(hasCycle(g)) {
		printf("There is a cycle: ");
		pStack s = getCycle(g);
		while (sizeStack(s))
			printf("%d ", pop(s));
		printf("\n");
	}
	else printf("This graph is acyclic.\n");
	
	freeGraph(g);
	printf("<testGraph0 ends..\n");
}

void testGraph1() {
	printf(">testGraph1 begins...\n");
	pGraph g = newGraph(7);
	addEdge(g, 0, 5);
	addEdge(g, 0, 1);
	addEdge(g, 0, 2);
	addEdge(g, 0, 6);
	addEdge(g, 2, 3);
	addEdge(g, 2, 4);
	addEdge(g, 3, 4);
	addEdge(g, 3, 5);
	addEdge(g, 4, 5);
	printAdjList(g);

	graphCycle(g);
	if(hasCycle(g)) {
		printf("There is a cycle: ");
		pStack s = getCycle(g);
		while (sizeStack(s))
			printf("%d", pop(s));
		printf("\n");
	}
	else
		printf("This graph is acyclic.\n");

	freeGraph(g);
	printf("<testGraph1 ends...\n");
}

void testGraph3() {
	printf(">testGraph3 begins...\n");
	pGraph g = newGraph(7);
	addEdge(g, 4, 3);
	addEdge(g, 0, 1);
	addEdge(g, 6, 4);
	addEdge(g, 5, 4);
	addEdge(g, 0, 2);
	addEdge(g, 0, 6);
	printAdjList(g);

	graphCycle(g);
	if(hasCycle(g)) {
		printf("There is a cycle: ");
		pStack s = getCycle(g);
		while (sizeStack(s))
			printf("%d", pop(s));
		printf("\n");
	}
	else
		printf("This graph is acyclic.\n");

	freeGraph(g);
	printf("<testGraph3 ends...\n");
}

void main() {
	testGraph0();
	testGraph1();
	testGraph3();

	printf("end of graph\n");
}