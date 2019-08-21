/**
 * This is a sort of assert() but provided with java like stack dump 
 * which is not available in the standard C.
 *
 * @author Youngsup Kim
 * 2014/03/15 Creation
 * 2014/03/20 Changed it to macro instead of function such that it can show 
 *            the real meaningful function name and file name. Otherwise, 
 *			  it always shows verify() as func name and verify.cpp as filename. 
 *
 * If DEBUG is defined, verify() checks an invariant and prints an error message 
 * if it fails. If invariant is true, this method does nothing.  
 * If invariant is false, * the message is printed, followed by a dump of the program 
 * function name, filename, and line number.
 * If DEBUG is not defined, it does nothing.
 *
 * @param invariant - the condition to be verified
 * @param message - the error message to be printed if the invariant fails to
 *                  hold true.
 */

#ifndef verify_h
#define verify_h

#if defined(NDEBUG) // Release Mode 
#define verify(invariant, message) { ; }	// do nothing
#else
#define verify(invariant, message) {											\
	if (!invariant) {															\
		fprintf(stderr, "***ERROR: %s ***\n", message);							\
		fprintf(stderr, "at %s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);	\
	} \
}
#endif

#endif verify_h

