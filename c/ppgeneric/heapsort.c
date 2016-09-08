/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890

	heapsort.c - Heap Sort implementations.  

	The first activities here tried to implement what I found in pseudocode,
more or less, in Wikipedia.  First draft was from a read on July 27, 2016 of:
	
	http://en.wikipedia.org/wiki/Heapsort

	I also added one from pseudocode out of the CLRS Algorithms book.

	NOTE:  Add formal bibliography somewhere eventually.
 */

#include <string.h>
#include "itemtype.h"

/*
	Below are modified from a paste of the wiki overview.
	"i is the index of the current node":
 */

static inline int wppc_iParent(int i) { return (i - 1) / 2; }

static inline int wppc_iLeftChild(int i)  { return 2 * i + 1; }
static inline int wppc_iRightChild(int i) { return 2 * i + 2; }

/* 
    clrspcMaxHeapify - Algorithms book by authors Cormen, Leiserson, Rivest and Stein
published in 2009
 */

void clrspcOriginalMaxHeapify(ItemType itemArray[], int itemCount, int rootIndex, ComparisonFnPtr cmpFn) {
	/* Note that this version presumes possible calls for rootIndex being an
		end leaf, necessary because it is a recursive function.  */
	int l = wppc_iLeftChild(rootIndex);
	int largest;
	int r = wppc_iRightChild(rootIndex);

	if ( l < itemCount && cmpFn(itemArray+l,itemArray+rootIndex) > 0 )
		largest = l;
	else largest = rootIndex;

	if ( r < itemCount && cmpFn(itemArray+r,itemArray+largest) > 0 )
		largest = r;

	if ( largest != rootIndex ) {
		SwapItem(itemArray+rootIndex,itemArray+largest);
		clrspcOriginalMaxHeapify(itemArray,itemCount,largest,cmpFn);
	}
}

/* Here is my reorganized one, which I think is clearer and at least as good... */
void clrspcXCMaxHeapify(ItemType itemArray[], int itemCount, int rootIndex, ComparisonFnPtr cmpFn) {
	int l = wppc_iLeftChild(rootIndex);
	int r = l + 1; /* cheaper calculation? */
	int swapi;

	if ( l >= itemCount ) return; /* return because there is no leaf. */
	if ( r < itemCount ) {
		swapi = ( cmpFn(itemArray+l,itemArray+r) > 0 ) ? l : r;
		/* note that I changed this so that on equal,
			the smaller value ends up on the right. */
	} else swapi = l;
	if ( cmpFn(itemArray+rootIndex,itemArray+swapi) > 0 )
		return;			/* return because root is largest of three. */

	/* Otherwise swap the chosen largest,
		and call recursively for that swap index: */
	SwapItem(itemArray+rootIndex,itemArray+swapi);
	clrspcOriginalMaxHeapify(itemArray,itemCount,swapi,cmpFn);
}

void clrspcBuildMaxHeap(ItemType itemArray[],int itemCount, ComparisonFnPtr cmpFn) {
	/* array length and heap-size are apparently the same for this use.  Heap-size
		only acquires an interesting difference when heapsort operates, reducing
		the heap size section at each pull of a maximum.
		*/

	int i;
	int lasti = itemCount - 1;
	for(i=wppc_iParent( lasti ); i>=0; --i)
		clrspcXCMaxHeapify(itemArray,itemCount,i,cmpFn);
		/* clrspcOriginalMaxHeapify(itemArray,itemCount,i,cmpFn); */
}

void clrspcHeapSort(ItemType itemArray[],int itemCount, ComparisonFnPtr cmpFn) {
	int i;
	int heapsize = itemCount;

	clrspcBuildMaxHeap(itemArray,itemCount,cmpFn);
	for(i=(itemCount-1); i>0; --i) {
		SwapItem(itemArray,itemArray+i);
		heapsize--;
		clrspcXCMaxHeapify(itemArray,heapsize,0,cmpFn);
	}
}

/* shiftDown - from wiki:
(Repair the heap whose root element is at index 'start', assuming the heaps rooted at its children are valid)
 */
void wppcShiftDown(ItemType itemArray[], int startIndex, int endIndex, ComparisonFnPtr cmpFn) {
    /* input: an array itemArray[] to be repaired as a heap, with initial root
	 index and end index.

	NOTE:  I am using this, as it seems to me to be clearer.  Got the idea from old Sedgewick.
     */
	int childi = wppc_iLeftChild(startIndex);
    int rooti = startIndex;
	int swapi;

	/* Only enter loop if the defined left child is within the end index designation. */
	while ( childi <= endIndex ) {
		/* Start by assigning swapi to be the left child. */
		swapi = childi;
		/* If there is a right child, and it is larger, assign swapi to that. */
		/* This we bias the larger child as the left hand one. */
		if ( ( childi+1 ) <= endIndex ) {
			if ( cmpFn(itemArray+childi,itemArray+childi+1) < 0 )
				swapi = childi + 1;	
		}
		/* If root is larger than or equal to the assigned swap child, then return without doing anything. */
		if ( cmpFn(itemArray+rooti,itemArray+swapi) >= 0 )
			return;
		/* Otherwise, swap root with the assigned swap child, and assign the next root to be said child. */
		
		SwapItem(itemArray+rooti,itemArray+swapi);
		rooti = swapi;

		/* Save a little by doing the left child calculation only once. */
		childi = wppc_iLeftChild(rooti);
	}
}

void wppcCloserToOriginalShiftDown(ItemType itemArray[], int startIndex, int endIndex, ComparisonFnPtr cmpFn) {
	int childi;
    int rooti = startIndex;
	int swapi;

	while ( wppc_iLeftChild(rooti) <= endIndex ) {
		childi = wppc_iLeftChild(rooti);
		swapi = rooti;
		
		if ( cmpFn(itemArray+swapi,itemArray+childi) < 0 )
			swapi = childi;
		if ( ( childi+1 ) <= endIndex && cmpFn(itemArray+swapi,itemArray+childi+1) < 0 )
			swapi = childi+1;
		/* This we bias the larger child as the left hand one. */

		if ( swapi == rooti ) return;

		SwapItem(itemArray+rooti,itemArray+swapi);
		rooti = swapi;
	}
}

void wppcShiftDownHeapify(ItemType itemArray[], int itemCount, ComparisonFnPtr cmpFn) {
    /* input: an unordered array itemArray of length itemCount */
	int lasti = itemCount - 1;
	int starti = wppc_iParent( lasti );

	while ( starti >= 0 ) wppcShiftDown( itemArray, starti--, lasti, cmpFn );
}

void wppcShiftDownHeapSort(ItemType itemArray[], int itemCount, ComparisonFnPtr cmpFn) {
    /* input: an unordered array itemArray of length itemCount */
	wppcShiftDownHeapify(itemArray,itemCount,cmpFn);

	int endi = itemCount - 1;

	while ( endi > 0 ) {
		SwapItem(itemArray+endi,itemArray);
		wppcShiftDown( itemArray, 0, --endi, cmpFn );
	}
}

void wppcShiftUp(ItemType itemArray[], int startIndex, int endIndex, ComparisonFnPtr cmpFn) {
    /* input:  startIndex represents the limit of how far up the heap to sift.
                   endIndex is the node to sift up.
     */
	int childi = endIndex;
	int parenti;

	while ( childi > startIndex ) {

		parenti = wppc_iParent( childi );

		if ( cmpFn(itemArray+parenti,itemArray+childi) < 0 ) {
			SwapItem(itemArray+parenti,itemArray+childi);
			childi = parenti;
		} else {
			return;
		}

	}	
}

void wppcShiftUpHeapify(ItemType itemArray[], int itemCount, ComparisonFnPtr cmpFn) {
    /* input: an unordered array itemArray of length itemCount */
	int focusi = 1;

	while ( focusi < itemCount ) {
		wppcShiftUp( itemArray, 0, focusi++, cmpFn );
	}
}

/*
int (*cmp)(const void *, const void *)
*/
void wppcShiftUpHeapSort(ItemType itemArray[], int itemCount, ComparisonFnPtr cmpFn) {
    /* input: an unordered array itemArray of length itemCount */
	wppcShiftUpHeapify(itemArray,itemCount,cmpFn);

	int endi = itemCount - 1;

	while ( endi > 0 ) {
		SwapItem(itemArray+endi,itemArray);
		wppcShiftDown( itemArray, 0, --endi, cmpFn );
	}
}

/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890

End of heapsort.c
 */

