/* externalsortTests.c */

#include "sppsortTests.h"

/* The following three inlines are replicated from the externalsort.c
   source file, which is transliteraded from wikipedia pseudocode:
 */
static inline int wppc_iParent(int i) { return (i - 1) / 2; }

static inline int wppc_iLeftChild(int i)  { return 2 * i + 1; }
static inline int wppc_iRightChild(int i) { return 2 * i + 2; }

int TestCount = sizeof(TestVector) / sizeof(ItemType);

Test(externalsort_wppcMinHeapShiftDown,siftDownAndCheck3Elements) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv[] = {1,2,3};
	ItemType tvr[] = {1,2,3};
	wppcMinHeapShiftDown(tv,0,2,cmp);
	b = EqualVectors('0',tv,tvr,3);
	cr_assert(b);
}

Test(externalsort_wppcMinHeapShiftDown,siftDownAndCheck7Elements) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv1[] = {1,2,3,4,5,6,7};
	ItemType tv2[] = {1,2,3,4,5,6,7};
	ItemType tvr1[] = {1,2,3,4,5,6,7};
	ItemType tvr2[] = {1,2,3,4,5,6,7};
	/* Results should be greater of the two children is swapped up. */
	/* DumpVector(stderr,tv1,7); */
	wppcMinHeapShiftDown(tv1,2,6,cmp);
	/* DumpVector(stderr,tv1,7); */
	b = EqualVectors('0',tv1,tvr1,7);
	cr_assert(b);
	/* DumpVector(stderr,tv2,7); */
	wppcMinHeapShiftDown(tv2,1,6,cmp);
	/* DumpVector(stderr,tv2,7); */
	b = EqualVectors('0',tv2,tvr2,7);
	cr_assert(b);
}

Test(externalsort_wppcMinHeapShiftDown,siftDownAndCheck7ElementsLimits) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv1[] = {1,2,3,4,5,6,7};
	ItemType tv2[] = {1,2,3,4,5,6,7};
	/* Results should be greater of the two children is swapped up. */
	ItemType tvr1[] = {1,2,3,4,5,6,7};
	ItemType tvr2[] = {1,2,3,4,5,6,7};
	wppcMinHeapShiftDown(tv1,0,6,cmp);
	b = EqualVectors('0',tv1,tvr1,7);
	cr_assert(b);
	/*DumpVector(stderr,tv,7);*/
	wppcMinHeapShiftDown(tv2,3,6,cmp);
	/*DumpVector(stderr,tv2,7);*/
	b = EqualVectors('0',tv2,tvr2,7);
	cr_assert(b);
	wppcMinHeapShiftDown(tv2,4,6,cmp);
	/*DumpVector(stderr,tv2,7);*/
	b = EqualVectors('0',tv2,tvr2,7);
	cr_assert(b);
	wppcMinHeapShiftDown(tv2,4,6,cmp);
	/*DumpVector(stderr,tv2,7);*/
	b = EqualVectors('0',tv2,tvr2,7);
	cr_assert(b);
	wppcMinHeapShiftDown(tv2,6,6,cmp);
	/*DumpVector(stderr,tv2,7);*/
	b = EqualVectors('0',tv2,tvr2,7);
	cr_assert(b);
}

Test(externalsort_wppcShiftDownHeapify,siftDownHeapifyAndCheck7Elements) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv[] = {1,2,3,4,5,6,7};
	ItemType tvr[] = {1,2,3,4,5,6,7};
	DumpVector(stderr,tv,7);
	wppcMinHeapShiftDownHeapify(tv,7,cmp);
	DumpVector(stderr,tv,7);
	b = EqualVectors('0',tv,tvr,7);
	cr_assert(b);
}

Test(externalsort_wppcShiftDownHeapify,checkTestVectorMax) {
	int i,j;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType *ptvc = CopyVector(TestVector,TestCount);
	
	fprintf(stderr,"Dumping Test Vector:  \n");
	DumpVector(stderr,TestVector,TestCount);
	fprintf(stderr,"Dumping Test Vector copy:  \n");
	DumpVector(stderr,ptvc,TestCount);
	/*
	 */
	wppcMinHeapShiftDownHeapify(ptvc,TestCount,cmp);
	fprintf(stderr,"Dumping heapified Vector:  \n");
	DumpVector(stderr,ptvc,TestCount);
	/*
	 */
	for(i=1; i<TestCount; ++i) {
		fprintf(stderr,"Root is %d, Element %d is %d\n",(int)*ptvc,i,(int)*(ptvc+i));
		cr_assert_leq(cmp(ptvc,ptvc+i),0);
	}
	for(i=1; i<TestCount; ++i) {
		j = wppc_iParent(i);
		cr_assert_leq(cmp(ptvc+j,ptvc+i),0);
	}
	for(i=0; i<(TestCount-1); ++i) {
		j = wppc_iLeftChild(i);
		if (j >= TestCount) break; /* Indicating you are in the leaves. */
		cr_assert_leq(cmp(ptvc+i,ptvc+j),0);
		j = wppc_iRightChild(i);
		if ( j != TestCount ) 
			cr_assert_leq(cmp(ptvc+i,ptvc+j),0);
	}
#ifdef nevereverever
#endif
}

/*
End of externalsortTests.c
 */
