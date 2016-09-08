/* itemtypeTests.c */

#include "../env.h"
#include "itemtype.h"
#include <stdio.h>
#include <criterion/criterion.h>

#ifdef __PERSON_ITEMTYPE 

#else

#define TestItemTypeArgsEqual			1
#define TestItemTypeFirstArgGreaterX	3
#define TestItemTypeFirstArgGreaterY	2

#define SingleRecordAsString	"1234"
#define SingleParsedValue		1234

#define SecondRecordAsString	"5689"
#define SecondParsedValue		5689

ItemType TestVector[] = {1207,5,42,6875309,1428,99360,360,206,1,2,609,1941,0,11,8,123456890};

#define TestData0FSpec RelSpecTestData"/inttestdata0.lst"
#define TestData1FSpec RelSpecTestData"/inttestdata1.lst"
#define TestData2FSpec RelSpecTestData"/inttestdata2.lst"
#define TestData3FSpec RelSpecTestData"/inttestdata3.lst"
#define TestData4FSpec RelSpecTestData"/inttestdata4.lst"

#endif

int TestCount = sizeof(TestVector) / sizeof(ItemType);

Test(itemtype_GetComparisonFunction,get_and_compare_cmp) {
	extern int Cmp0ItemType(const void *, const void *);
	extern int Cmp1ItemType(const void *, const void *);
	ComparisonFnPtr cmp = NULL;

	cmp = GetComparisonFunction('0');
    cr_assert(cmp == Cmp0ItemType);

	cmp = GetComparisonFunction('1');
    cr_assert(cmp == Cmp1ItemType);
}

Test(itemtype_GetComparisonFunction,cmp_args_equal) {
	char c;
	ComparisonFnPtr cmp;
	int r;
	ItemType x = TestItemTypeArgsEqual;
	ItemType y = TestItemTypeArgsEqual;

	for(c='0'; c<='1'; ++c) {
		cmp = GetComparisonFunction(c);
		r = cmp(&x,&y);
		cr_assert(r == 0);
	}
}

Test(itemtype_GetComparisonFunction,cmp_first_arg_greater) {
	char c;
	ComparisonFnPtr cmp;
	int r;
	ItemType x = TestItemTypeFirstArgGreaterX;
	ItemType y = TestItemTypeFirstArgGreaterY;
	
	for(c='0'; c<='1'; ++c) {
		cmp = GetComparisonFunction(c);
		r = cmp(&x,&y);
		cr_assert(r > 0);
	}
}

Test(itemtype_GetComparisonFunction,cmp_first_arg_less) {
	char c;
	ComparisonFnPtr cmp;
	int r;
	ItemType x = TestItemTypeArgsEqual;
	ItemType y = TestItemTypeFirstArgGreaterY;
	
	for(c='0'; c<='1'; ++c) {
		cmp = GetComparisonFunction(c);
		r = cmp(&x,&y);
		cr_assert(r < 0);
	}
}

Test(itemtype_EqualVectors,check_combinations) {
	bool b;
	char c;
	ItemType tv1[] = {1,2,3,4};
	ItemType tv2[] = {5,6,7,8};
	ItemType tv3[] = {5,6,7,9};
	ItemType tv4[] = {};

	for(c='0'; c<='1'; ++c) {
		b = EqualVectors(c, tv1, tv1, 4);
		cr_assert(b);
		b = EqualVectors(c, tv1, tv2, 4);
		cr_assert(!b);
		b = EqualVectors(c, tv2, tv3, 4);
		cr_assert(!b);
		b = EqualVectors(c, tv2, tv3, 3);
		cr_assert(b);
		b = EqualVectors(c, tv2, tv4, 0);
		cr_assert(b);
		b = EqualVectors(c, tv4, tv4, 0);
		cr_assert(b);
	}
}

Test(itemtype_CopyVector,cmp_result_array_pair) {
	bool b;
	ItemType *ltvp;
	ItemType ltv[] = {};
	
	ltvp = CopyVector(TestVector,TestCount);
	b = EqualVectors('0', TestVector, ltvp, TestCount);
	cr_assert(b);
	ltvp = CopyVector(ltv,0);
	b = EqualVectors('0', ltv, ltvp, 0);
	cr_assert(b);
}

Test(itemtype_CopyVectorData,cmp_result_array_pair) {
	bool b;
	ItemType *pnewitem = (ItemType *) calloc(TestCount,ItemTypeSize);
	ItemType ltv[] = {};
	
	CopyVectorData(pnewitem,TestVector,TestCount);
	b = EqualVectors('0', TestVector, pnewitem, TestCount);
	cr_assert(b);
	CopyVectorData(pnewitem,ltv,0);
	b = EqualVectors('0', ltv, pnewitem, 0);
	cr_assert(b);
}

Test(itemtype_ParseRecord,parse_single_record_from_string) {
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	char *string = SingleRecordAsString;
	ItemType litem0 = SingleParsedValue;
	ItemType litem1;
	int r;
	
	r = ParseRecord(string,&litem1);
	cr_assert( cmp(&litem1,&litem0) == 0 );
}

Test(itemtype_LoadVector,loads_and_sorts) {
	FILE *fp = fopen(TestData0FSpec,"r");
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	cr_assert_eq(n,25);
	cr_assert_eq(ltv[0],18037);
	cr_assert_eq(ltv[n-1],13477);
}

Test(itemtype_LoadVector,load_duplicaterecorddata) {
	FILE *fp = fopen(TestData1FSpec,"r");
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	cr_assert_eq(n,50);
	cr_assert_eq(ltv[0],18037);
	cr_assert_eq(ltv[n-1],13477);
}

Test(itemtype_LoadVector,load_quadruplicaterecorddata) {
	FILE *fp = fopen(TestData2FSpec,"r");
	int n;
	ItemType *ltv = LoadVector(fp, &n);

	cr_assert_eq(n,100);
	cr_assert_eq(ltv[0],18037);
	cr_assert_eq(ltv[n-1],13477);
}

Test(itemtype_LoadVector,loads_large_file) {
	FILE *fp = fopen(TestData3FSpec,"r");
	int n;
	ItemType *ltv = LoadVector(fp, &n);
/*
fprintf(stderr,"trace %d\n",n);
fprintf(stderr,"trace %d\n",ltv[0]);
 */
	cr_assert_eq(n,4000);
	cr_assert_eq(ltv[0],14517);
	cr_assert_eq(ltv[n-1],19187);
}

Test(itemtype_ReadVectorSegment,loads_one_segment) {
	FILE *fp = fopen(TestData4FSpec,"r");
	int n;
	ItemType *ltv = ReadVectorSegment(fp, 64, &n);
	cr_assert_gt(n,1);
	cr_assert_eq(ltv[0],29076);
}

Test(itemtype_ReadVectorSegment,loads_basic_segment) {
	FILE *fp = fopen(TestData4FSpec,"r");
	int n;
	ItemType *ltv = ReadVectorSegment(fp, 4000, &n);
fprintf(stderr,"trace %d\n",n);
	cr_assert_gt(n,1);
	cr_assert_eq(ltv[0],29076);
/*
fprintf(stderr,"trace %d\n",ltv[n-1]);
 */
	cr_assert_eq(ltv[n-1],29760);
}

Test(itemtype_ReverseCopyVector,cmp_result_opposing_elements) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	int i;
	ItemType *ltvp1, *ltvp2;
	
	ltvp1 = ReverseCopyVector(TestVector,TestCount);
	for(i=0; i<TestCount; ++i) {
		cr_assert(cmp(TestVector+i,ltvp1+TestCount-(i+1)) == 0);
	}
	ltvp2 = ReverseCopyVector(ltvp1,TestCount);
	b = EqualVectors('0', TestVector, ltvp2, TestCount);
	cr_assert(b);
}

Test(itemtype_ReverseCopyVectorData,cmp_result_opposing_elements) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	int i;
	ItemType *pnewitem1 = (ItemType *) calloc(TestCount,ItemTypeSize);
	ItemType *pnewitem2 = (ItemType *) calloc(TestCount,ItemTypeSize);
	
	ReverseCopyVectorData(pnewitem1,TestVector,TestCount);
	for(i=0; i<TestCount; ++i) {
		cr_assert(cmp(TestVector+i,pnewitem1+TestCount-(i+1)) == 0);
	}
	ReverseCopyVectorData(pnewitem2,pnewitem1,TestCount);
	b = EqualVectors('0', TestVector, pnewitem2, TestCount);
	cr_assert(b);
}

Test(itemtype_ReverseVector,cmp_result_opposing_elements) {
	bool b;
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	int i;
	ItemType *ltvp;
	
	ltvp = CopyVector(TestVector,TestCount);
	ReverseVector(ltvp,TestCount);
	for(i=0; i<TestCount; ++i) {
		cr_assert(cmp(TestVector+i,ltvp+TestCount-(i+1)) == 0);
	}
	ReverseVector(ltvp,TestCount);
	b = EqualVectors('0', TestVector, ltvp, TestCount);
	cr_assert(b);
}

Test(itemtype,compare_ReverseCopyVector_ReverseVector) {
	bool b;
	ItemType *ltvp;
	
	ltvp = ReverseCopyVector(TestVector,TestCount);
	ReverseVector(ltvp,TestCount);
	b = EqualVectors('0', TestVector, ltvp, TestCount);
	cr_assert(b);
}

Test(itemtype_SwapItem,simple_swap) {
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType litem0 = SingleParsedValue;
	ItemType litem1 = SingleParsedValue;
	ItemType litem2 = SecondParsedValue;
	ItemType litem3 = SecondParsedValue;
	SwapItem(&litem0,&litem2);
	cr_assert( cmp(&litem0,&litem3) == 0 );
	cr_assert( cmp(&litem2,&litem1) == 0 );
}
#ifdef never
#endif

Test(itemtype,WriteReadNativeVectorSegments) {
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType *pnewoutv = (ItemType *) calloc(3,ItemTypeSize);
	ItemType *pnewinv = (ItemType *) calloc(3,ItemTypeSize);
	int n;
	
	GenRandomRecord(pnewoutv);
	GenRandomRecord(pnewoutv+1);
	GenRandomRecord(pnewoutv+2);
	/*DumpVector(stderr,pnewoutv,3);*/
	FILE *ofp = fopen("teststructoutfile0","w");
	int r = WriteNativeVectorSegment(ofp, pnewoutv, 3);
	fclose(ofp);
	cr_assert_eq( r, 3 );
	FILE *ifp = fopen("teststructoutfile0","r");
	pnewinv = ReadNativeVectorSegment(ifp, 3, &n);
	fclose(ifp);
	/*fprintf(stderr,"n == %d\n",n);
	DumpVector(stderr,pnewinv,2);*/
	cr_assert_eq( n, 3 );
	cr_assert( cmp(pnewoutv,pnewinv) == 0 );
	cr_assert( cmp(pnewoutv+1,pnewinv+1) == 0 );
	cr_assert( cmp(pnewoutv+2,pnewinv+2) == 0 );
	free(pnewinv);
	free(pnewoutv);
}

Test(itemtype,WriteReadManyNativeVectorSegments) {
	int i;
	int ic=10000;
	char *fn = "teststructoutfile1";
	ComparisonFnPtr cmp = GetComparisonFunction('0');
	ItemType *pnewoutv = (ItemType *) calloc(ic,ItemTypeSize);
	ItemType *pnewinv = (ItemType *) calloc(ic,ItemTypeSize);
	int n;
	int r;
	
	FILE *ofp = fopen(fn,"w");
	for(i=0; i<ic; ++i) {
		GenRandomRecord(pnewoutv+i);
	}
	r = WriteNativeVectorSegment(ofp, pnewoutv, ic);
	fclose(ofp);
	cr_assert_eq( r, ic );
	FILE *ifp = fopen(fn,"r");
	pnewinv = ReadNativeVectorSegment(ifp, ic, &n);
	fclose(ifp);
	/*fprintf(stderr,"n == %d\n",n);
	DumpVector(stderr,pnewinv,ic);*/
	cr_assert_eq( n, ic );
	for(i=0; i<ic; ++i) {
		cr_assert( cmp(pnewoutv+i,pnewinv+i) == 0 );
	}
	free(pnewinv);
	free(pnewoutv);
}

/*
End of itemtypeTests.c
 */
