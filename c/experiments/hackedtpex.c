/* From:
http://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
 */
#include <stdio.h>
#include <stdlib.h>

typedef int ItemType;

ItemType DefaultVector[] = (ItemType []) {1958,5101,6530250,9352619,4512,57,98422,5516,47,46,19961219,1957,0,9,1023,45};
int DefaultCount = sizeof(DefaultVector) / sizeof(int);

int LessThanValue = -1;
int GreaterThanValue = 1;

int Cmp0ItemType(const void *pItemType1, const void *pItemType2) {
	
	const ItemType *pit1 = (const ItemType *) pItemType1;
	const ItemType *pit2 = (const ItemType *) pItemType2;

	if ( *pit1 < *pit2 ) {
		return LessThanValue;
	}
	if ( *pit1 > *pit2 ) {
		return GreaterThanValue;
	}
	return 0;
}

int values[] = { 88, 56, 100, 2, 25 };

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int main()
{
	int n;

	printf("Before sorting the list is: \n");
	for( n = 0 ; n < 5; n++ ) 
	{
		printf("%d ", values[n]);
	}
	puts("\n");

	qsort(values, 5, sizeof(int), cmpfunc);

	printf("\nAfter sorting the list is: \n");
	for( n = 0 ; n < 5; n++ ) 
	{   
		printf("%d ", values[n]);
	}
	puts("\n");

	qsort(DefaultVector, DefaultCount, sizeof(ItemType), Cmp0ItemType);

	printf("\nAfter sorting the DefaultVector is: \n");

	for( n = 0 ; n < DefaultCount; n++ ) 
	{   
		printf("%d ", DefaultVector[n]);
	}
	puts("\n");

	return(0);
}
