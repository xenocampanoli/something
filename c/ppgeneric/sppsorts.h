/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890
	sppsorts.h - Something C "Preprocessor Generic" sorts Header */

#include "itemtype.h"
#include <stdio.h>

extern void clrspcOriginalMaxHeapify(ItemType itemArray[], int itemCount, int rootIndex, ComparisonFnPtr cmpFn);
extern void clrspcXCMaxHeapify(ItemType itemArray[], int itemCount, int rootIndex, ComparisonFnPtr cmpFn);
extern void clrspcBuildMaxHeap(ItemType itemArray[],int itemCount, ComparisonFnPtr cmpFn);
extern void clrspcHeapSort(ItemType itemArray[],int itemCount, ComparisonFnPtr cmpFn);

extern void hps2MergeSort(ItemType itemArray[], int itemCount, ComparisonFnPtr cmpFn);
extern void hps2MergeSortArray(ItemType *pItemArray, ItemType *pResult, int iStart, int iEnd, ComparisonFnPtr cmpFn);

extern void wpBottomUpMergeSort(ItemType *pItemArray, int itemCount, ComparisonFnPtr cmpFn);

extern void wppcInsertionSort(ItemType itemArray[],int itemCount, ComparisonFnPtr cmpFn);

extern void wppcMinHeapMultiMergeExternalSort(FILE *iFp, int nMBL, char *preSortType, char storageType, ComparisonFnPtr cmpFn, FILE *oFp);

extern void wppcMinHeapShiftDown(ItemIndexType itemArray[], int startIndex, int endIndex, ComparisonFnPtr cmpFn);
extern void wppcMinHeapShiftDownHeapify(ItemIndexType itemArray[], int itemCount, ComparisonFnPtr cmpFn);
extern void wppcPMerge(ItemType *pItemHeap[], int pItemHeapCount[],  int arrayCount, ComparisonFnPtr cmpFn);
extern void wppcPreSortBinaryMergeExternalSort();

extern void wppcShiftDown(ItemType itemArray[], int startIndex, int endIndex,ComparisonFnPtr cmpFn);
extern void wppcShiftDownHeapify(ItemType itemArray[], int itemCount, ComparisonFnPtr cmpFn);
extern void wppcShiftDownHeapSort(ItemType itemArray[], int itemCount, ComparisonFnPtr cmpFn);

extern void wppcShiftUp(ItemType itemArray[], int startIndex, int endIndex, ComparisonFnPtr cmpFn);
extern void wppcShiftUpHeapify(ItemType itemArray[], int itemCount, ComparisonFnPtr cmpFn);
extern void wppcShiftUpHeapSort(ItemType itemArray[], int itemCount, ComparisonFnPtr cmpFn);

extern void xcMerge(ItemType *pItemArray0, int itemCount0, ItemType *pItemArray1,int itemCount1, ItemType *pItemArray2, int itemCount2, ComparisonFnPtr cmpFn);
extern void xcTopDownMergeSortRecursion(ItemType *pItemArray, ItemType *pBuffer, int itemCount, ComparisonFnPtr cmpFn);
extern void xcTopDownMergeSort(ItemType itemArray[], int itemCount, ComparisonFnPtr cmpFn);

/*
End of sppsorts.h
 */
