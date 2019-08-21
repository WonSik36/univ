/**************************************************************************
	Algorithm Analysis(ITP) HW4

	21300691 Cheung Won Sik

	How to Compile Code to Program
	1. (on command line) gcc hw4.c -o hw4
	2. It should be compiled in windows system

	How to Execute Program
	1. (on command line) hw4.exe
	   -> It automatically use "hw4.data" to input data
	2. (on command line) hw4.exe (file_name)
	   -> use "file_name" to input data

	Input File Assumption
	1. Graph name is one alphabet character
	2. Vertex order is not matter (that will be Sorted in code)
	3. But column and row order should be same

	Return of program
	1.Array of adjacency list of given graph
	2.Discovery time and finish time of each vertex after step1 of SCC Algorithm
	3.Array of adjacency list of transpose graph after step2 of SCC Algorithm
	4.Discovery time and finish time of each vertex after step3 of SCC Algorithm
	5.SCC result

**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define TRUE 1
#define FALSE 0

#define FILE_NAME "hw4.data"
#define MAX_STR_SIZE 255

/********** Linked List Structures & Functions **********/
typedef char Data;

typedef struct _node{
	Data data;
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
void ListInsert(List * list, Data data);
int LFirst(List * list, Data * data);
int LNext(List * list, Data * data);
void LSort(List * list);
Node* MergeSort(Node * node);
Node* Merge(Node * first, Node * second);
Node* getMid(Node * node);
Data LRemove(List * list);
void LFree(List * list);
void copyList(List * toL, List * fromL);

/********** Graph Construct Structures & Functions **********/
enum {WHITE, GRAY, BLACK};

typedef Node Vertex;

typedef struct _grpah{
	int numV;		//number of vertex
	int numE;		//number of edge
	int * color;	//flag of visit & finish
	int * d;		//discovery time
	int * f;		//finish time
	Data * label;	//label of vertex
	List * adjList;
}Graph;

void graphInit(Graph * g, int nv);
void graphFree(Graph * g);
void addEdge(Graph * g, Data fromV, Data toV);
void sortAdjArrayByAlpha(Graph * g);
void sortAdjArrayByFinishTime(Graph * g);

/********** main functions & helper functions **********/
int makeGraph(Graph * g, char * fName);
void displayAdjlist(Graph * g);
void DFS(Graph * g);
void DFS_Visit(Graph * g, int idx, int label, int * time);
int findIndexByData(Graph * g, Data data);
Data findDataByIndex(Graph * g, int idx);
void transGraph(Graph * toG,Graph * fromG);
void printDF(Graph * g);
void printSCC(Graph * g);

int main(int argc, char* argv[]){
	int i;
	int re;
	Graph g;
	Graph trans;

	/******* Read input file and convert graph *******/
	if(argc==1){
		re = makeGraph(&g, FILE_NAME);
	}else{
		re = makeGraph(&g, argv[1]);
	}
	if(!re){
		printf("Error opening file");
		return -1;
	}
	printf("1)Array of adjacency list of given graph\n\n");
	displayAdjlist(&g);

	/******* Step1 DFS *******/
	DFS(&g);
	printf("2)Discovery time and finish time of each vertex after step1\n\n");
	printDF(&g);

	/******* Step2 Transpose graph *******/
	transGraph(&trans, &g);
	printf("3)Array of adjacency list of transpose graph after step2\n\n");
	displayAdjlist(&trans);

	/******* Step3 DFS Transpose graph *******/
	sortAdjArrayByFinishTime(&trans);
	//displayAdjlist(&trans);
	DFS(&trans);
	printf("4)Discovery time and finish time of each vertex after step3\n\n");
	printDF(&trans);

	/******* Step4 Display SCC result *******/
	sortAdjArrayByAlpha(&trans);
	printf("5)SCC result\n\n");
	printSCC(&trans);

	graphFree(&g);
	graphFree(&trans);
	system("pause");
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
void ListInsert(List * list, Data data){
	//append new node to tail
	Node * newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;

	list->tail->next = newNode;
	list->tail = list->tail->next;

	(list->numN)++;

	//printf("%c's number is %d\n",list->head->data,list->numN);
}

// Call First node
// If First node exists return True
// and update parameter data to first node data
// else return false
int LFirst(List * list, Data * data){
	if(list->head->next == NULL)
		return FALSE;
	list->before = list->head;
	list->cur = list->head->next;
	//update data to current node data
	*data = list->cur->data;
	return TRUE;
}

// Call next node from current node
// If next node exists return True
// 	and update parameter data to next node data
// 	and also update current node to next node
// else return false
int LNext(List * list, Data * data){
	if(list->cur->next == NULL)
		return FALSE;

	list->before = list->cur;
	list->cur = list->cur->next;

	*data = list->cur->data;
	return TRUE;
}

// Sort list by merge sort in ascending order of data
void LSort(List * list){
	if(list->head->next == NULL)
		return;
	else{
		list->head->next = MergeSort(list->head->next);
	}
}

// merge sort for linked list
Node* MergeSort(Node * node){
	if(node==NULL || node->next==NULL)
		return node;
	Node * mid = getMid(node);
	Node * half = mid->next;
	mid->next = NULL;
	//printf("divide two halves %c %c \n", node->data, half->data);
	return Merge(MergeSort(node), MergeSort(half));
}

// merge two partion of linked list
Node* Merge(Node * first, Node * second){
	Node * dummy = (Node*)malloc(sizeof(Node));
	Node * cur = dummy; // use dummy node at head

	// compare two halves and append smaller one
	//printf("merge two halves %c %c \n", first->data, second->data);
	while(first!=NULL && second!=NULL){
		if(first->data <= second->data){
			cur->next = first;
			first = first->next;
		}else{
			cur->next = second;
			second = second->next;
		}
		cur = cur->next;
	}

	// after one partion is empty, append other one whole
	if(first==NULL){
		cur->next = second;
	}else{
		cur->next = first;
	}

	return dummy->next;
}

// get mid point of given linked list
Node* getMid(Node * node){
	Node * slow;
	Node * fast;
	Node * ffast;

	if(node == NULL)
		return node;

	slow = node;
	fast = node;

	while(fast->next!=NULL){
		ffast = fast->next;
		if(ffast->next!=NULL){
			slow = slow->next;
			fast = ffast->next;
		}else
			break;
	}
	return slow;
}

// Delete node at current position
// return the data in deleted node
Data LRemove(List * list){
	Node * rpos = list->cur;
	Data data = rpos->data;

	list->before->next = list->cur->next;
	list->cur = list->before;

	free(rpos);
	(list->numN)--;

	return data;
}

// Free all dynamically allocated variable in list
void LFree(List * list){
	Data data;

	//printf("delete array of %c\n",list->head->data);
	if(LFirst(list, &data)){
		//printf("del: %c, ", data);
		//printf("remain vertex: %d\n",list->numN);
		LRemove(list);
		while(LNext(list, &data)){
			//printf("del: %c, ", data);
			//printf("remain vertex: %d\n",list->numN);
			LRemove(list);
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
	g->adjList = (List*)malloc(sizeof(List)*nv);
	g->color = (int*)malloc(sizeof(int)*nv);
	g->d = (int*)malloc(sizeof(int)*nv);
	g->f = (int*)malloc(sizeof(int)*nv);
	g->label = (int*)malloc(sizeof(Node)*nv);
	g->numV = nv;
	g->numE = 0;

	for(i=0;i<nv;i++){
		ListInit(&(g->adjList[i]));
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
	free(g->adjList);
	free(g->color);
	free(g->d);
	free(g->f);

	return;
}

//Add edge
void addEdge(Graph * g, Data fromV, Data toV){
	//printf("add Edge from %c to %c\n",fromV,toV);
	int i;
	for(i=0;i<g->numV;i++){
		if((g->adjList[i]).head->data == fromV){
			ListInsert(&(g->adjList[i]), toV);
			break;
		}
	}
	g->numE += 1;
}

// use insertion sort
// sort alpahbetical order by ascending order
void sortAdjArrayByAlpha(Graph * g){
	int i,j;
	List * list = (List*)malloc(sizeof(List));

	for(i=1;i<g->numV;i++){
		copyList(list, &(g->adjList[i]));
		for(j=i-1; j>=0; j--){
			if((g->adjList[j]).head->data > list->head->data){
				copyList(&(g->adjList[j+1]), &(g->adjList[j]));
			}else
				break;
		}
		copyList(&(g->adjList[j+1]), list);
	}

	free(list);
	return;
}

// use insertion sort
// sort finish time order by descending order
void sortAdjArrayByFinishTime(Graph * g){
	int i,j;
	int temp;
	List * list = (List*)malloc(sizeof(List));

	for(i=1;i<g->numV;i++){
		copyList(list, &(g->adjList[i]));
		temp = g->f[i];
		for(j=i-1; j>=0; j--){
			//printf("compare %c to %c\n",(g->adjList[j]).head->data,list->head->data);
			//printf("%d %d\n",(g->f[j]), (g->f[i]));
			if((g->f[j]) < temp){
				//printf("change %c to %c\n",(g->adjList[j]).head->data,list->head->data);
				copyList(&(g->adjList[j+1]), &(g->adjList[j]));
				g->f[j+1] = g->f[j];
			}else
				break;
		}
		copyList(&(g->adjList[j+1]), list);
		g->f[j+1] = temp;
	}

	free(list);
	return;
}

/********** main functions & helper functions **********/

// update input graph pointer to graph from input file
// return false when file stream error occur
// else return true
int makeGraph(Graph * g, char * fName){
	List list;
	FILE * fp;
	char str[MAX_STR_SIZE];
	char data;
	int i,j;
	int count;
	Vertex * vertex;

	// open file
	fp = fopen(fName,"rt");
	if(fp == NULL){
		return FALSE;
	}

	//take node list from input file's first line
	ListInit(&list);
	fgets(str, MAX_STR_SIZE, fp);
	i = 0;
	while(str[i]){
		if((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z')){
			ListInsert(&list, str[i]);
		}
		i++;
	}

	//make adjacency array from node list
	graphInit(g, list.numN);
	i=0;
	LFirst(&list, &data);
	(g->adjList[i++]).head->data = data;
	while(LNext(&list, &data)){
		(g->adjList[i]).head->data = data;
		i++;
	}

	//make adjacency list from remaining file data
	i=0;
	while(fgets(str, MAX_STR_SIZE, fp)){
		j = 0, count = 0;
		while(count < list.numN){
			if(str[j]=='1'){
				addEdge(g, (g->adjList[i]).head->data, (g->adjList[count]).head->data);
				count++;
			}else if(str[j]=='0'){
				count++;
			}
			j++;
		}
		i++;
	}


	//sort adjacency array by alphabetical ascending order
	sortAdjArrayByAlpha(g);
	//sort adjacency list by alphabetical ascending order
	for(i=0;i<g->numV;i++){
		LSort(&(g->adjList[i]));
	}

	fclose(fp);
	return TRUE;
}

void displayAdjlist(Graph * g){
	int i;
	Data data;

	for(i=0;i<g->numV;i++){
		printf("\t%c -> ",(g->adjList[i]).head->data);

		if(LFirst(&(g->adjList[i]), &data)){
			printf("%c -> ",data);

			while(LNext(&(g->adjList[i]), &data)){
				printf("%c -> ",data);
			}
		}
		printf("NULL\n");
	}

	printf("\n");
	return;
}

void DFS(Graph * g){
	int i;
	int time=0;

	for(i=0;i<g->numV;i++){
		g->color[i] = WHITE;
	}

	for(i=0;i<g->numV;i++){
		if(g->color[i] == WHITE)
			DFS_Visit(g, i, i, &time);
	}
}

void DFS_Visit(Graph * g, int idx, int label, int * time){
	Data data;
	int i;

	g->color[idx] = GRAY;
	*time = *time+1;
	g->d[idx] = *time;
	//printf("time: %d\n",*time);
	g->label[idx] = findDataByIndex(g,label);

	//printf("Discover %c at time %d\n", (g->adjList[idx]).head->data, *time);

	if(LFirst(&(g->adjList[idx]), &data)){
		i = findIndexByData(g, data);
		//printf("First: %c index %d\n",data,i);
		if(g->color[i]==WHITE){
			//printf("Enter DFS %c\n", data);
			DFS_Visit(g, i, label, time);
		}

		while(LNext(&(g->adjList[idx]), &data)){
			i = findIndexByData(g, data);
			//printf("Next: %c index %d\n",data,i);
			if(g->color[i]==WHITE){
				//printf("Enter DFS %c\n", data);
				DFS_Visit(g, i, label, time);
			}
		}
	}
	g->color[idx] = BLACK;
	*time = *time+1;
	g->f[idx] = *time;

	//printf("Finish %c at time %d\n", (g->adjList[idx]).head->data,*time);
}
void transGraph(Graph * toG,Graph * fromG){
	int i;
	Data data;

	graphInit(toG, fromG->numV);

	for(i=0;i<fromG->numV;i++){
		(toG->adjList[i]).head->data = (fromG->adjList[i]).head->data;
	}

	for(i=0;i<fromG->numV;i++){
		if(LFirst(&(fromG->adjList[i]), &data)){
			addEdge(toG, data, (toG->adjList[i]).head->data);

			while(LNext(&(fromG->adjList[i]), &data)){
				addEdge(toG, data, (toG->adjList[i]).head->data);
			}
		}
	}

	for(i=0;i<fromG->numV;i++){
		toG->d[i] = fromG->d[i];
		toG->f[i] = fromG->f[i];
	}
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
		if(fData == data)
			return i;
	}

	return -1;
}

// find adjacency array data by index
Data findDataByIndex(Graph * g, int idx){
	if(g->adjList == NULL){
		return -1;
	}

	return (g->adjList[idx]).head->data;
}

// print discovery time and finish time
void printDF(Graph * g){
	int i;

	// print discovery time of vertex
	printf("\tDiscovery time of each vertex\n\t");
	//print all vertex
	for(i=0; i<g->numV;i++){
		printf("%c\t", (g->adjList[i]).head->data);
	}
	printf("\n\t");
	//print discovery time
	for (i=0;i<g->numV;i++){
		printf("%d\t", g->d[i]);
	}
	printf("\n\n");

	// print finish time of vertex
	printf("\tFinish time of each vertex\n\t");
	//print all vertex
	for(i=0; i<g->numV;i++){
		printf("%c\t", (g->adjList[i]).head->data);
	}
	printf("\n\t");
	//print finish time
	for (i=0;i<g->numV;i++){
		printf("%d\t", g->f[i]);
	}
	printf("\n\n");
}

//print Stronly Connected Component
void printSCC(Graph * g){
	int count = 1;
	int i = 0;

	if(g->adjList == NULL)
		return;

	printf("\tSCC%d: vertex ",count++);
	printf("%c ",(g->adjList[i]).head->data);

	for(i=1;i<g->numV;i++){
		if(g->label[i-1] == g->label[i]){
			printf("%c ",(g->adjList[i]).head->data);
		}else{
			printf("\n\tSCC%d: vertex ",count++);
			printf("%c ",(g->adjList[i]).head->data);
		}
	}
	printf("\n");
}