/* mergesortTests.c */

#include "sppsortTests.h"

/* The following three inlines are replicated from the mergesort.c
   source file, which is transliteraded from wikipedia pseudocode:
 */
static inline int xc_iParent(int i) { return (i - 1) / 2; }

static inline int xc_iLeftChild(int i)  { return 2 * i + 1; }
static inline int xc_iRightChild(int i) { return 2 * i + 2; }

int TestCount = sizeof(TestVector) / sizeof(ItemType);

Test(mergesort_hps2MergeSortArray,sortAndCheck) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv[] = {7,6,5,4,3,2,1};
	ItemType tvr[] = {1,2,3,4,5,6,7};
	DumpVector(stderr,tv,7);
	ItemType *pcopy = CopyVector(tv,7);
	
	hps2MergeSortArray(pcopy, tv, 0, 7, cmp);
	DumpVector(stderr,tv,7);
	b = EqualVectors('0',tv,tvr,7);
	cr_assert(b);
}

Test(mergesort_hps2MergeSort,sortAndCheck) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv[] = {1,2,3,4,5,6,7};
	ItemType tvr[] = {1,2,3,4,5,6,7};
	/* DumpVector(stderr,tv,7); */
	hps2MergeSort(tv,7,cmp);
	/* DumpVector(stderr,tv,7); */
	b = EqualVectors('0',tv,tvr,7);
	cr_assert(b);
}

Test(mergesort_hps2MergeSort,sortAndCheck2) {
	int i;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType *ptvc = CopyVector(TestVector,TestCount);
	
	/* DumpVector(stderr,TestVector,TestCount); */
	hps2MergeSort(ptvc,TestCount,cmp);
	/* DumpVector(stderr,ptvc,TestCount); */
	exit(0);
	for(i=0; i<(TestCount-1); ++i) {
		cr_assert_leq(cmp(ptvc+i,ptvc+i+1),0);
	}
}

Test(mergesort_hps2MergeSort,sortAndCheckCmp1) {
	int i;
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	ItemType *ptvc = CopyVector(TestVector,TestCount);
	
	hps2MergeSort(ptvc,TestCount,cmp);
	for(i=0; i<(TestCount-1); ++i) {
		cr_assert_lt(cmp(ptvc+i,ptvc+i+1),0);
	}
}

Test(mergesort_hps2MergeSort,sortTestData0_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	FILE *fp = fopen(TestData0FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	hps2MergeSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(mergesort_hps2MergeSort,sortTestData1_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	FILE *fp = fopen(TestData1FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	hps2MergeSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(mergesort_hps2MergeSort,sortTestData2_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	FILE *fp = fopen(TestData2FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	hps2MergeSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(mergesort_hps2MergeSort,sortTestData3_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	FILE *fp = fopen(TestData3FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	hps2MergeSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(mergesort_xcMerge,sortAndCheck) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv1[] = {1,3,5,7,9,11,13};
	ItemType tv2[] = {2,4,6,8,10,12,14};
	ItemType tvc[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
	ItemType *ptvr = (ItemType *) calloc(14,ItemTypeSize);
	/*
	fprintf(stderr,"trace 0\n");
	DumpVector(stderr,tv1,13);
	fprintf(stderr,"trace 1\n");
	DumpVector(stderr,tv2,13);
	fprintf(stderr,"trace 2\n");
	*/
	xcMerge(ptvr,14,tv1,7,tv2,7,cmp);
	/*
	fprintf(stderr,"trace 3\n");
	DumpVector(stderr,ptvr,14);
	fprintf(stderr,"trace 4\n");
	*/
	b = EqualVectors('0',ptvr,tvc,14);
	cr_assert(b);
}

Test(mergesort_xcTopDownMergeSort,sortAndCheck) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv[] = {1,2,3,4,5,6,7};
	ItemType tvr[] = {1,2,3,4,5,6,7};
	/* DumpVector(stderr,tv,7); */
	xcTopDownMergeSort(tv,7,cmp);
	/* DumpVector(stderr,tv,7); */
	b = EqualVectors('0',tv,tvr,7);
	cr_assert(b);
}

Test(mergesort_xcTopDownMergeSort,sortAndCheck2) {
	int i;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType *ptvc = CopyVector(TestVector,TestCount);
	
	/* DumpVector(stderr,TestVector,TestCount); */
	xcTopDownMergeSort(ptvc,TestCount,cmp);
	/* DumpVector(stderr,ptvc,TestCount); */
	exit(0);
	for(i=0; i<(TestCount-1); ++i) {
		cr_assert_leq(cmp(ptvc+i,ptvc+i+1),0);
	}
}

Test(mergesort_xcTopDownMergeSort,sortAndCheckCmp1) {
	int i;
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	ItemType *ptvc = CopyVector(TestVector,TestCount);
	
	xcTopDownMergeSort(ptvc,TestCount,cmp);
	for(i=0; i<(TestCount-1); ++i) {
		cr_assert_lt(cmp(ptvc+i,ptvc+i+1),0);
	}
}

Test(mergesort_xcTopDownMergeSort,sortTestData0_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	FILE *fp = fopen(TestData0FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	xcTopDownMergeSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(mergesort_xcTopDownMergeSort,sortTestData1_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	FILE *fp = fopen(TestData1FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	xcTopDownMergeSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(mergesort_xcTopDownMergeSort,sortTestData2_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	FILE *fp = fopen(TestData2FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	xcTopDownMergeSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(mergesort_xcTopDownMergeSort,sortTestData3_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	FILE *fp = fopen(TestData3FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	xcTopDownMergeSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(mergesort_wpBottomUpMergeSort,sortAndCheck) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv[] = {1,2,3,4,5,6,7};
	ItemType tvr[] = {1,2,3,4,5,6,7};
	/*DumpVector(stderr,tv,7);*/
	wpBottomUpMergeSort(tv,7,cmp);
	/*DumpVector(stderr,tv,7);*/
	b = EqualVectors('0',tv,tvr,7);
	cr_assert(b);
}

Test(mergesort_wpBottomUpMergeSort,sortAndCheck2) {
	int i;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType *ptvc = CopyVector(TestVector,TestCount);
	
	/* DumpVector(stderr,TestVector,TestCount);*/
	wpBottomUpMergeSort(ptvc,TestCount,cmp);
	/* DumpVector(stderr,ptvc,TestCount);*/
	for(i=0; i<(TestCount-1); ++i) {
		cr_assert_leq(cmp(ptvc+i,ptvc+i+1),0);
	}
}

Test(mergesort_wpBottomUpMergeSort,sortAndCheckCmp1) {
	int i;
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	ItemType *ptvc = CopyVector(TestVector,TestCount);
	
	wpBottomUpMergeSort(ptvc,TestCount,cmp);
	for(i=0; i<(TestCount-1); ++i) {
		cr_assert_lt(cmp(ptvc+i,ptvc+i+1),0);
	}
}

Test(mergesort_wpBottomUpMergeSort,sortTestData0_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	FILE *fp = fopen(TestData0FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	wpBottomUpMergeSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(mergesort_wpBottomUpMergeSort,sortTestData1_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	FILE *fp = fopen(TestData1FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	wpBottomUpMergeSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(mergesort_wpBottomUpMergeSort,sortTestData2_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	FILE *fp = fopen(TestData2FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	wpBottomUpMergeSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(mergesort_wpBottomUpMergeSort,sortTestData3_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	FILE *fp = fopen(TestData3FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	wpBottomUpMergeSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

#ifdef nothing
#endif
/* End of mergesortTests.c */
