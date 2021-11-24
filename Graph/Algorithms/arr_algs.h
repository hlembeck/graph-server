#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "structures.h"

/* defines an interval(segment). Low and high are usually indices in an array. */
typedef struct segment{
	int low;
	int high;
	long value;
} segment;

/*
Max subarray
*/
//Recurisve (divide and conquer)
segment max_subarray(long *arr, segment bounds);
//Non-recursive
segment max_subarray2(long *arr, int len);


/* 
Heapsort 
*/
//Assumes children of i form max heaps, then makes tree rooted at i a max heap.
void max_heapify(long *arr, int len, int i);
void max_heapify_recursive(long *arr, int len, int i);

void max_heap(long *arr, int len);

void heapsort(long *arr, int len, int heapsize);