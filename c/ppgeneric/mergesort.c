/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890

	mergesort.c - Merge Sort implementations.  

	https://en.wikipedia.org/wiki/Merge_sort

	Conceptually, a merge sort works as follows:

		1.	Divide the unsorted list into n sublists, each containing 1
		element (a list of 1 element is considered sorted).
		2.	Repeatedly merge sublists to produce new sorted sublists until
		there is only 1 sublist remaining. This will be the sorted list.

 */

#include <string.h>
#include "itemtype.h"

extern void hps2MergeSortArray(ItemType *pItemArray, ItemType *pResult, int iStart, int iEnd, ComparisonFnPtr cmpFn);
extern void xcMerge(ItemType *pItemArray0, int itemCount0, ItemType *pItemArray1,int itemCount1, ItemType *pItemArray2, int itemCount2, ComparisonFnPtr cmpFn);

static inline int _min(int n1, int n2) { return ( n1 < n2 ) ? n1 : n2; }

/* The following version is translated from python from page 83 of an O'Reilly book
	on Algorithms.
 */
void hps2MergeSort(ItemType itemArray[], int itemCount, ComparisonFnPtr cmpFn) {
	// Merge Sort itemArray in place.
	ItemType *b = CopyVector(itemArray,itemCount);
	
	hps2MergeSortArray(b, itemArray, 0, itemCount, cmpFn);
}

void hps2MergeSortArray(ItemType *pItemArray, ItemType *pResult, int iStart, int iEnd, ComparisonFnPtr cmpFn) {
	int delta = iEnd - iStart;
	int i,j;
	int index;
	int mid;

	if ( delta < 2 ) return;
	if ( delta == 2 ) {
		if ( cmpFn(pResult+iStart,pResult+iStart+1) > 0 )
			SwapItem(pResult+iStart,pResult+iStart+1);
		return;
	}

	mid = ( iStart + iEnd ) / 2;
	hps2MergeSortArray(pResult, pItemArray, iStart, mid, cmpFn);
	hps2MergeSortArray(pResult, pItemArray, mid, iEnd, cmpFn);
	
	/* Merge pItemArray left and right sides */
	i = iStart;
	j = mid;
	index = iStart;
	while ( index < iEnd ) {
		/* The following says:  If the second index is greater than the end, or
			the first index is less than the midpoint and it's data is less than
			the second, ... */
		if ( j >= iEnd || ( i < mid && cmpFn(pItemArray+i,pItemArray+j) < 0 ) ) {
			pResult[index] = pItemArray[i++];
		} else {
			pResult[index] = pItemArray[j++];
		}
		++index;
	}
}

/* The following was coded looking directly at Wiki C code, because the only
	pseudocode was for linked lists, and I really wanted to get the Bottom up,
	which is without recursion. */
void wpBottomUpMergeSort(ItemType *pItemArray, int itemCount, ComparisonFnPtr cmpFn) {
	ItemType *b = (ItemType *) calloc(itemCount,ItemTypeSize);
	int espan;
	int i,j,k;
	int span;

	// As per wiki, array is full of runs of length span.
	for( span=1;  span < itemCount;  span *= 2) { /* this line wiki code */
		for(i=0; i<itemCount; i += ( 2*span ) ) { /* this line wiki code */
			j = _min(i+span,itemCount);
			k = _min(i+2*span,itemCount);
			if ( j == itemCount ) {
				CopyVectorData(b+i,pItemArray+i,(j-i));
			} else {
				xcMerge(b+i,(k-i),pItemArray+i,span,pItemArray+j,(k-j),cmpFn);
			}
		}	
		CopyVectorData(pItemArray,b,itemCount);
	}
}

void xcMerge(ItemType *pItemArray0, int itemCount0, ItemType *pItemArray1,int itemCount1, ItemType *pItemArray2, int itemCount2, ComparisonFnPtr cmpFn) {
	int i = 0;
	int j1, j2;

	if ( itemCount0 != ( itemCount1 + itemCount2 ) ) {
		fprintf(stderr,"Programmer error merge counts:  %d != %d + %d\n",
			itemCount0, itemCount1, itemCount2 ); 
		exit(9);
	}
	j1 = j2 = 0;
	while ( j1 < itemCount1 && j2 < itemCount2 ) {

		if ( cmpFn(pItemArray1+j1,pItemArray2+j2) < 0 ) {
			pItemArray0[i++] = pItemArray1[j1++];
		} else {
			pItemArray0[i++] = pItemArray2[j2++];
		}
	}

	if ( j1 < itemCount1 ) CopyVectorData(pItemArray0+i,pItemArray1+j1, (itemCount1-j1) );
	if ( j2 < itemCount2 ) CopyVectorData(pItemArray0+i,pItemArray2+j2, (itemCount2-j2) );
}

void xcTopDownMergeSortRecursion(ItemType *pItemArray, ItemType *pBuffer, int itemCount, ComparisonFnPtr cmpFn) {
	int m = itemCount / 2;

	if ( itemCount < 2 ) return;

	xcTopDownMergeSortRecursion(pItemArray,pBuffer,m,cmpFn);
	xcTopDownMergeSortRecursion(pItemArray+m,pBuffer+m,itemCount-m,cmpFn);
	xcMerge(pBuffer,itemCount,pItemArray,m,pItemArray+m,itemCount-m,cmpFn);
	CopyVectorData(pItemArray,pBuffer,itemCount);
}

void xcTopDownMergeSort(ItemType itemArray[], int itemCount, ComparisonFnPtr cmpFn) {
	ItemType *b = (ItemType *) calloc(itemCount,ItemTypeSize);

	xcTopDownMergeSortRecursion(itemArray, b, itemCount, cmpFn);
}

/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890
End of mergesort.c
 */

