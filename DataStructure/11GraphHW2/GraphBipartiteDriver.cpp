#include <stdio.h>
#include "graphBipartite.h"
#include "graphQS.h"
#include "verify.h"

void testGraph0() {
	printf(">testGraph0 begins...dfs:03421\n");
	pGraph g = newGraph(5);
	addEdge(g, 0, 1);
	addEdge(g, 0, 3);
	addEdge(g, 1, 2);
	addEdge(g, 2, 3);
	addEdge(g, 3, 4);
	printAdjList(g);

	graphBipartite(g);
	if (isBipartite(g)) {
		printf("Yes, is is bigraph\n");
		verify(verifyBipartite(g), "This bigraph is invalid\n");
		printBipartite(g);
	}
	else {
		printf("It is not bigraph\n");
		printf("There is a cycle: ");
		pStack s = getCycle(g);
		while (sizeStack(s))
			printf("%d ", pop(s));
		printf("\n");
	}

	freeGraph(g);
	printf("<testGraph0 ends...\n");
}

void testGraph1() {
	printf(">testGraph1 begins...bipartite (0, 3, 4)(1,2,5,6)\n");
	pGraph g = newGraph(7);
	addEdge(g, 0, 5);
	addEdge(g, 0, 1);
	addEdge(g, 0, 2);
	addEdge(g, 0, 6);
	addEdge(g, 1, 3);
	addEdge(g, 2, 3);
	addEdge(g, 2, 4);
	addEdge(g, 4, 5);
	addEdge(g, 4, 6);
	printAdjList(g);

	graphBipartite(g);
	if (isBipartite(g)) {
		printf("Yes, is is bigraph\n");
		verify(verifyBipartite(g), "This bigraph is invalid\n");
		printBipartite(g);
	}
	else {
		printf("It is not bigraph\n");
		printf("There is a cycle: ");
		pStack s = getCycle(g);
		while (sizeStack(s))
			printf("%d ", pop(s));
		printf("\n");
	}

	freeGraph(g);
	printf("<testGraph1 ends...\n");
}

void testGraph2() {
	printf(">testGraph2 begins...Cycle(3,4,5)\n");
	pGraph g = newGraph(7);
	addEdge(g, 0, 5);
	addEdge(g, 4, 3);
	addEdge(g, 0, 1);
	addEdge(g, 6, 4);
	addEdge(g, 5, 4);
	addEdge(g, 0, 2);
	addEdge(g, 0, 6);
	addEdge(g, 5, 3);
	printAdjList(g);

	graphBipartite(g);
	if (isBipartite(g)) {
		printf("Yes, is is bigraph\n");
		verify(verifyBipartite(g), "This bigraph is invalid\n");
		printBipartite(g);
	}
	else {
		printf("It is not bigraph\n");
		printf("There is a cycle: ");
		pStack s = getCycle(g);
		while (sizeStack(s))
			printf("%d ", pop(s));
		printf("\n");
	}

	freeGraph(g);
	printf("<testGraph2 ends...\n");
}

void main(){
	testGraph0();
	testGraph1();
	testGraph2();
	printf("end of graph\n");
}