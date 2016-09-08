/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890

	insertionsort.c - Inserton Sort implementations.  

	The first activities here tried to implement what I found in pseudocode,
more or less, in Wikipedia.  First draft was from a read on August 18, 2016 of:
	
	https://en.wikipedia.org/wiki/Insertion_sort

		for i ← 1 to length(A)-1
			j ← i
			while j > 0 and A[j-1] > A[j]
				swap A[j] and A[j-1]
				j ← j - 1
			end while
		end for
 */

#include <string.h>
#include "itemtype.h"

void wppcInsertionSort(ItemType itemArray[], int itemCount, ComparisonFnPtr cmpFn) {
	int i, j;

	for (i=1; i<itemCount; ++i) {
		j = i;
		/* Simply starts on the left, and gradually scoots any item that is
			less on the right to the left of anything that is its greater,
			until the right end of the array is encountered.
		 */
		while( j > 0 && cmpFn(itemArray+j-1,itemArray+j) > 0 ) {
			SwapItem(itemArray+j-1,itemArray+j);
			--j;
		}
	}
}

/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890
End of insertionsort.c
 */

