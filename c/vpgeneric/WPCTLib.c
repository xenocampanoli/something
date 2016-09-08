/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890

	C implementation of Heap oriented methods from Wikipedia Pseudocode.

	This tries to implement what I found in Wikipedia.  First draft was from a
read on July 27, 2016 of:  transation code://en.wikipedia.org/wiki/Heapsort

Other citings should be added here corresponding to code additions. 
 */

#include <string.h>
#include "./itemtype.h"

#define IiSize sizeof(ItemType)

/*
	Below are modified from a paste of the wiki overview.
	"i is the index of the current node":
 */

inline int iParent(int i)     { return (i - 1) / 2; }

inline int iLeftChild(int i)  { return 2 * i + 1; }
inline int iRightChild(int i) { return 2 * i + 2; }

/* Swap uses memcpy for maximum speed, but with universality. */
inline void SwapItem(ItemType *pBuffer,ItemType *pRoot,ItemType *pChild) {
	memcpy(pBuffer,pRoot,IiSize);
	memcpy(pRoot,pChild,IiSize);
	memcpy(pChild,pBuffer,IiSize);
}

/* siftDown - from wiki:
(Repair the heap whose root element is at index 'start', assuming the heaps rooted at its children are valid)
 */

void siftDown(ItemType itemArray[], int startIndex, int endIndex) {
    /* input: an array itemArray[] to be repaired as a heap, with initial root
	 index and end index.
     */
    int rooti = startIndex;
	int childi = iLeftChild(rooti);
	ItemType itembuffer;

	do {
		
		if ( ( childi + 1 ) <= endIndex )            ++childi;

		if ( itemTypeCmp(itemArray+rooti,itemArray+childi) >= 0 ) return;
		if ( itemArray[childi] <= itemArray[rooti] ) return;

		SwapItem(&itembuffer,itemArray+rooti,itemArray+childi);

		rooti = childi;

		childi = iLeftChild(rooti);

	} while ( childi < endIndex );
}

void siftDownHeapify(ItemType itemArray[], int itemCount) {
    /* input: an unordered array itemArray of length itemCount */
	int lasti = itemCount - 1;
	int focusi = iParent( lasti );

	while ( focusi >= 0 ) siftDown( itemArray, focusi--, lasti );
}

void siftDownHeapSort(ItemType itemArray[], int itemCount) {
    /* input: an unordered array itemArray of length itemCount */
	siftDownHeapify(itemArray,itemCount);

	int endi = itemCount - 1;
	ItemType itembuffer;

	while ( endi > 0 ) {
		SwapItem(&itembuffer,itemArray+endi,itemArray);
		siftDown( itemArray, 0, --endi );
	}
}

void siftUp(ItemType itemArray[], int startIndex, int endIndex) {
    /* input:  startIndex represents the limit of how far up the heap to sift.
                   endIndex is the node to sift up.
     */
	int childi = endIndex;
	int parenti;
	ItemType itembuffer;

	while ( childi > startIndex ) {

		parenti = iParent( childi );

		if ( itemArray[parenti] < itemArray[childi] ) {
			SwapItem(&itembuffer,itemArray+parenti,itemArray+childi);
			childi = parenti;
		} else {
			return;
		}

	}	

}

void siftUpHeapify(ItemType itemArray[], int itemCount) {
    /* input: an unordered array itemArray of length itemCount */
	int focusi = 1;

	while ( focusi < itemCount ) {
		siftUp( itemArray, 0, focusi++ );
	}
}

void siftUpHeapSort(ItemType itemArray[], int itemCount) {
    /* input: an unordered array itemArray of length itemCount */
	siftUpHeapify(itemArray,itemCount);

	int endi = itemCount - 1;
	ItemType itembuffer;

	while ( endi > 0 ) {
		SwapItem(&itembuffer,itemArray+endi,itemArray);
		siftDown( itemArray, 0, --endi );
	}
}
