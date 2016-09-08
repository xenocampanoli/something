/* quicksortTests.c */

#include "sppsortTests.h"

/* The following three inlines are replicated from the quicksort.c
   source file, which is transliteraded from wikipedia pseudocode:
 */
static inline int wppc_iParent(int i) { return (i - 1) / 2; }

static inline int wppc_iLeftChild(int i)  { return 2 * i + 1; }
static inline int wppc_iRightChild(int i) { return 2 * i + 2; }

int TestCount = sizeof(TestVector) / sizeof(ItemType);

Test(quicksort_wppcQuickSort,sortAndCheck) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType tv[] = {1,2,3,4,5,6,7};
	ItemType tvr[] = {1,2,3,4,5,6,7};
	/*DumpVector(stderr,tv,7);*/
	wppcQuickSort(tv,7,cmp);
	/*DumpVector(stderr,tv,7);*/
	b = EqualVectors('0',tv,tvr,7);
	cr_assert(b);
}

Test(quicksort_wppcQuickSort,sortAndCheck2) {
	int i;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType *ptvc = CopyVector(TestVector,TestCount);
	
	wppcQuickSort(ptvc,TestCount,cmp);
	for(i=0; i<(TestCount-1); ++i) {
		cr_assert_lt(cmp(ptvc+i,ptvc+i+1),0);
	}
}

Test(quicksort_wppcQuickSort,sortAndCheckCmp1) {
	int i;
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	ItemType *ptvc = CopyVector(TestVector,TestCount);
	
	wppcQuickSort(ptvc,TestCount,cmp);
	for(i=0; i<(TestCount-1); ++i) {
		cr_assert_lt(cmp(ptvc+i,ptvc+i+1),0);
	}
}

Test(quicksort_wppcQuickSort,sortTestData0_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	FILE *fp = fopen(TestData0FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	wppcQuickSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(quicksort_wppcQuickSort,sortTestData1_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	FILE *fp = fopen(TestData1FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	wppcQuickSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(quicksort_wppcQuickSort,sortTestData2_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	FILE *fp = fopen(TestData2FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	wppcQuickSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

Test(quicksort_wppcQuickSort,sortTestData3_and_check) {
	ComparisonFnPtr cmp = GetComparisonFunction('1');
	FILE *fp = fopen(TestData3FSpec,"r");
	int i;
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	wppcQuickSort(ltv,n,cmp);
	for(i=0; i<(n-1); ++i) {
		cr_assert_leq(cmp(ltv+i,ltv+i+1),0);
	}
}

/* End of quicksortTests.c */
