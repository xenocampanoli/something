/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890

	externalsort.c - External Sort implementations.  

	https://en.wikipedia.org/wiki/External_sorting

 */

#include <time.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../env.h"
#include "sppsorts.h"

#define FileDivisionLimit 32

static inline int wppc_iParent(int i) { return (i - 1) / 2; }
static inline int wppc_iLeftChild(int i)  { return 2 * i + 1; }

static inline int wppcPreSort(int mblDivisor, int nMBL, FILE *ifp, char **fSpecArray) {
	int k;
	char *b (ItemType *);
	if ( nMBL % mblDivisor ) k++;

	return k;
}

static inline int GetDataDivisionCount(char storageType, int maxItems, size_t maxAvailableBufferSize) {
	size_t itemRecordBufferBytes = GetMaxItemRecordReadBufferBytes(storageType);
	int k = maxAvailableBufferSize / itemRecordBufferBytes;
	if ( k % 2 ) k++;
	if ( k > FileDivisionLimit ) {
		fprintf(stderr,
"FATAL:  MBL size of %d leads to %d divisions, which exceeds limit %d\n",
			(int)maxAvailableBufferSize,k,FileDivisionLimit);
		fprintf(stderr,"Total Data seen is %d.",fileSize);
		exit(9);
	}

	return k;
}

static inline void SwapIndexItem(ItemTypeHeapNode *pItem1,ItemTypeHeapNode *pItem2) {
	ItemTypeHeapNode buffer	= *pItem1;
	*pItem1					= *pItem2;
	*pItem2					= buffer;
}

/* wppcMinHeapShiftDown - from wiki:
(Repair the heap whose root element is at index 'start', assuming the heaps rooted at its children are valid)
 */
void wppcMinHeapShiftDown(ItemTypeHeapNode itemArray[], int startIndex, int endIndex, ComparisonFnPtr cmpFn) {
    /* input: an array itemArray[] to be repaired as a heap, with initial root
	 index and end index.

	NOTE:  This is almost the same as the maxheap one in heapsort.c.
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
			if ( cmpFn(itemArray[childi].pitem,itemArray[childi+1].pitem) > 0 )
				swapi = childi + 1;	
		}
		/* If root is larger than or equal to the assigned swap child, then return without doing anything. */
		if ( cmpFn(itemArray[rooti].pitem,itemArray[swapi].pitem) <= 0 )
			return;
		/* Otherwise, swap root with the assigned swap child, and assign the next root to be said child. */
		
		SwapIndexItem(itemArray+rooti,itemArray+swapi);
		rooti = swapi;

		/* Save a little by doing the left child calculation only once. */
		childi = wppc_iLeftChild(rooti);
	}
}

void wppcMinHeapShiftDownHeapify(ItemTypeHeapNode itemArray[], int itemCount, ComparisonFnPtr cmpFn) {
    /* input: an unordered array itemArray of length itemCount */
	int lasti = itemCount - 1;
	int starti = wppc_iParent( lasti );

	while ( starti >= 0 ) wppcMinHeapShiftDown( itemArray, starti--, lasti, cmpFn );
}

void wppcPMerge(ItemType *pItemHeap[], int pItemHeapCount[],  int arrayCount, ComparisonFnPtr cmpFn) {
	int *ina = (int *) calloc(arrayCount,sizeof(int));
}

/* Two kinds of interesting external merge sorts in the wiki:

	1.  Generation of sections into heaps, then merge in the heapfile data.

	2.	Generation of sections into sorted files that fit into memory, then
		divide and conquer traditional binary merge.

NOTE:  I'll use the acronym MBM for Max Buffer Memory.  This will be a
	guestimated number above and beyond what the rest of the program uses,
	but it should be engineered as well as is practical.
12345678901234567890123456789012345678901234567890123456789012345678901234567890
 */

typedef struct PreSortRecord {
	int presortitems;
	char fspec[80];
} PreSortType;

bool ReadNextSegment(char storageType, FILE *iFp, int bufferitems, ItemType *pItemArray, int *itemsRead) {
	int itemsread;
	ItemType *pitemlist;
	
	ValidateStorageType(storageType);
	switch(storageType) {
	case NativeStorage:
		*itemsRead = ReadNativeVectorSegment(iFp, ( nMBL / ItemTypeSize ), &itemcount);
		break;
	case CSV_Storage:
		*itemsRead = ReadCSV_VectorSegment(iFp, nMBL, &itemcount);
		break;
	default:
		fprintf(stderr,"FATAL:  programmer error inside ReadNextSegment.\n");
		exit(9);
	}

	if (*itemsRead > 0) return true; 
	return false;
}

int WriteNextSegment(char storageType, ItemType *pItemArray, int itemCount) {
	int ric;
	
	ValidateStorageType(storageType);
	switch(storageType) {
	case NativeStorage:
		ric = WriteNativeVectorSegment(pPSR->fp, pItemArray, itemCount);
		break;
	case CSV_Storage:
		ric = WriteCSV_VectorSegment(pPSR->fp, pItemArray, itemCount);
		break;
	default:
		fprintf(stderr,"FATAL:  programmer error inside WriteNextSegment.\n");
		exit(9);
	}

	return ric;
}

/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890
	This presort is the intended universal.  It should work with the min-heap,
	the divide and conquer, and the append external sort.
 */
PreSortType * xcPreSortSubsets(char storageType, FILE *iFp, int nMBL, char *sortType, ComparisonFnPtr cmpFn, int *preSortedFileCount) {
	int filesize = GetFileSize(iFp);
	int maxitems = GetMaxItemsInFile(storageType, filesize);
	int bufferitems = GetBufferItemsGivenMaxBufferSize(char storageType, nMBL);
	PreSortType *psa = (PreSortType *) calloc(k+1,sizeof(PreSortType));
	int psi = 0;
	char psfsprefix[32];
	bool u;
	ItemType *pib = calloc(bufferitems,ItemTypeSize);
	int itemsread;
	int itemswritten;
	FILE *ofp;

	sprintf(psfsprefix,"/tmp/xcPreSort%d",(int)time(NULL));

	psa[0].pitemarray = pib;
	while ( ReadNextSegment(storageType, iFp, bufferitems, pib, &itemsread) ) {

		if ( psi >= k ) {
			/* Note:  This may not be the best way to do this, and it must
				be tested to make sure it is okay. The last read should
				return false from zero records read.
			 */
			fprintf(stderr,"FATAL:  Input data exceeds allocated presort resources.\n");
			exit(9);
		}

		u = true;
		if ( u && strcmp(sortType,NativeQSort) == 0 )			{ u=false; qsort(pib,itemsread,ItemTypeSize,cmpFn); }
		if ( u && strcmp(sortType,CLRSPCHeapSort) == 0 )		{ u=false; clrspcHeapSort(pib,itemsread,cmpFn); }
		if ( u && strcmp(sortType,WPPCShiftDownHeapSort) == 0 )	{ u=false; wppcShiftDownHeapSort(pib,itemsread,cmpFn); }
		if ( u && strcmp(sortType,WPPCShiftUpHeapSort) == 0 )	{ u=false; wppcShiftUpHeapSort(pib,itemsread,cmpFn); }

		sprintf(psa[psi].fspec,"%s_file%d.%c.tmp",psfsprefix,psi,storageType);
		ofp = fopen(psa[psi].fspec,"w");
		itemswritten = WriteNativeVectorSegment(ofp, pib, itemsread);
		fclose(ofp);
		if (itemswritten != itemsread) {
			fprintf(stderr,"FATAL:  Presorted output records %d differs from items read %d.\n",itemswritten,itemsread);
			exit(9);
		}
		psa[psi].presortitems = itemswritten;
		++psi;

		if ( itemswritten < bufferitems ) break; /* end of primary input file */

	}
	*preSortedFileCount = psi;
	return psa;
}

void wppcMinHeapMultiMergeExternalSortCopy(FILE *iFp, int nMBL, char *preSortType, char storageType, ComparisonFnPtr cmpFn, FILE *oFp) {
	int psfilecount;
	int i;

	/* Pre-sort large file into psfilecount small ones and return array of
		structs with filepointers to these open for reading. */
	PreSortType *ppsa = xcPreSortSubsets(iFp,nMBL,preSortType,storageType,cmpFn,&psfilecount);

	int halfMBL = nMBL/2;
}

typedef struct ItemTypeHeapStruct {
	ItemType *pitemarray;
	int itemindex;
	int presortitems;
	int rereaditems;
	char fspec[80];
	FILE *fp;
} ItemTypeHeapNode;

void xcInitCopyHeapNode(ItemTypeHeapNode *pHeap, char *fSpec, int preSortItems, int bRItems) {
	pHeap->fp = fopen(fSpec,"r");
	strcpy(pHeap->fspec,fSpec);
	pheap->itemindex = 0;
	pHeap->presortitems = preSortItems;
	pHeap->rereaditems = 0;
	pHeap->pitemarray = calloc(bRItems,ItemTypeSize);
	pHeap->itemsread = 0;
}

void xcInitSlabHeapNode(ItemTypeHeapNode *pHeap, char *fSpec, int preSortItems, ItemTypeMemStack *pITMS) {
	pHeap->fp = fopen(fSpec,"r");
	strcpy(pHeap->fspec,fSpec);
	pheap->itemindex = 0;
	pHeap->presortitems = preSortItems;
	pHeap->rereaditems = 0;
	pHeap->pitemarray = xcPopItemMemStack(pITMS);
	pHeap->itemsread = 0;
}

typedef struct {
	/* counts are short, as FileDivisionLimit will tend to be around 32. */
	size_t maxmemory;
	size_t memitems;
	short readycount;
	short usedupcount;
	ItemType **readystack;
	ItemType **usedupstack;
} ItemTypeMemStack

void xcFreeMemStack(pITMS) {
	int i;
	
	for(i=0;  i<pITMS->memitems;  ++i) {
		if (pITMS->readystack[i]) {
			free(pITMS->readystack[i]);
			pITMS->readystack[i] = NULL;
		}
		if (pITMS->usedstack[i]) {
			free(pITMS->usedstack[i]);
			pITMS->usedstack[i] = NULL;
		}
	}
}

ItemTypeMemStack xcInitItemTypeMemStack(int nMBL, int preSortItems) {
	ItemTypeMemStack *pitms = malloc(sizeof(ItemTypeMemStack));

	pitms->maxbuffermemory = nMBL;
	pitms->memitems = preSortItems * 2 + 1; /*
		For each presort file, there must be two available memory items
		in order to fill up the output buffer and have more for oddments
		coming in, and one extra for the finall null pointer stopping
		point.
											 */
	pitms->readycount = 0;
	pitms->readystack = (ItemType **) calloc(memItems,sizeof(ItemType *));
	pitms->usedupcount = 0;
	pitms->usedupstack = (ItemType **) calloc(memItems,sizeof(ItemType *));
	return pitms;
}

ItemType *xcPopItemMemStack(ItemTypeMemStack *pITMS) {
}

void xcPushMemToReady(ItemTypeMemStack *pITMS, ItemType *pitemarray) {
}

void xcPushMemToUsed(ItemTypeMemStack *pITMS, ItemType *pitemarray) {
}

void xcReclaimUsed(ItemTypeMemStack *pITMS) {
}

void xcMinHeapExternalSort() {
}

void xcMinHeapInitProcessing() {
}

typedef struct  {
	int britems;
	int bwitems;
	ItemTypeMemStack *pitms;
	ItemTypeHeapNode *pheap;
} ItemTypeHeapKit;

ItemTypeHeapKit * xcInitItemTypeHeapKit(int nMBL, int psFileCount, PreSortType *pPSA) {
	ItemTypeHeapKit *pithk = malloc(sizeof(ItemTypeHeapKit));
	int halfMBL = nMBL/2;

	pithk->pitms = xcInitItemTypeMemStack(nMBL,psFileCount);
	pithk->britems = GetItemsGivenMaxBufferSize(NativeStorage,halfMBL/psFileCount);
	pithk->bwitems = GetItemsGivenMaxBufferSize(NativeStorage,halfMBL);
	pithk->pheap = (ItemTypeHeapNode *) calloc(psFileCount,sizeof(ItemTypeHeapNode));

	for(i=0; i<psFileCount; ++i) {
		xcInitSlabHeapNode(pithk->pheap+i, ppsa[i].presortitems, ppsa[i].fspec, pithk->pitms);
	
		pithk->pheap[i].itemsread =
			ReadNativeVectorSegment(ppsa[i].fp, pithk->pheap[i].pitemarray, pithk->britems);
		if ( pithk->pheap[i].itemsread < 0 ) {
			fprintf(stderr,"FATAL:  reread problem on presort file %d.\n",i);
			exit(9);
		}
		if ( pithk->pheap[i].itemsread == 0 ) {
			/* Again, the following case should not happen: */
			fprintf(stderr,"WARNING:  zero items were read from presorted file %d.\n",i);
			continue;
		}
		pithk->pheap[i].rereaditems = pithk->pheap[i].itemsread;
	}

	return pithk;
}

int xcReadFromPresortedFile(itemTypeHeapNode *pHeap, ItemTypeMemStack *pITMS, int itemElements, int endI) {
	if ( pHeap->itemsread <= pHeap->itemindex ) {
		/* push memory to used heap and read a new segment from presorted */
		xcPushMemToUsed(pITMS,pHeap->pitemarray);
		pHeap->pitemarray = xcPopItemMemStack(pITMS);
		pHeap->itemsread =
			ReadNativeVectorSegment(pHeap->fp, pHeap->pitemarray, itemElements);
		if ( pHeap->itemsread == 0 ) {
			xcPushMemToReady(pITMS,pHeap->pitemarray);
			pHeap->pitemarray = NULL;
			fclose(pHeap.fp);
			if ( pHeap.rereaditems !=  pHeap.presortitems ) {
				fprintf(stderr,"ERROR re-read count %d not equal to presort count of %d.\n",
					pHeap.rereaditems, pHeap.presortitems);
				fprintf(stderr,"Continuing processing with other data.\n");
			}
			return ( endI - 1 );
		} else {
			if ( pheap->itemsread < 0 ) {
				fprintf(stderr,"FATAL ERROR reading %s, index %d of %d \n",ppsa[i].fspec,i);
				exit(9);
			}
		}
	}
	return endI
}

bool xcRelayNextBatch(char storageType, ItemType *pob, int obi, FILE *oFp) {
}

void wpMinHeapSlabExternalSort(FILE *iFp, int nMBL, char *preSortType, char storageType, ComparisonFnPtr cmpFn, FILE *oFp) {
	int psfilecount;
	int i;

	PreSortType *ppsa = xcPreSortSubsets(iFp,nMBL,preSortType,storageType,cmpFn,&psfilecount);
	pithk = xcInitItemTypeSlabHeapKit(nMBL, psFilecount, ppsa);

	wppcMinHeapShiftDownHeapify(pithk->pheap, psfilecount, cmpFn);

	int endi = psfilecount - 1;
	int obi = 0;
	bool brv;

	while ( endi > 0 ) {
		pithk->pob[obi++] = (pheap->pitemarray + pheap->itemindex );
		/* The memory stack allows for pointer assignment, as the memory is
			then kept and reclaimed for use in the loop as output is written.
		 */
		if ( obi >= pithk->witems ) {
			/* Write To output file, because the buffer is full. */
			brv = xcRelayNextBatch(storageType, pithk->pob, obi, oFp);
			if ( ! brv ) {
				fprintf(stderr,"FATAL ERROR writing to final output.\n");
				exit(9);
			}
			xcReclaimUsed(pithk->pitms);
			obi = 0;
		}
		pithk->pheap->itemindex++;
		if ( pithk->pheap->itemsread <= pithk->pheap->itemindex ) /* should be == if true */
			endi = xcReadFromPresortedFile(pithk->pheap, pithk->pitms, pithk->britems, endi);
		wppcMinHeapShiftDown( pheap, 0, endi, cmpFn );
	}
	/* write the output buffer out the last time: */
	brv = WriteNextSegment(storageType, ob, obi);
	if ( ! brv ) {
		fprintf(stderr,"FATAL ERROR writing to final output.\n");
		exit(9);
	}
	xcFreeMemStack(pITMS);
}

void wpMinHeapCopyExternalSort(FILE *iFp, int nMBL, char *preSortType, char storageType, ComparisonFnPtr cmpFn, FILE *oFp) {
	int psfilecount;
	int i;

	PreSortType *ppsa = xcPreSortSubsets(iFp,nMBL,preSortType,storageType,cmpFn,&psfilecount);
	int britems = GetItemsGivenMaxBufferSize(NativeStorage,halfMBL/psFileCount);
	int bwitems = GetItemsGivenMaxBufferSize(NativeStorage,halfMBL);
	ItemTypeHeapNode *pheap = (ItemTypeHeapNode *) calloc(psfilecount,sizeof(ItemTypeHeapNode));

	for(i=0; i<psfilecount; ++i) {
		xcInitCopyHeapNode(pheap+i, ppsa[i].presortitems, ppsa[i].fspec, pitms);
	
		pheap[i].itemsread =
			ReadNativeVectorSegment(ppsa[i].fp, pheap[i].pitemarray, britems);
		if ( pithk->pheap[i].itemsread < 0 ) {
			fprintf(stderr,"FATAL:  reread problem on presort file %d.\n",i);
			exit(9);
		}
		if ( pithk->pheap[i].itemsread == 0 ) {
			/* Again, the following case should not happen: */
			fprintf(stderr,"WARNING:  zero items were read from presorted file %d.\n",i);
			continue;
		}
		pheap[i].rereaditems = pheap[i].itemsread;
	}

	wppcMinHeapShiftDownHeapify(pheap, psfilecount, cmpFn);

	int endi = psfilecount - 1;
	ItemType *pob = malloc(halfMBL);
	int obi = 0p

	while ( endi > 0 ) {
		CopyItem(pob + obi++, pheap->pitemarray + pheap->itemindex );
		if ( witems <= obi ) {
			/* Write To output file */
			brv = WriteNextSegment(storageType, ob, obi);
			if ( ! brv ) {
				fprintf(stderr,"FATAL ERROR writing to final output.\n");
				exit(9);
			}
			obi = 0;
		}
		pheap->itemindex++;
		if ( pheap->itemsread <= pheap->itemindex ) {
			/* push memory to used heap and read a new segment from presorted */
			pheap->itemsread =
				ReadNativeVectorSegment(pheap->fp, pheap->pitemarray, itemElements);
			if ( pheap->itemsread == 0 ) {
				free(pheap->pitemarray);
				pheap->pitemarray = NULL;
				fclose(pheap.fp);
				if ( ppsa[i].rereaditems !=  ppsa[i].presortitems ) {
					fprintf(stderr,"ERROR re-read count %d not equal to presort count of %d.\n",
						ppsa[i].rereaditems, ppsa[i].presortitems);
					fprintf(stderr,"Continuing processing with other data.\n");
				}
				endi--;
			} else {
				if ( pheap->itemsread < 0 ) {
					fprintf(stderr,"FATAL ERROR reading %s, index %d of %d \n",ppsa[i].fspec,i);
					exit(9);
				}
			}
		}
		wppcMinHeapShiftDown( pheap, 0, endi, cmpFn );
	}
	brv = WriteNextSegment(storageType, ob, obi);
	if ( ! brv ) {
		fprintf(stderr,"FATAL ERROR writing to final output.\n");
		exit(9);
	}
	for(i=0; i<psfilecount; ++i) {
		if ( ! pheap->pitemarray ) continue;
		free(pheap->pitemarray);
		pheap->pitemarray = NULL; 
	}
/* need free completion */
}

void CleanUpMergePair(FILE **fp, int setOffset, char **bFSpec) {
	int i,k;
	int r;

	for (i=0; i<3; ++i) {
		k = setOffset + i;
		r = fclose(fp[i])
		if ( r ) {
			if (i) fprintf(stderr, "FATAL:  error closing %s\n",bFSpec[k]);
			else fprintf(stderr, "FATAL:  error closing output file.\n");
			exit(9);
		} 
		if (i) {
			r = remove(bFSpec[k]);
			if ( r ) {
				fprintf(stderr, "FATAL:  error removing %s\n",bFSpec[k]);
				exit(9);
			} 
			free(bFSpec[k]);
		}
	}
}

FILE **InitializeMergePair(char *outFileSpec, char **iFSpec1, char **iFSpec2) {
	FILE *fp = calloc(3,sizeof(FILE *));
	int j1, j2;

	if ( iFSpec2 ) {
		fp[0] = File.open(outFileSpec,"w");
		fp[1] = File.open(iFSpec1,"r");
		fp[2] = File.open(iFSpec2,"r");
		for(k=0; k<3; ++k) {
			if ( fp[k] != NULL ) continue;
			fprintf(stderr, "FATAL:  error trying to open file %d in output set %d\n",k,i);
			exit(9);
		}
	} else {
		r = rename(iFSpec1,outFileSpec);
		if ( r ) {
			fprintf(stderr, "FATAL:  error renaming %s to %s\n",iFSpec1,outFileSpec);
			exit(9);
		} 
	}
	return fp;
}


bool MaintainMergePairIOBuffers(int itemIndex[], int itemCount[], FILE **fp, ItemType **pItemArray, int itemCapacity[], bool lastOut, char storageType) {
	int i;

	for (i=0;  i<3;  ++i) {
		if (i) {
			if ( itemCount[i] == 0 ) continue;
			if ( itemIndex[i] < itemCount[i] ) continue;
			itemCount[i] =
				ReadNativeVectorSegment(fp[i], pItemArray[i], itemCapacity[i]);
			if ( itemCount[i] == 0 ) {
				fclose(fp[i]);
			} else {
				if ( itemCount[i] < 0 ) {
					fprintf(stderr,"FATAL ERROR reading %d, result %d\n",i,itemCount[i]);
					exit(9);
				}
			}
			itemIndex[i] = 0;
		} else {
			if ( itemindex[0] < itemCapacity[0] )
				if ( itemCount[1] != 0 || itemCount[1] != 0 ) continue;
			if (lastOut ) {
				itemCount[0] = WriteNextSegment(storageType, pItemArray[0], itemCapacity[0]);
			} else {
				itemCount[0] = WriteNativeVectorSegment(fp[0], pItemArray[0], itemCapacity[0]);
			}
			if (itemCount[0] <= 0) {
				fprintf(stderr,"FATAL:  result %d not number specified %d.\n", writeresult, itemCount[0]);
				exit(9);
			}
			if ( itemCount[1] == 0 || itemCount[1] == 0 ) return false;
		}
	}
	return true;
}

char * wpMergeSortPairsRecursively(char *bFSpec[], int iFileCount, char *bBFspec, ItemType *pItemArray[], int itemCapacity[], char storageType, comparisonFnPtr cmpFn) {
	int cmpi;
	ItemType *pob = pItemArray[0];
	int itemcount[3];
	int itemindex[3];
	int j1,j2;
	int k;
	int r;

	int ofiles = iFileCount / 2;
	char **outFileSpecs = calloc(*outFiles,80);
	FILE **fp;
	
	for(i=0; i<ofiles; ++i) {
		sprintf(outFileSpecs[i],"%s_%d",bBFspec[i],i);
		j1 = i*2;
		j2 = j1 + 1;
		fp = InitializeMerge(outFileSpecs[i], bFSpec[j1], bFSpec[j2]);
		while ( MaintainMergePairIOBuffers(itemIndex,itemCount,fp,pItemArray,itemCapacity[1],(ofiles == 1),storageType) ) {
			cmpr = cmpFn(pItemArray[1]+itemindex[1],pItemArray[2]+itemindex[2]);
			if ( cmpr == 0 ) {
				for (cmpi=1; cmpi<=2; ++cmpi) {
					CopyItem(pob + obi++, pItemArray[cmpi]+itemindex[cmpi])
					++itemindex[cmpi]; 
				}
			} else {
				cmpi = ( cmpr < 0 ) ? 1 : 2;
				CopyItem(pob + obi++, pItemArray[cmpi]+itemindex[cmpi])
				++itemindex[cmpi]; 
			}
		}
		CleanUpMerge(fp,setOffset,bFSpec);
	}

	if ( ofiles == 1 ) return ofspecs[0];
	char *ffspec = wpMergeSortPairsRecursively(bFSpec, bFileCount, pItemArray, itemCapacity, cmpFn);
	return ffspec;
}

void wpDivideAndConquerExternalSort(FILE *iFp,int nMBL, char *preSortType, char storageType, comparisonFnPtr cmpFn) {
	int psfilecount;
	int i;

	PreSortType *ppsa = xcPreSortSubsets(iFp,nMBL,preSortType,storageType,cmpFn,&psfilecount);
	char *bFSpec[] = calloc(psfilecount,sizeof(char *));
	ItemType *pibuffer[3];
	int itemcapacity[3];
	int halfMBL = nMBL / 2;

	for(i=0; i<psfilecount; i+=2) {
		bFSpec[i] = strdup(ppsa[i].fspec);
	}

	pibuffer[0] = malloc(halfMBL);
	pibuffer[1] = malloc(halfMBL/2);
	pibuffer[2] = malloc(halfMBL/2);

	itemcapacity[0] = GetItemsGivenMaxBufferSize(NativeStorage,halfMBL);
	itemcapacity[1] = GetItemsGivenMaxBufferSize(NativeStorage,halfMBL/2);

	char *ffspec = wpMergeSortPairsRecursively(bFSpec,iFileCount,bBFspec,pItemArray,itemCapacity,storageType,cmpFn);

	for(i=0;  i<3;  ++i) free(pibuffer[i]);

	return ffspec;
}

/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890
End of externalsort.c
 */
