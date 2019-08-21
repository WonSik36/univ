/**************************************************************************
	Algorithm Analysis(ITP) HW5

	21300691 Cheung Won Sik

	How to Compile Code to Program
	1. (on command line) gcc hw5.c -o hw5.out
	2. It should be compiled in mac, linux operating system

	How to Execute Program
	1. (on command line) ./hw5.out
	   -> It automatically use "hw5.data" to input data
	2. (on command line) ./hw5.out (file_name)
	   -> use "file_name" to input data

	Input File Assumption
	1. given data's column and row order should be same

	Return of program
	1.Array of adjacency list of given graph
	2.Run Bellman-Ford's algorithm and print result & running time
	3.Run Dijtstra's algorithm and print result & running time
	4.Run Floyd-Warshall's algorithm and print result & running time

	Screenshot
	1.png : example of given data (hw5.data)
	2.png : example of given data with graph which has negative weight edge (test1.data)
	3.png : example of graph data with graph which has negative weight cycle (test2.data)

**************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

#define FILE_NAME "hw5.data"
#define MAX_STR_SIZE 255

/********** Linked List Structures & Functions **********/
typedef char* Data;

typedef struct _node{
	Data data;
	int w;
	struct _vertex * next;
}Node;

typedef struct _linkedlist{
	Node * head;
	Node * cur;
	Node * before;
	Node * tail;
	int numN;
}LinkedList;

typedef LinkedList List;

void ListInit(List * list);
void ListInsert(List * list, Data data, int w);
int LFirst(List * list, Data data);
int LNext(List * list, Data data);
int LSearch(List * list, Data data);
Data LRemove(List * list);
void LFree(List * list);
void copyList(List * toL, List * fromL);

/********** Graph Structures & Functions **********/
typedef Node Vertex;

typedef struct _grpah{
	int numV;		//number of vertex
	int numE;		//number of edge
	int * dist;
	int * pred;
	List * adjList;
	int ** result;
	double time;
}Graph;

void graphInit(Graph * g, int nv);
void graphFree(Graph * g);
void addEdge(Graph * g, Data fromV, Data toV, int w);

/********** Priority Queue Structures & Functions **********/
typedef struct _PQElem{
	int w;
	int data;
}PQElem;

typedef struct _PriorityQueue{
	int numE;
	PQElem * PQArr;
}PQ;

void PQInit(PQ * pq, int num);
void PQFree(PQ * pq);
int IsPQEmpty(PQ * pq);
void PQInsert(PQ * pq, int w, int data);
int PQDelete(PQ * pq);
void PQUpdateWeight(PQ *pq, int w, int data);
int getParentIDX(int idx);
int getLChildIDX(int idx);
int getRChildIDX(int idx);
int getHiPriChildIDX(PQ * pq, int idx);

/********** main functions & helper functions **********/
int makeGraph(Graph * g, char * fName);
void displayAdjlist(Graph * g);
void displayAdjArray(Graph * g);
void displayResult(Graph * g);
int findIndexByData(Graph * g, Data data);
Data findDataByIndex(Graph * g, int idx);
void initSingleSource(Graph * g, int src);
int relax(Graph * g, int u, int v, int w);
int Bellman_Ford(Graph * g, int src);
int result_Bellman_Ford(Graph * g);
void Dijkstra(Graph * g, int src);
void result_Dijkstra(Graph * g);
void Floyd(Graph * g);
void result_Floyd(Graph * g);
int abs(int num);

int main(int argc, char* argv[]){
	int re;
	Graph g;

	/******* Read input file and Create graph *******/
	if(argc==1){
		re = makeGraph(&g, FILE_NAME);
	}else{
		re = makeGraph(&g, argv[1]);
	}
	if(!re){
		printf("Error Opening File\n");
		return -1;
	}
	printf("1)Array of adjacency list of given graph\n\n");
	displayAdjlist(&g);

	/******* Apply Bellman-Ford's algorithm for |V| times and print result *******/
	re = result_Bellman_Ford(&g);
	printf("2)It took %.6lf seconds to compute shortest path between cities with Bellman-Ford's algorithm as follows.\n\n",g.time);
	if(!re) printf("There is Negative Weight Cycle in Graph\n");
	displayResult(&g);

	/******* Apply Dijkstra's algorithm for |V| times and print result *******/
	result_Dijkstra(&g);
	printf("3)It took %.6lf seconds to compute shortest path between cities with Dijkstra's algorithm as follows.\n\n",g.time);
	displayResult(&g);

	/******* Run Floyd-Warshall's algorithm and print result *******/
	result_Floyd(&g);
	printf("4)It took %.6lf seconds to compute shortest path between cities with Floyd's algorithm as follows.\n\n",g.time);
	displayResult(&g);

	graphFree(&g);

	return 0;
}

/********** Linked List Structures & Functions **********/

// Initialize list
void ListInit(List * list){
	//node head is dummy node
	list->head = (Node*)malloc(sizeof(Node));
	list->head->data = NULL;
	list->head->next = NULL;
	list->tail = list->head;
	list->numN = 0;
}

// Insert new node at tail
void ListInsert(List * list, Data data, int w){
	//append new node to tail
	Node * newNode = (Node*)malloc(sizeof(Node));
	newNode->data = (Data)malloc(sizeof(char)*(strlen(data)+1));
	strcpy(newNode->data,data);
	newNode->next = NULL;
	newNode->w = w;

	list->tail->next = newNode;
	list->tail = list->tail->next;

	(list->numN)++;
}

// Call First node
// If First node exists return True
// and update parameter data to first node data
// else return false
int LFirst(List * list, Data data){
	if(list->head->next == NULL)
		return FALSE;
	list->before = list->head;
	list->cur = list->head->next;
	//update data to current node data
	strcpy(data,list->cur->data);
	return TRUE;
}

// Call next node from current node
// If next node exists return True
// 	and update parameter data to next node data
// 	and also update current node to next node
// else return false
int LNext(List * list, Data data){
	if(list->cur->next == NULL)
		return FALSE;

	list->before = list->cur;
	list->cur = list->cur->next;

	strcpy(data,list->cur->data);
	return TRUE;
}

// Search node which has input data
// return weight of node
int LSearch(List * list, Data data){
	char dummy[30];

	if(LFirst(list, dummy)){
		if(strcmp(data, dummy) == 0){
			return list->cur->w;
		}else{
			while(LNext(list, dummy)){
				if(strcmp(data, dummy) == 0){
					return list->cur->w;
				}
			}

			return -1;
		}
	}
	return -1;
}

// Delete node at current position
// return the data in deleted node
Data LRemove(List * list){
	Node * rpos = list->cur;
	Data data = (Data)malloc(strlen(rpos->data)+1);
	strcpy(data,rpos->data);

	list->before->next = list->cur->next;
	list->cur = list->before;

	free(rpos->data);
	free(rpos);
	(list->numN)--;

	return data;
}

// Free all dynamically allocated variable in list
void LFree(List * list){
	char dummy[30];
	Data data;

	//printf("delete array of %c\n",list->head->data);
	if(LFirst(list, dummy)){
		//printf("del: %c, ", data);
		//printf("remain vertex: %d\n",list->numN);
		data = LRemove(list);
		free(data);
		while(LNext(list, dummy)){
			//printf("del: %c, ", data);
			//printf("remain vertex: %d\n",list->numN);
			data = LRemove(list);
			free(data);
		}
	}
	//printf("\n");
	free(list->head);
}

//copy list to list by deep copy
void copyList(List * toL, List * fromL){
	if(toL == NULL)
		printf("NULL!\n");

	toL->head = fromL->head;
	toL->tail = fromL->tail;
	toL->numN = fromL->numN;
	toL->cur = fromL->cur;
	toL->before = fromL->before;
}

/********** Graph Construct Structures & Functions **********/
// Initialize graph
void graphInit(Graph * g, int nv){
	int i;
	g->result = (int**)malloc(sizeof(int*)*nv);
	g->adjList = (List*)malloc(sizeof(List)*nv);
	g->dist = (int*)malloc(sizeof(int)*nv);
	g->pred = (int*)malloc(sizeof(int)*nv);
	g->numV = nv;
	g->numE = 0;

	for(i=0;i<nv;i++){
		ListInit(&(g->adjList[i]));
		g->result[i] = (int*)malloc(sizeof(int)*nv);
	}

	return;
}

//Free dynamically allocated variable from graph
void graphFree(Graph * g){
	int i;

	if(g->adjList != NULL){
		for(i=0;i<g->numV;i++)
			LFree(&(g->adjList[i]));
	}

	if(g->result != NULL){
		for(i=0;i<g->numV;i++)
			free(g->result[i]);
	}

	free(g->adjList);
	free(g->dist);
	free(g->pred);
	free(g->result);

	return;
}

//Add edge
void addEdge(Graph * g, Data fromV, Data toV, int w){
	//printf("add Edge from %c to %c\n",fromV,toV);
	int i;
	for(i=0;i<g->numV;i++){
		if(strcmp((g->adjList[i]).head->data,fromV)==0){
			ListInsert(&(g->adjList[i]), toV,w);
			break;
		}
	}
	g->numE += 1;
}

/********** Priority Queue Structures & Functions **********/

// initialize priority queue
void PQInit(PQ * pq, int num){
	pq->numE = 0;
	pq->PQArr = (PQElem*)malloc(sizeof(PQElem)*(num+1));
}

// memory free to priority queue
void PQFree(PQ * pq){
	free(pq->PQArr);
}

// return is priority queue empty
int IsPQEmpty(PQ * pq){
	if(pq->numE == 0)
		return TRUE;
	else
		return FALSE;
}

// insert element with edge weight & vertex index
void PQInsert(PQ * pq, int w, int data){
	int idx = pq->numE+1;
	PQElem elem = {w,data};

	while(idx != 1){
		if(w < (pq->PQArr[getParentIDX(idx)].w)){
			pq->PQArr[idx] = pq->PQArr[getParentIDX(idx)];
			idx = getParentIDX(idx);
		}else
			break;
	}
	pq->PQArr[idx] = elem;
	pq->numE += 1;

	//printf("Element Inserted w: %d, data: %d, num: %d\n",w,data,pq->numE);
}

// pop highest priority element in queue
int PQDelete(PQ * pq){
	int rData = pq->PQArr[1].data;
	PQElem elem = pq->PQArr[pq->numE];

	int parentIDX = 1;
	int childIDX;

	while(childIDX = getHiPriChildIDX(pq, parentIDX)){
		if(elem.w <= pq->PQArr[childIDX].w)
			break;

		pq->PQArr[parentIDX] = pq->PQArr[childIDX];
		parentIDX = childIDX;
	}

	pq->PQArr[parentIDX] = elem;
	pq->numE -= 1;
	return rData;
}

// update weight by data(vertex index)
// and regulate priority queue
void PQUpdateWeight(PQ *pq, int w, int data){
	PQElem elem = pq->PQArr[pq->numE];
	int parentIDX;
	int childIDX;
	int i;

	// search element which has input data
	for(i=1;i<pq->numE+1;i++){
		if(pq->PQArr[i].data == data){
			parentIDX = i;
			break;
		}
	}

	// delete updated element and change it to last element -> O(lgN)
	while(childIDX = getHiPriChildIDX(pq, parentIDX)){
		if(elem.w <= pq->PQArr[childIDX].w)
			break;
		pq->PQArr[parentIDX] = pq->PQArr[childIDX];
		parentIDX = childIDX;
	}

	pq->PQArr[parentIDX] = elem;
	pq->numE -= 1;

	// insert updated element to priority queue -> O(lgN)
	PQInsert(pq, w, data);
	//printf("Parent Weight: %d\n",pq->PQArr[1]);
	//printf("Left Child Weight: %d\n",pq->PQArr[2]);
	//printf("Right Child Weight: %d\n\n",pq->PQArr[3]);
	// finally it has time complexity O(lgN)
}

// return parent element index
int getParentIDX(int idx){
	return idx/2;
}

// return left child element index
int getLChildIDX(int idx){
	return idx*2;
}

// return right child element index
int getRChildIDX(int idx){
	return idx*2 + 1;
}

// compare left & right child
// and return high priority child element index
int getHiPriChildIDX(PQ * pq, int idx){
	if(getLChildIDX(idx) > pq->numE)
		return 0;
	else if(getLChildIDX(idx) == pq->numE)
		return getLChildIDX(idx);
	else{
		if(pq->PQArr[getLChildIDX(idx)].w > pq->PQArr[getRChildIDX(idx)].w)
			return getRChildIDX(idx);
		else
			return getLChildIDX(idx);
	}
}

/********** main functions & helper functions **********/

// update input graph pointer to graph from input file
// return false when file stream error occur
// else return true
int makeGraph(Graph * g, char * fName){
	List list;
	FILE * fp=NULL;
	char str[MAX_STR_SIZE];
	int i,j;
	int num;
	Node * node;

	// open file
	fp = fopen(fName,"rt");
	if(fp == NULL){
		return FALSE;
	}

	//take node list from input file's first line
	ListInit(&list);
	while(fscanf(fp,"%s",str) != -1){
		if(LSearch(&list, str) == -1){
			ListInsert(&list, str,0);
		}else{
			break;
		}
	}

	//make adjacency array from node list
	graphInit(g, list.numN);
	i=0;

	LFirst(&list, str);
	node = (g->adjList[i++]).head;
	node->data = (Data)malloc(strlen(str)+1);
	strcpy(node->data,str);

	while(LNext(&list, str)){
		node = (g->adjList[i]).head;
		node->data = (Data)malloc(strlen(str)+1);
		strcpy(node->data,str);
		i++;
	}

	//make adjacency list from remaining file data
	for(i=0;i<list.numN;i++){
		for(j=0;j<list.numN;j++){
			fscanf(fp,"%s",str);
			if(strcmp(str,"INF") != 0){
				num = atoi(str);
				if(num != 0){
					addEdge(g, (g->adjList[i]).head->data, (g->adjList[j]).head->data,num);
				}
			}
		}
		fscanf(fp,"%s",str);
	}
	LFree(&list);
	fclose(fp);
	return TRUE;
}

void displayAdjlist(Graph * g){
	int i;
	char data[30];

	for(i=0;i<g->numV;i++){
		printf("\t%s -> ",(g->adjList[i]).head->data);

		if(LFirst(&(g->adjList[i]), data)){
			printf("%s(%d) -> ",data,(g->adjList[i]).cur->w);

			while(LNext(&(g->adjList[i]), data)){
				printf("%s(%d) -> ",data,(g->adjList[i]).cur->w);
			}
		}
		printf("NULL\n");
	}

	printf("\n");
	return;
}

// list adjacency array
void displayAdjArray(Graph * g){
	int i;

	printf("\t\t");
	for(i=0;i<g->numV;i++){
		printf("%s\t",(g->adjList[i]).head->data);
	}
	printf("\n");
}


// display result after somewhat algorithm ran
void displayResult(Graph * g){
	int i,j;

	// first line
	displayAdjArray(g);

	// after first line
	for(i=0;i<g->numV;i++){
		printf("%s\t\t",(g->adjList[i]).head->data);
		for(j=0;j<g->numV;j++){
			if(g->result[i][j] == INT_MAX)
				printf("INF\t");
			else
				printf("%d\t",g->result[i][j]);
		}
		printf("\n");
	}

	printf("\n");
}

// find adjacency array index by data
int findIndexByData(Graph * g, Data data){
	Data fData;
	int i = 0;

	if(g->adjList == NULL){
		return -1;
	}

	for(i=0;i<g->numV;i++){
		fData = (g->adjList[i]).head->data;
		//printf("itter %d %c\n",i,fData);
		if(strcmp(fData,data)==0)
			return i;
	}

	return -1;
}

// find adjacency array data by index
Data findDataByIndex(Graph * g, int idx){
	if(g->adjList == NULL){
		return NULL;
	}

	return (g->adjList[idx]).head->data;
}

// initialize distance and predecessor
void initSingleSource(Graph * g, int src){
	int i;

	for(i=0;i<g->numV;i++){
		(g->dist[i]) = INT_MAX;
		g->pred[i] = -1;
	}

	g->dist[src] = 0;
}

// relax distance of vertex
int relax(Graph * g, int u, int v, int w){
	if(g->dist[u] == INT_MAX)
		return FALSE;

	//printf("d[v]: %s, d[u]: %s, w: %d\n",findDataByIndex(g,v),findDataByIndex(g,u),w);
	if(g->dist[v]>g->dist[u]+w){
		g->dist[v] = g->dist[u]+w;
		g->pred[v] = u;
		//printf("relax d[v]: %d\n", g->dist[v]);
		return TRUE;
	}else
		return FALSE;
}

// 1st shortest path algorithm
int Bellman_Ford(Graph * g, int src){
	int i,j;
	int idx;
	int w;
	char data[30];

	initSingleSource(g,src);

	//printf("\n\nSource : %s\n", findDataByIndex(g,src));
	// relax |V|-1 times
	for(j=0;j<g->numV-1;j++){
		for(i=0;i<g->numV;i++){
			//printf("%d TRY\n", i+1);
			if(LFirst(&(g->adjList[i]), data)){
				idx = findIndexByData(g,(g->adjList[i]).cur->data);
				w = (g->adjList[i]).cur->w;
				relax(g,i,idx,w);

				while(LNext(&(g->adjList[i]), data)){
					idx = findIndexByData(g,(g->adjList[i]).cur->data);
					w = (g->adjList[i]).cur->w;
					relax(g,i,idx,w);
				}
			}
		}
	}

	// check negative weight cycle
	for(i=0;i<g->numV-1;i++){
		if(LFirst(&(g->adjList[i]), data)){
			idx = findIndexByData(g,(g->adjList[i]).cur->data);
			w = (g->adjList[i]).cur->w;
			if((g->dist[i]!=INT_MAX)&&(g->dist[idx]>g->dist[i]+w))
				return FALSE;

			while(LNext(&(g->adjList[i]), data)){
				idx = findIndexByData(g,(g->adjList[i]).cur->data);
				w = (g->adjList[i]).cur->w;
				if((g->dist[i]!=INT_MAX)&&(g->dist[idx]>g->dist[i]+w))
					return FALSE;
			}
		}
	}

	return TRUE;
}

// run Bellman-Ford's algorithm |V| times
int result_Bellman_Ford(Graph * g){
	int i;
	int k;
	int res=0;
	clock_t start,end;

	// note start time
	start = clock();
	// run Bellman-Ford's algorithm |V| times
	for(i=0;i<g->numV;i++){
		res += Bellman_Ford(g, i);
		for(k=0;k<g->numV;k++){
			g->result[i][k] = g->dist[k];
		}
	}

	// note end time
	end = clock();
	// memorize running time
	g->time = (end-start)/(double)1000;

	if(res<g->numV)
		return FALSE;
	else
		return TRUE;
}

// 2nd shortest path algorithm
void Dijkstra(Graph * g, int src){
	PQ pq;
	char data[30];
	int i;
	int idx;
	int w;

	initSingleSource(g, src);
	// insert every vertex to priority queue
	PQInit(&pq, g->numV);
	for(i=0;i<g->numV;i++){
		PQInsert(&pq,g->dist[i],i);
	}

	while(!IsPQEmpty(&pq)){
		i = PQDelete(&pq);
		//printf("Vertex: %s\n",findDataByIndex(g,i));
		if(LFirst(&(g->adjList[i]), data)){
			// code below is relax procesure
			idx = findIndexByData(g,(g->adjList[i]).cur->data);
			w = (g->adjList[i]).cur->w;
			if(relax(g,i,idx,w)&&(!IsPQEmpty(&pq))){
				// if relax arise then rearrage priority queue
				PQUpdateWeight(&pq,w+(g->dist[i]),idx);
			}

			while(LNext(&(g->adjList[i]), data)){
				idx = findIndexByData(g,(g->adjList[i]).cur->data);
				w = (g->adjList[i]).cur->w;
				if(relax(g,i,idx,w)&&(!IsPQEmpty(&pq))){
					// if relax arise then rearrage priority queue
					PQUpdateWeight(&pq,w+(g->dist[i]),idx);
				}

			}

		}
	}
	PQFree(&pq);
}

// run Dijkstra's algorithm |V| times
void result_Dijkstra(Graph * g){
	int i;
	int k;
	int res = 0;
	clock_t start,end;

	// note start time
	start = clock();
	// run Dijkstra's algorithm |V| times
	for(i=0;i<g->numV;i++){
		res += i;
		//printf("%d",i); printf("%c",8);
		Dijkstra(g, i);
		for(k=0;k<g->numV;k++){
			//printf("\tdist[k]: %d\n",g->dist[k]);
			g->result[i][k] = g->dist[k];
		}
	}

	// note end time
	end = clock();
	// memorize running time
	g->time = (end-start)/(double)1000;
};

// 3rd shortest path algorithm
void Floyd(Graph * g){
	int ** dist[2];
	int ** pred;
	char data[30];
	int i,j,k;
	int idx = 0;	// index to choose dist[0] or dist[1]
	int cond1,cond2;

	/***** initialize *****/
	// memory allocate distance array
	for(i=0;i<2;i++){
		dist[i] = (int**)malloc(sizeof(int*)*g->numV);
		for(j=0;j<g->numV;j++){
			dist[i][j] = (int*)malloc(sizeof(int)*g->numV);
		}
	}
	// memory allocate predecessor array
	pred = (int**)malloc(sizeof(int*)*g->numV);
	for(i=0;i<g->numV;i++){
		pred[i] = (int*)malloc(sizeof(int)*g->numV);
	}

	// make 0 to diagonal element and others to infinite
	for(i=0;i<g->numV;i++){
		for(j=0;j<g->numV;j++){
			if(i==j)
				dist[0][i][j] = 0;
			else
				dist[0][i][j] = INT_MAX;
		}
	}

	// init distance array & predcessor
	for(i=0;i<g->numV;i++){
		if(LFirst(&(g->adjList[i]), data)){
			//set distance
			j = findIndexByData(g,data);
			dist[0][i][j] = (g->adjList[i]).cur->w;
			//set predecessor
			if((dist[0][i][j] == INT_MAX) || (i==j))
				pred[i][j] = -1;
			else
				pred[i][j] = i;

			while(LNext(&(g->adjList[i]), data)){
				//set distance
				j = findIndexByData(g,data);
				dist[0][i][j] = (g->adjList[i]).cur->w;
				//set predecessor
				if((dist[0][i][j] == INT_MAX) || (i==j))
					pred[i][j] = -1;
				else
					pred[i][j] = i;
			}
		}
	}

	// dynamic programming
	for(k=0;k<g->numV;k++){
		for(i=0;i<g->numV;i++){
			for(j=0;j<g->numV;j++){
				// Condition 1: isn't distance[i][k] == infinite or is distance[k][j] == infinite
				cond1 = !(dist[idx][i][k]==INT_MAX || dist[idx][k][j]==INT_MAX);
				// Condition 2: is distance[i][k] + distance[k][j] distance[i][j]
				cond2 = (dist[idx][i][k] + dist[idx][k][j] < dist[idx][i][j]);
				if(cond1 && cond2){
					dist[abs(idx-1)][i][j] = dist[idx][i][k] + dist[idx][k][j];
					pred[i][j] = k;
					//printf("k: %d, i: %d, j: %d, distance: %d\n",abs(idx-1),i,j,dist[abs(idx-1)][i][j]);
				}else{
					dist[abs(idx-1)][i][j] = dist[idx][i][j];
				}
			}
		}
		idx = abs(idx-1);
	}

	// copy distance to result
	for(i=0;i<g->numV;i++){
		for(j=0;j<g->numV;j++){
			g->result[i][j] = dist[idx][i][j];
		}
	}

	// memory free
	for(i=0;i<2;i++){
		for(j=0;j<g->numV;j++){
			free(dist[i][j]);
		}
		free(dist[i]);
	}
	for(i=0;i<g->numV;i++){
		free(pred[i]);
	}
	free(pred);
}

// run Floyd's algorithm and measure the time
void result_Floyd(Graph * g){
	clock_t start,end;

	// note start time
	start = clock();
	// run Floyd's algorithm
	Floyd(g);
	// note end time
	end = clock();
	// memorize running time
	g->time = (end-start)/(double)1000;
}

// return absolute value of input number
int abs(int num){
	if(num >=0)
		return num;
	else
		return -1 * num;
}