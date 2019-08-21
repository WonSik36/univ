#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "graphQS.h"


void testGraph1() {
	// create the graph 
	//  [0] -------[1]
	//   |        / |  \
			//   |      /   |  [2]
	//   |    /     |   /
	//   |  /       |  /
	//  [4]--------[3]
	//
	printf(">testGraph1 begins...\n");
	int V = 5;
	pGraph g = newGraph(V);
	addEdge(g, 0, 1);
	addEdge(g, 0, 4);
	addEdge(g, 1, 2);
	addEdge(g, 1, 3);
	addEdge(g, 1, 4);
	addEdge(g, 2, 3);
	addEdge(g, 3, 4);
	printGraph(g);				// print the adjacency list of the graph 
	depthFirstSearch(g, 0);		// output should be 
	breadthFirstSearch(g, 0);	// output should be 
	printGraph(g);				// print the adj[] and processing results 

	freeGraph(g);
	printf("<testGraph1 ends...\n");
}

void testGraph2() {
	// create the graph (PPT Example)
	//  [0] ----------------[6]
	//   | \\-----------[2]  |
	//   |  \--------[1]     |
	//   |                  /
	//   |    [3]       ---/     
	//   |   /   \     /
	//   |  /     \   /
	//  [5]--------[4]
	//
	printf(">testGraph2 begins...\n");
	int V = 7;
	pGraph g = newGraph(V);
	addEdge(g, 0, 5);
	addEdge(g, 4, 3);
	addEdge(g, 0, 1);
	addEdge(g, 6, 4);
	addEdge(g, 5, 4);
	addEdge(g, 0, 2);
	addEdge(g, 0, 6);
	addEdge(g, 5, 3);

	depthFirstSearch(g, 0);		// output should be 0 6 4 5 3 2 1
	breadthFirstSearch(g, 0);	// output should be 0 6 2 1 5 4 3
	printGraph(g);
	freeGraph(g);
	printf("<testGraph2 ends...\n");
}

void testGraph3() {
	// create the graph (PPT Example)
	//  [0] ----------------[6]          [7]--------[8]
	//   | \\-----------[2]  |
	//   |  \--------[1]     |           [9]--------[10]
	//   |                  /             | \
	//   |    [3]       ---/              |   \
	//   |   /   \     /                  |     \
	//   |  /     \   /                  [11]----[12]
	//  [5]--------[4]
	//
	printf(">testGraph3 begins...\n");
	int V = 13;
	pGraph g = newGraph(V);
	addEdge(g, 0, 5);
	addEdge(g, 4, 3);
	addEdge(g, 0, 1);
	addEdge(g, 9, 12);  //added
	addEdge(g, 6, 4);
	addEdge(g, 5, 4);
	addEdge(g, 0, 2);
	addEdge(g, 11, 12);	//added
	addEdge(g, 9, 10);	//added
	addEdge(g, 0, 6);
	addEdge(g, 7, 8);	//added
	addEdge(g, 9, 11);	//added
	addEdge(g, 5, 3);
	printGraph(g);

	connectedComponent(g);

	printf("Find a path from 0 to 3: It should be 0-6-4-5-3\n");
	pStack path = hasPathTo(g, 0, 3);

	while (sizeStack(path) > 0)
		printf("[%d] ", pop(path));
	printf("\n");

	freeStack(path);
	freeGraph(g);
	printf("<testGraph3 ends...\n");
}

// This program test textbook Figure 6.16 & Depth first search
void testFigure6_16() {
	// pGraph buildTestGraph() {
	//
	//           [0]
	//          /   \
		//         /     \
		//      [1]      [2]
	//      /  \     /  \
		//     /    \   /    \
		//    [3]  [4] [5]  [6]
	//       \  |   |   /
	//        \ |   |  /
	//           [7]
	//
	printf(">testFigure6_16 begins...\n");
	pGraph g = newGraph(8);
	addEdgeFromTo(g, 0, 2);
	addEdgeFromTo(g, 0, 1);		// [0] 1->2

	addEdgeFromTo(g, 1, 4);		// [1] 3->4->0
	addEdgeFromTo(g, 1, 3);
	addEdgeFromTo(g, 1, 0);

	addEdgeFromTo(g, 2, 6);		// [2] 0->5->6
	addEdgeFromTo(g, 2, 5);
	addEdgeFromTo(g, 2, 0);

	addEdgeFromTo(g, 3, 7);		// [3] 1->7
	addEdgeFromTo(g, 3, 1);

	addEdgeFromTo(g, 4, 7);
	addEdgeFromTo(g, 4, 1);

	addEdgeFromTo(g, 5, 7);
	addEdgeFromTo(g, 5, 2);

	addEdgeFromTo(g, 6, 7);
	addEdgeFromTo(g, 6, 2);

	addEdgeFromTo(g, 7, 6);
	addEdgeFromTo(g, 7, 5);
	addEdgeFromTo(g, 7, 4);
	addEdgeFromTo(g, 7, 3);

	printf(" DFS output shoud be 0 1 3 7 4 5 2 6\n");
	depthFirstSearch(g, 0);

	printf(" BFS output shoud be 0 1 2 3 4 5 6 7 \n");
	breadthFirstSearch(g, 0);
	printGraph(g);

	printf("The distance from 0 to 2 should be 1; it is %d\n", distTo(g, 0, 1));
	printf("The distance from 0 to 5 should be 2; it is %d\n", distTo(g, 0, 5));
	printf("The distance from 0 to 3 should be 2; it is %d\n", distTo(g, 0, 3));
	printf("The distance from 0 to 7 should be 3; it is %d\n", distTo(g, 0, 7));

	freeGraph(g);
	printf("<testFigure6_16 ends...\n");
}

void testGraph4() {
	// create the graph (BFS PPT Example)
	//  [0] ---------[2]
	//   | \         /|
	//   |  [1]    /  |
	//   |       /    |
	//   |    [3]     |   
	//   |   /   \    |   
	//   |  /     \  /       
	//  [5]--------[4]
	//
	printf(">testGraph4 begins...\n");
	int V = 6;
	pGraph g = newGraph(V);
	addEdgeFromTo(g, 0, 5);
	addEdgeFromTo(g, 0, 1);
	addEdgeFromTo(g, 0, 2);
	addEdgeFromTo(g, 1, 2);
	addEdgeFromTo(g, 1, 0);
	addEdgeFromTo(g, 2, 4);
	addEdgeFromTo(g, 2, 3);
	addEdgeFromTo(g, 2, 1);
	addEdgeFromTo(g, 2, 0);
	addEdgeFromTo(g, 3, 2);
	addEdgeFromTo(g, 3, 4);
	addEdgeFromTo(g, 3, 5);
	addEdgeFromTo(g, 4, 2);
	addEdgeFromTo(g, 4, 3);
	addEdgeFromTo(g, 5, 0);
	addEdgeFromTo(g, 5, 3);

	breadthFirstSearch(g, 0);	// output should be [0 2 1 5 3 4]
	printGraph(g);				// edgeTo[] = - 0 0 2 2 0 
	// distTo[] = 0 1 1 2 2 1

	printf("The distance from 0 to 4 should be 2; it is %d\n", distTo(g, 0, 4));
	printf("The distance from 0 to 5 should be 1; it is %d\n", distTo(g, 0, 5));
	printf("The distance from 0 to 3 should be 2; it is %d\n", distTo(g, 0, 3));
	printf("The distance from 0 to 0 should be 0; it is %d\n", distTo(g, 0, 0));
	freeGraph(g);
	printf("<testGraph4 ends...\n");
}

// Driver program to test Graph functions
void main() {
	testGraph1();		// test adjacency list of a simple graph
	testGraph2();		// test DFS and BFS
	testGraph3();		// test DFS, Connected components and edgeTo[]
	testGraph4();		// test BFS, edgeTo[] and distTo[]
	testFigure6_16();	// textbook Figure 6.16 & Depth first search

	printf("end of graph\n");
}

