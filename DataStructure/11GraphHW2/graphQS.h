// graphQS.h - a simple queue and stack to support Graph.cpp
// 2014/05/01	YSK	Creation

#ifndef graphQS_h
#define graphQS_h

typedef int Key;				// for flexibility

typedef struct Node *pNode;		// a generic node for queue and stack
typedef struct Node {
	Key		key;
	pNode	next;
} Node;

typedef struct Queue *pQueue;
typedef struct Queue {
	pNode front;
	pNode rear;
	int size;
} Queue;

typedef struct Stack *pStack;
typedef struct Stack {
	pNode	top;
	int		size;
} Stack;

// define the function prototypes for queue and stack
void	freeNode(pNode curr);			// helper function to free generic nodes
pNode newNode(Key key);

// Queue operations
pQueue	newQueue();
int		sizeQueue(pQueue q);
void	enqueue(pQueue q, Key key);
Key		dequeue(pQueue q);
void	freeQueue(pQueue q);

// Stack operations
pStack	newStack();
int		sizeStack(pStack s);
void	push(pStack s, Key key);
Key		pop(pStack s);
void	freeStack(pStack s);
pStack	copyStack(pStack s);    // added to suppoer graphCycle, Bipartite

#endif graphQS_h
