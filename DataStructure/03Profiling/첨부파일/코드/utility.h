
/**		ECE20010 Data Structure; 2014 Spring
  *		Instructor: Youngsup Kim
  *
  *		Filename: utility.h
  *		Created: 2014.03.01
  */

/** utility.h */
#ifndef utility_h 
#define utility_h

#define WELCOME_MESSAGE "Welcome to ECE20010!\nGod is good all the time!\n"

#define COMPARE(x, y)	(((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)
#define SWAP(x, y, t)	((t) = (x), (x) = (y), (y) = (t))

#define MALLOC(p, sizeInByte) \
if (!((p) = (int*)malloc(sizeInByte))) { \
	fprintf(stderr, "Insufficient memory when allocating %d bytes.\n", \
	sizeInByte); \
	exit(EXIT_FAILURE);\
}

#define REALLOC(p, sizeInByte) \
if (!((p) = realloc(p, sizeInByte))) { \
	fprintf(stderr, "Insufficient memory when allocating %d bytes.\n", \
	sizeInByte); \
	exit(EXIT_FAILURE); \
}

#define CALLOC(p, n, oneEntrySizeInByte) { \
if (!((p) = realloc(p, oneEntrySizeInByte)))	\
	fprintf(stderr, "Insufficient memory when allocating %d bytes.\n", \
	oneEntrySizeInByte); \
	exit(EXIT_FAILURE); \
}

#define FREE(p) if (p != NULL) free(p); 

// Use the following if system("pause") is unavailable. 
#define PUASE {printf("\nPress any key to exit."); getch();}

#endif 