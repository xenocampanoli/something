/* heapsortTests.c */

#include "sppsortTests.h"

/* The following three inlines are replicated from the heapsort.c
   source file, which is transliteraded from wikipedia pseudocode:
 */
static inline int wppc_iParent(int i) { return (i - 1) / 2; }

static inline int wppc_iLeftChild(int i)  { return 2 * i + 1; }
static inline int wppc_iRightChild(int i) { return 2 * i + 2; }

int TestCount = sizeof(TestVector) / sizeof(ItemType);

Test(heapsort_clrspcXCMaxHeapify,siftDownAndCheck3Elements) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv[] = {1,2,3};
	ItemType tvr[] = {3,2,1};
	clrspcXCMaxHeapify(tv,3,0,cmp);
	b = EqualVectors('0',tv,tvr,3);
	cr_assert(b);
}

Test(heapsort_clrspcXCMaxHeapify,siftDownAndCheck7Elements) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv1[] = {1,2,3,4,5,6,7};
	ItemType tv2[] = {1,2,3,4,5,6,7};
	ItemType tvr1[] = {1,2,7,4,5,6,3};
	ItemType tvr2[] = {1,5,3,4,2,6,7};
	/*clrspcXCMaxHeapify(tv1,7,0,cmp);*/
	clrspcOriginalMaxHeapify(tv1,7,2,cmp);
	/*DumpVector(stderr,tv1,7);*/
	b = EqualVectors('0',tv1,tvr1,7);
	cr_assert(b);
	clrspcXCMaxHeapify(tv2,7,1,cmp);
	/*DumpVector(stderr,tv2,7);*/
	b = EqualVectors('0',tv2,tvr2,7);
	cr_assert(b);
}

Test(heapsort_clrspcBuildMaxHeap,siftDownAndCheck7Elements) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv[] = {1,2,3,4,5,6,7};
	ItemType tvr[] = {7,5,6,4,2,1,3};
	/*DumpVector(stderr,tv,7);*/
	clrspcBuildMaxHeap(tv,7,cmp);
	/*DumpVector(stderr,tv,7);*/
	b = EqualVectors('0',tv,tvr,7);
	cr_assert(b);
}

Test(heapsort_clrspcHeapSort,sortAndCheck) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv[] = {1,2,3,4,5,6,7};
	ItemType tvr[] = {1,2,3,4,5,6,7};
	/*DumpVector(stderr,tv,7);*/
	clrspcHeapSort(tv,7,cmp);
	/*DumpVector(stderr,tv,7);*/
	b = EqualVectors('0',tv,tvr,7);
	cr_assert(b);
}

Test(heapsort_clrspcHeapSort,sortAndCheck2) {
	int i;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType *ptvc = CopyVector(TestVector,TestCount);
	
	clrspcHeapSort(ptvc,TestCount,cmp);
	for(i=0; i<(TestCount-1); ++i) {
		cr_assert_lt(cmp(ptvc+i,ptvc+i+1),0);
	}
}

Test(heapsort_clrspcHeapSort,sortAndCheckCmp1) {
	int i;
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	ItemType *ptvc = CopyVector(TestVector,TestCount);
	
	clrspcHeapSort(ptvc,TestCount,cmp);
	for(i=0; i<(TestCount-1); ++i) {
		cr_assert_lt(cmp(ptvc+i,ptvc+i+1),0);
	}
}

Test(heapsort_clrspcHeapSort,sortTestData0_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	FILE *fp = fopen(TestData0FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	clrspcHeapSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(heapsort_clrspcHeapSort,sortTestData1_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	FILE *fp = fopen(TestData1FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	clrspcHeapSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(heapsort_clrspcHeapSort,sortTestData2_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	FILE *fp = fopen(TestData2FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	clrspcHeapSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(heapsort_clrspcHeapSort,sortTestData3_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	FILE *fp = fopen(TestData3FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	clrspcHeapSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(heapsort_wppcShiftDown,siftDownAndCheck3Elements) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv[] = {1,2,3};
	ItemType tvr[] = {3,2,1};
	wppcShiftDown(tv,0,2,cmp);
	b = EqualVectors('0',tv,tvr,3);
	cr_assert(b);
}

Test(heapsort_wppcShiftDown,siftDownAndCheck7Elements) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv1[] = {1,2,3,4,5,6,7};
	ItemType tv2[] = {1,2,3,4,5,6,7};
	/* Results should be greater of the two children is swapped up. */
	ItemType tvr1[] = {1,2,7,4,5,6,3};
	ItemType tvr2[] = {1,5,3,4,2,6,7};
	/*DumpVector(stderr,tv,7);*/
	wppcShiftDown(tv1,2,6,cmp);
	/*DumpVector(stderr,tv,7);*/
	b = EqualVectors('0',tv1,tvr1,7);
	cr_assert(b);
	wppcShiftDown(tv2,1,6,cmp);
	b = EqualVectors('0',tv2,tvr2,7);
	cr_assert(b);
}

Test(heapsort_wppcShiftDown,siftDownAndCheck7ElementsLimits) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv1[] = {1,2,3,4,5,6,7};
	ItemType tv2[] = {1,2,3,4,5,6,7};
	/* Results should be greater of the two children is swapped up. */
	ItemType tvr1[] = {3,2,7,4,5,6,1};
	ItemType tvr2[] = {1,2,3,4,5,6,7};
	wppcShiftDown(tv1,0,6,cmp);
	b = EqualVectors('0',tv1,tvr1,7);
	cr_assert(b);
	/*DumpVector(stderr,tv,7);*/
	wppcShiftDown(tv2,3,6,cmp);
	/*DumpVector(stderr,tv2,7);*/
	b = EqualVectors('0',tv2,tvr2,7);
	cr_assert(b);
	wppcShiftDown(tv2,4,6,cmp);
	/*DumpVector(stderr,tv2,7);*/
	b = EqualVectors('0',tv2,tvr2,7);
	cr_assert(b);
	wppcShiftDown(tv2,4,6,cmp);
	/*DumpVector(stderr,tv2,7);*/
	b = EqualVectors('0',tv2,tvr2,7);
	cr_assert(b);
	wppcShiftDown(tv2,6,6,cmp);
	/*DumpVector(stderr,tv2,7);*/
	b = EqualVectors('0',tv2,tvr2,7);
	cr_assert(b);
}

Test(heapsort_wppcShiftDownHeapify,siftDownHeapifyAndCheck7Elements) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv[] = {1,2,3,4,5,6,7};
	ItemType tvr[] = {7,5,6,4,2,1,3};
	/*DumpVector(stderr,tv,7);*/
	wppcShiftDownHeapify(tv,7,cmp);
	/*DumpVector(stderr,tv,7);*/
	b = EqualVectors('0',tv,tvr,7);
	cr_assert(b);
}

Test(heapsort_wppcShiftDownHeapify,checkTestVectorMax) {
	int i,j;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType *ptvc = CopyVector(TestVector,TestCount);
	
	/*
	fprintf(stderr,"Dumping Test Vector:  \n");
	DumpVector(stderr,TestVector,TestCount);
	fprintf(stderr,"Dumping Test Vector copy:  \n");
	DumpVector(stderr,ptvc,TestCount);
	 */
	wppcShiftDownHeapify(ptvc,TestCount,cmp);
	/*
	fprintf(stderr,"Dumping heapified Vector:  \n");
	DumpVector(stderr,ptvc,TestCount);
	 */
	for(i=1; i<TestCount; ++i) {
	/*	fprintf(stderr,"Root is %d, Element %d is %d\n",(int)*ptvc,i,(int)*(ptvc+i)); */
		cr_assert_geq(cmp(ptvc,ptvc+i),0);
	}
	for(i=1; i<TestCount; ++i) {
		j = wppc_iParent(i);
		cr_assert_geq(cmp(ptvc+j,ptvc+i),0);
	}
	for(i=0; i<(TestCount-1); ++i) {
		j = wppc_iLeftChild(i);
		if (j >= TestCount) break; /* Indicating you are in the leaves. */
		cr_assert_geq(cmp(ptvc+i,ptvc+j),0);
		j = wppc_iRightChild(i);
		cr_assert_geq(cmp(ptvc+i,ptvc+j),0);
	}
}

Test(heapsort_wppcShiftDownHeapSort,sortAndCheck) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv[] = {1,2,3,4,5,6,7};
	ItemType tvr[] = {1,2,3,4,5,6,7};
	/*DumpVector(stderr,tv,7);*/
	wppcShiftDownHeapSort(tv,7,cmp);
	/*DumpVector(stderr,tv,7);*/
	b = EqualVectors('0',tv,tvr,7);
	cr_assert(b);
}

Test(heapsort_wppcShiftDownHeapSort,sortAndCheck2) {
	int i;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType *ptvc = CopyVector(TestVector,TestCount);
	
	wppcShiftDownHeapSort(ptvc,TestCount,cmp);
	for(i=0; i<(TestCount-1); ++i) {
		cr_assert_lt(cmp(ptvc+i,ptvc+i+1),0);
	}
}

Test(heapsort_wppcShiftDownHeapSort,sortAndCheckCmp1) {
	int i;
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	ItemType *ptvc = CopyVector(TestVector,TestCount);
	
	wppcShiftDownHeapSort(ptvc,TestCount,cmp);
	for(i=0; i<(TestCount-1); ++i) {
		cr_assert_lt(cmp(ptvc+i,ptvc+i+1),0);
	}
}

Test(heapsort_wppcShiftDownHeapSort,sortTestData0_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	FILE *fp = fopen(TestData0FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	wppcShiftDownHeapSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(heapsort_wppcShiftDownHeapSort,sortTestData1_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	FILE *fp = fopen(TestData1FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	wppcShiftDownHeapSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(heapsort_wppcShiftDownHeapSort,sortTestData2_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	FILE *fp = fopen(TestData2FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	wppcShiftDownHeapSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(heapsort_wppcShiftDownHeapSort,sortTestData3_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	FILE *fp = fopen(TestData3FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	wppcShiftDownHeapSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(heapsort_wppcShiftUP,siftUPAndCheck3Elements) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv[] = {1,2,3};
	ItemType tvr[] = {3,2,1};
	wppcShiftUp(tv,0,2,cmp);
	b = EqualVectors('0',tv,tvr,3);
	cr_assert(b);
}

Test(heapsort_wppcShiftUpHeapify,siftUpHeapifyAndCheck7Elements) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv[] = {1,2,3,4,5,6,7};
	/*ItemType tvr[] = {7,5,6,4,2,1,3};*/
	ItemType tvr[] = {7,4,6,1,3,2,5};
	/*DumpVector(stderr,tv,7);*/
	wppcShiftUpHeapify(tv,7,cmp);
	/*DumpVector(stderr,tv,7);*/
	b = EqualVectors('0',tv,tvr,7);
	cr_assert(b);
}

Test(heapsort_wppcShiftUpHeapSort,sortAndCheck) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv[] = {1,2,3,4,5,6,7};
	ItemType tvr[] = {1,2,3,4,5,6,7};
	/*DumpVector(stderr,tv,7);*/
	wppcShiftUpHeapSort(tv,7,cmp);
	/*DumpVector(stderr,tv,7);*/
	b = EqualVectors('0',tv,tvr,7);
	cr_assert(b);
}

Test(heapsort_wppcShiftUpHeapSort,sortAndCheck2) {
	int i;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType *ptvc = CopyVector(TestVector,TestCount);
	
	wppcShiftUpHeapSort(ptvc,TestCount,cmp);
	for(i=0; i<(TestCount-1); ++i) {
		cr_assert_lt(cmp(ptvc+i,ptvc+i+1),0);
	}
}

Test(heapsort_wppcShiftUpHeapSort,sortAndCheckCmp1) {
	int i;
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	ItemType *ptvc = CopyVector(TestVector,TestCount);
	
	wppcShiftUpHeapSort(ptvc,TestCount,cmp);
	for(i=0; i<(TestCount-1); ++i) {
		cr_assert_lt(cmp(ptvc+i,ptvc+i+1),0);
	}
}

Test(heapsort_wppcShiftUpHeapSort,sortTestData0_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	FILE *fp = fopen(TestData0FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	wppcShiftUpHeapSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(heapsort_wppcShiftUpHeapSort,sortTestData1_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	FILE *fp = fopen(TestData1FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	wppcShiftUpHeapSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(heapsort_wppcShiftUpHeapSort,sortTestData2_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	FILE *fp = fopen(TestData2FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	wppcShiftUpHeapSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(heapsort_wppcShiftUpHeapSort,sortTestData3_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	FILE *fp = fopen(TestData3FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	wppcShiftUpHeapSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

/* I should probably add heap search functions in heapsort.c to complete the suite, and
    these tests.  For now, do it later.
 */

/*
End of heapsortTests.c
 */
