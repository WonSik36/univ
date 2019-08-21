/* File: SListHWDriver.cpp */
/* On my honor, I pledge that I have neither received nor provided improper assistance 
 * in the completion of this assignment. Signed: WonSikCheung.
 */
/**
 * SListDriver runs test cases on the SList program.
 * It prints summary information on basic operations and
 * halts with an error (and a stack trace) if any of the tests fail.
 *
 * @author WonSikCheung
 * @student number 21300691
 * @e-mail address cws0173@hgu.edu
 * 2014/03/15 Creation
 * 2014/04/16 Modified - Make other function to test delete funcitons, insertTailSList, pop, push, enqueue, and dequeue.
 */
/**************************************************************************************************
void testEmpty();				To test list's empty condition
void testInsertFront();         To test insertFrontSList()
void testInsertEnd();			To test insertEndSList()
void testInsertTail();			To test insertTailSList()
void testDelete();				To test deleteSList(), deleteFrontSList(), deleteEndSList()
void testStack();				To test pushSList(), popSLIst();
void testQueue();				To test enqueueSList(), dequeueSList()
**************************************************************************************************/
#if 0
#include <stdio.h>
#include <string.h>
#include "SList.h"
#include "verify.h"

void testEmpty();
void testInsertFront();
void testInsertEnd();
void testInsertTail();
void testDelete();
void testStack();
void testQueue();

void main(int argc, char *argv[]) {
	testEmpty();
	testInsertFront();
	testInsertEnd();
	testInsertTail();
	testDelete();
	testStack();
	testQueue();
}

/**
 * testEmpty() tests ToStringSList(), isEmptySList(), lengthSList(), 
 * insertFrontSList(), and insertEndSList() on an empty list.  
 */

void testEmpty() {
	printf("**********Start testEmpty()**********\n");

	pSList p = makeSList();

	printf("After construction should be NOTHING: %s\n", toStringSList(p));
	printf("isEmptySList() should be true(1): It is (%d)\n", isEmptySList(p));
	printf("lengthSList() should be 0: It is %d\n", lengthSList(p));
	validateSList(p);

	insertFrontSList(3, p);
	printf("After insertFrontSList(3) [ 3 ]: It is %s\n", toStringSList(p));
	validateSList(p);

	insertEndSList(5, p);
	printf("After insertEndSList(5) [ 3 5 ]: %s\n", toStringSList(p));
	validateSList(p);

	freeSList(p);
}

/**
* testInsertFront() tests toStringSList(), isEmptySList(), lengthSList(),
* insertFrontSList(), and insertEndSList() after insertFrontSList().
*/

void testInsertFront() {
	printf("\n**********Start testInsertFront()**********\n");
	
	pSList list = makeSList();

	insertFrontSList(3, list);
	insertFrontSList(2, list);
	insertFrontSList(1, list);
	validateSList(list);
	printf("After insertFrontSList [ 1 2 3]: %s\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ 1 2 3 ]") == 0, "InsertFrontSList() failed");
	verify(isEmptySList(list) == 0, "isEmptySList() after insertFrontSList() failed");

	printf("lengthSList() should be 3. It is: %d\n", lengthSList(list));
	verify(lengthSList(list) == 3, "lengthSList() failed");

	insertEndSList(4, list);
	printf("After insertEndSList(4): %s\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ 1 2 3 4 ]") == 0, "insertEndSList() failed");

	validateSList(list);
	freeSList(list);
}

/**
* testInsertEnd() tests toStringSList(), insertFrontSList() and insertEndSList().
* verify() prints summary information of the tests and halts the program
* if errors are detected.
*/

void testInsertEnd() {
	printf("\n**********Start testInsertEnd()**********\n");

	pSList list = makeSList();

	insertEndSList(6, list);
	insertEndSList(7, list);
	insertEndSList(8, list);
	validateSList(list);

	printf("After insertEndSList [ 6 7 8 ]: %s\n", toStringSList(list));
	printf("lengthSList() should be 3. It is: %d\n", lengthSList(list));
	verify(lengthSList(list) == 3, "lengthSList() after insertEndSList() failed");

	insertFrontSList(5, list);
	printf("After insertFrontSList(5) [ 5 6 7 8 ]: %s\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ 5 6 7 8 ]") == 0, "insertFrontSList(5) failed");
	validateSList(list);

	freeSList(list);
}


/**
 * testInsertTail(); tests insertTailSList(),toStringSList(), insertEndSList(), deleteSList() and deleteEndSList().
 * verify() prints summary information of the tests and halts the program
 * if errors are detected.
 */

void testInsertTail(){
	printf("\n**********Start testInsertTail()**********\n");

	pSList list = makeSList();

	insertTailSList(3, list);
	printf("After insertTailSList [ 3 ]: %s\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ 3 ]") == 0, "insertTailSList() failed");

	insertEndSList(5, list);
	insertEndSList(7, list);
	validateSList(list);

	printf("After insertEndSList [ 3 5 7 ]: %s\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ 3 5 7 ]") == 0, "insertEndSList() failed");

	insertTailSList(3, list);
	printf("After insertTailSList [ 3 5 7 3 ]: %s\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ 3 5 7 3 ]") == 0, "insertTailSList() failed");

	deleteSList(3, list);
	printf("After deleteSList [ 5 7 ]: %s\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ 5 7 ]") == 0, "deleteSList() failed");

	insertTailSList(1, list);
	printf("After insertTailSList [ 5 7 1 ]: %s\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ 5 7 1 ]") == 0, "insertTailSList() failed");

	deleteEndSList(list);
	printf("After deleteEndSList [ 5 7 ]: %s\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ 5 7 ]") == 0, "deleteEndSList() failed");

	insertTailSList(1, list);
	printf("After insertTailSList [ 5 7 1 ]: %s\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ 5 7 1 ]") == 0, "insertTailSList() failed");

	freeSList(list);
}

/**
 * testDelete() tests toStringSList(), insertEndSList(), deleteSList(), deleteFrontSList(), and deleteEndSList().
 * verify() prints summary information of the tests and halts the program
 * if errors are detected.
 */

void testDelete(){
	printf("\n**********Start testDelete()**********\n");


	pSList list = makeSList();

	insertEndSList(1, list);
	insertEndSList(3, list);
	insertEndSList(4, list);
	insertEndSList(3, list);
	insertEndSList(1, list);
	insertEndSList(2, list);
	insertEndSList(5, list);
	validateSList(list);
	
	printf("After insertEndSList [ 1 3 4 3 1 2 5 ]: %s\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ 1 3 4 3 1 2 5 ]") == 0, "insertEndSList() failed");

	deleteSList(0, list);
	deleteSList(1, list);
	validateSList(list);
	printf("After deleteSList [ 3 4 3 2 5 ]: %s\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ 3 4 3 2 5 ]") == 0, "deleteSList() failed");

	deleteFrontSList(list);
	printf("After deleteFrontSList [ 4 3 2 5 ]: %s\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ 4 3 2 5 ]") == 0, "deleteFrontSList() failed");

	deleteEndSList(list);
	printf("After deleteEndSList [ 4 3 2 ]: %s\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ 4 3 2 ]") == 0, "deleteEndSList() failed");

	deleteEndSList(list);
	deleteEndSList(list);
	deleteEndSList(list);
	validateSList(list);
	printf("After deleteEndSList [ ]: %s\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ ]") == 0, "deleteEndSList() failed");

	deleteSList(1, list);
	deleteFrontSList(list);
	deleteEndSList(list);
	printf("After deleteSList, deleteFrontSList and deleteEndSList [ ]: %s\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ ]") == 0, "deleteEndSList() failed");

	freeSList(list);
}

/**
 * testStack() tests toStringSList(), popSList(), pushSList().
 * verify() prints summary information of the tests and halts the program
 * if errors are detected.
 */
void testStack(){
	printf("\n**********Start testStack()**********\n");

	pSList list = makeSList();
	int i;
	
	for(i=1;i<11;i++)
		pushSList(i, list);
	validateSList(list);
	printf("After pushSList [ 10 9 8 7 6 5 4 3 2 1 ]: %s (input 1 to 10)\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ 10 9 8 7 6 5 4 3 2 1 ]") == 0, "pushSList() failed");

	printf("Progress popSList [ 10 9 8 7 6 ]: [ ");
	for(i=0;i<5;i++)
		printf("%d ",popSList(list));
	printf("]\n");
	validateSList(list);
	printf("After popSList [ 5 4 3 2 1 ]: %s\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ 5 4 3 2 1 ]") == 0, "popSList() failed");
}

/**
 * testQueue() tests toStringSList(), enqueueSList(), dequeueSList().
 * verify() prints summary information of the tests and halts the program
 * if errors are detected.
 */
void testQueue(){
	printf("\n**********Start testQueue()**********\n");
	pSList list = makeSList();
	int i;

	for(i=1;i<11;i++)
		enqueueSList(i, list);
	validateSList(list);
	printf("After enqueueSList [ 1 2 3 4 5 6 7 8 9 10 ]: %s(input 1 to 10)\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ 1 2 3 4 5 6 7 8 9 10 ]") == 0, "enqueueSList() failed");

	printf("Progress dequeueSList [ 1 2 3 4 5 ]: [ ");
	for(i=0;i<5;i++)
		printf("%d ",dequeueSList(list));
	printf("]\n");
	validateSList(list);
	printf("After dequeueSList [ 6 7 8 9 10 ]: %s\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ 6 7 8 9 10 ]") == 0, "dequeueSList() failed");
}

#endif

/* File: SList2Driver.cpp */
/**
 * SListDriver runs test cases on the SList program.
 * It prints summary information on basic operations and
 * halts with an error (and a stack trace) if any of the tests fail.
 *
 * @author Youngsup Kim
 * 2014/03/15 Creation
 *
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "SList.h"
#include "verify.h"

void testEmpty();
void testInsertFront();
void testInsertEnd();
void testDelete();
void testInsertTail();
void testInsertTailTiming();

void main(int argc, char *argv[]) {
	int a[] = { 0, 0, 0, 0, 1, 1, 0, 0, 0, 3, 3, 3, 1, 1, 0 };	
	// int a[] = {2, 3, 7, 4, 2, 2 };
	int n = sizeof(a) / sizeof(int);

	testEmpty();
	testInsertFront();
	testInsertEnd();	
	testDelete();
	testInsertTail();
	testInsertTailTiming();

#if 0	
	pSList list = makeSList();

	for (i = 0; i < n; i++) printf("%d ", a[i]); printf("\n");
	smoothie(a, n);
	for (i = 0; i < n; i++) printf("%d ", a[i]); printf("\n");

	for (i = 0; i < n; i++) {
		insertEndSList(a[i], list);
	}
	printf("list: %s\n", toStringSList(list));
	printf("lengthSList() should be %d. It is: %d\n", n, lengthSList(list));
	verify(lengthSList(list) == n, "insertFrontSList() failed");
	validateSList(list);

	printf("Before squeezer:%s\n", toStringSList(list));
	squeezer(list);
	printf("After squeezer: %s\n", toStringSList(list));
	validateSList(list);

	insertEndSList(0, list);
	printf("rehearse i list: %s\n", toStringSList(list));
	rehearse(list);
	printf("rehearse o list: %s\n", toStringSList(list));

	insertEndSList(999, list);
	printf("The should end with (999): %s\n", toStringSList(list));
	validateSList(list);
#endif
}
#if 1
/**
* testEmpty() tests ToStringSList(), isEmptySList(), lengthSList(),
* insertFrontSList(), and insertEndSList() on an empty list.
* Prints summary information of the tests
* and halts the program if errors are detected.
*/

void testEmpty() {
	printf(">Start testEmpty: \n");
	pSList p = makeSList();

	printf("After construction should be NOTHING: %s\n", toStringSList(p));
	printf("isEmptySList() should be true(1): It is (%d)\n", isEmptySList(p));
	printf("lengthSList() should be 0: It is %d\n", lengthSList(p));
	validateSList(p);

	insertFrontSList(3, p);
	printf("After insertFrontSList(3) [ 3 ]: It is %s\n", toStringSList(p));

	insertEndSList(5, p);
	printf("After insertEndSList(5) [ 3 5 ]: %s\n", toStringSList(p));
	validateSList(p);	
	freeSList(p);
	printf("<testEmpty()\n");
}

/**
* testInsertFront() tests toStringSList(), isEmptySList(), lengthSList(),
* insertFrontSList().
* It prints summary information of the tests and halts the program if errors are detected.
*/

void testInsertFront() {
	printf(">Start InsertFrontSList() test: \n");
	pSList list = makeSList();

	insertFrontSList(3, list);
	insertFrontSList(2, list);
	insertFrontSList(1, list);
	printf("After insertFrontSList [ 1 2 3]: %s\n", toStringSList(list));
	verify(strcmp(toStringSList(list), "[ 1 2 3 ]") == 0, "InsertFrontSList() failed");
	verify(isEmptySList(list) == 0, "isEmptySList() after insertFrontSList() failed");
	
	printf("lengthSList() should be 3. It is: %d\n", lengthSList(list));
	verify((lengthSList(list) == 3), "lengthSList() failed");
	validateSList(list);
	freeSList(list);
	printf("<testInsertFront \n");
}

/**
* testInsertEnd() tests toStringSList(), isEmptySList(), lengthSList(),
* insertFrontSList().
* It prints summary information of the tests and halts the program
* if errors are detected.
*/

void testInsertEnd() {
	pSList list = makeSList();

	printf(">Start InsertEndSList() test: \n");
	insertEndSList(6, list);
	insertEndSList(7, list);

	printf("After insertEndSList [ 6 7 ]: %s\n", toStringSList(list));
	printf("lengthSList() should be 2. It is: %d\n", lengthSList(list));
	verify((lengthSList(list) == 2), "lengthSList() after insertEndSList() failed");
	validateSList(list);
	freeSList(list);	
	printf("<InsertEndSList()\n");
}

void testDelete() {
	int i;
	int a[] = { 1, 2, 3, 4, 5 }; 
	int size = sizeof(a) / sizeof(a[0]);
	pSList list = makeSList();

	printf(">Start delete.....SList() test: \n");
	printf("insertEndSList 1, 2, 3, 4, 5\n");
	for (i = 0; i < size; i++) insertEndSList(a[i], list);
	printf("After insertEndSList 1 2 3 4 5: %s\n", toStringSList(list));

	deleteFrontSList(list);
	printf("After deleteFrontSList 2 3 4 5: %s\n", toStringSList(list));
	validateSList(list);
	deleteFrontSList(list);
	printf("After deleteFrontSList 3 4 5: %s\n", toStringSList(list));
	validateSList(list);
	deleteFrontSList(list);
	printf("After deleteFrontSList 4 5: %s\n", toStringSList(list));
	deleteFrontSList(list);
	printf("After deleteFrontSList 5: %s\n", toStringSList(list));
	deleteFrontSList(list);
	printf("After deleteFrontSList NOTHING LEFT: %s\n", toStringSList(list));
	validateSList(list);

	printf("insertEndSList 1, 2, 3, 4, 5\n");
	for (i = 0; i < size; i++) insertEndSList(a[i], list);
	printf("After insertEndSList 1 2 3 4 5: %s\n", toStringSList(list));

	deleteEndSList(list);
	printf("After deleteEndSList 1 2 3 4: %s\n", toStringSList(list));
	validateSList(list);
	deleteEndSList(list);
	printf("After deleteEndSList 1 2 3: %s\n", toStringSList(list));
	validateSList(list);
	deleteEndSList(list);
	printf("After deleteEndSList 1 2: %s\n", toStringSList(list));
	validateSList(list);
	deleteEndSList(list);
	printf("After deleteEndSList 1: %s\n", toStringSList(list));
	validateSList(list);
	deleteEndSList(list);
	printf("After deleteEndSList NOTHING LEFT: %s\n", toStringSList(list));
	validateSList(list);

	printf("insertEndSList 1, 2, 3, 4, 5\n");
	for (i = 0; i < size; i++) insertEndSList(a[i], list);
	printf("After insertEndSList 1 2 3 4 5: %s\n", toStringSList(list));

	deleteSList(1, list);
	printf("After deleteSList(1) 2 3 4 5: %s\n", toStringSList(list));
	validateSList(list);

	deleteSList(3, list);
	printf("After deleteSList(3) 2 4 5: %s\n", toStringSList(list));
	validateSList(list);

	deleteSList(5, list);
	printf("After deleteSList(5) 2 4: %s\n", toStringSList(list));
	validateSList(list);

	deleteSList(4, list);
	printf("After deleteSList(4) 2: %s\n", toStringSList(list));
	validateSList(list);

	deleteSList(2, list);
	printf("After deleteSList(2) NOTHING LEFT: %s\n", toStringSList(list));
	validateSList(list);

	freeSList(list);
	printf("<testDelete.....SList()\n");
}

void testInsertTail() {
	int i;
	int a[] = { 1, 2, 3, 4, 5 };
	int size = sizeof(a) / sizeof(a[0]);
	pSList list = makeSList();

	printf(">Start insertTailSList() INITIAL testing: \n");
	printf("insertEndSList 1, 2, 3, 4, 5\n");
	for (i = 0; i < size; i++) insertEndSList(a[i], list);
	printf("After insertEndSList 1 2 3 4 5: %s\n", toStringSList(list));

	deleteFrontSList(list);
	printf("After deleteFrontSList 2 3 4 5: %s\n", toStringSList(list));
	validateSList(list);

	deleteEndSList(list);
	printf("After deleteFrontSList 3 4: %s\n", toStringSList(list));
	validateSList(list);

	deleteFrontSList(list);
	printf("After deleteTailSList 3: %s\n", toStringSList(list));
	validateSList(list);

	deleteFrontSList(list);
	printf("After deleteTailSList NOTHING: %s\n", toStringSList(list));
	validateSList(list);

	printf("If no ERROR is printed above, then InsertTail INITIAL test is passed\n");
	printf("<testInsertTail\n");
}

#define MAX_ITERATION 30000
void testInsertTailTiming() {
	int i;
	pSList list;
	clock_t start;
	double f;	// front	O(1)
	double e;	// end		O(n)
	double t;	// tail		O(1)

	printf(">Start insertTailSList() TIMING test: \n");
	printf("insertFrontSList: O(1)\n");
	list = makeSList();
	start = clock();
	for (i = 0; i < MAX_ITERATION; i++) insertFrontSList(i, list);
	printf("duration=%f sec\n", (f = (double)(clock() - start) / CLOCKS_PER_SEC));
	validateSList(list);
	freeSList(list);

	printf("insertEndSList; O(n)\n");
	list = makeSList();
	start = clock();
	for (i = 0; i < MAX_ITERATION; i++) insertEndSList(i, list);
	printf("duration=%f sec\n", (e = (double)(clock() - start) / CLOCKS_PER_SEC));
	validateSList(list);
	freeSList(list);

	printf("insertTailSList: O(1)\n");
	list = makeSList();
	start = clock();
	for (i = 0; i < MAX_ITERATION; i++) insertTailSList(i, list);
	printf("duration=%f sec\n", (t = (double)(clock() - start) / CLOCKS_PER_SEC));
	validateSList(list);
	freeSList(list);

	if ( e > (t + f) * 100) 
		printf("<InsertTail TIMING TEST is passed\n");
	else
		printf("<InsertTail TIMING TEST was not successful\n");
}

#endif