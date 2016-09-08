/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890

	itemtype.c - Items are a compile-time definition for elements to be sorted,
	searched, or otherwise handled in any of the various algorithms in this
	Preprocessor Generics (ppgeneric) suite.

	This has gotten so big, I am now dividing it into three sections:

	1.	Data Definitions and Manipulations

	2.	I/O Facilities

 */

/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890
    Data Definitions and Manipulations:

		a.  PP Inclusions and Internals
		b.	ItemType pre-prosessor conditioned code.
		c.	Preprocessor independent Interfaces.
 */

/*	BEGIN:  PP Inclusions and Internals */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h> 

#include "itemtype.h"

int SortAscending = true;
int LessThanValue = -1;
int GreaterThanValue = 1;

static inline int _genRandString(char *charSet, char *outString, int fieldSize) {
	int d = strlen(charSet) * RAND_MAX;
	size_t ri;
	char *b = outString;

	while(fieldSize--) {
        ri = (double) rand() / d;
        *b++ = charSet[ri];
    }
	*b = '\0';
}

/*	END:  PP Inclusions and Internals */

/*	BEGIN:  ItemType pre-prosessor conditioned code. */

#ifdef __PERSON_ITEMTYPE 

ItemType * GetDefaultTestVector() {
}

int Cmp0ItemType(const void *pItemArray1, const void *pItemArray2) {
	
	const ItemType *pit1 = (const ItemType *) pItemArray1;
	const ItemType *pit2 = (const ItemType *) pItemArray2;

	if ( memcmp(pit1->LastName,pit2->LastName) < 0 ) {
		return LessThanValue;
	}
	if ( memcmp(pit1->LastName,pit2->LastName) > 0 ) {
		return GreaterThanValue;
	}
	if ( memcmp(pit1->FirstName,pit2->FirstName) < 0 ) {
		return LessThanValue;
	}
	if ( memcmp(pit1->FirstName,pit2->FirstName) > 0 ) {
		return GreaterThanValue;
	}
	return 0
}

int Cmp1ItemType(const void *pItemArray1, const void *pItemArray2) {
	
	const ItemType *pit1 = (const ItemType *) pItemArray1;
	const ItemType *pit2 = (const ItemType *) pItemArray2;

	const int cmp0result = Cmp0ItemType(pItemArray1,pItemArray2);
	if (cmp0result) return cmp0result;

	if ( pit1->Age < pit2->Age )
		return LessThanValue;
	if ( pit1->Age > pit2->Age )
		return GreaterThanValue;
	if ( pit1->RedCellType < pit2->RedCellType )
		return LessThanValue;
	if ( pit1->RedCellType > pit2->RedCellType )
		return GreaterThanValue;
	if ( pit1->RhD < pit2->RhD )
		return LessThanValue;
	if ( pit1->RhD > pit2->RhD )
		return GreaterThanValue;
	if ( pit1->IQ < pit2->IQ )
		return LessThanValue;
	if ( pit1->IQ > pit2->IQ )
		return GreaterThanValue;
	return 0
}

/* Copies in C go from right to left, like assignments, so doing that here: */
int CopyItem(ItemType *pItem1, ItemType *pItem2) {
	strcpy(pItem1->LastName,pItem2->LastName);
	strcpy(pItem1->FirstName,pItem2->FirstName);
	strcpy(pItem1->LifeStory,pItem2->LifeStory);
	pItem1->Age = pItem2->Age;
	pItem1->IQ = pItem2->IQ;
	pItem1->RhD = pItem2->RhD;
	pItem1->RedCellType = pItem2->RedCellType;
}

int DumpRecord(FILE *ofp, ItemType *pItem) {
	fprintf(ofp,"%s,%s,%s,%d,%d",pItem->LastName,pItem->FirstName,pItem->LifeStory,pItem->Age,pItem->IQ,
	switch(pItem->RedCellType) {
		case A:
			fprintf(ofp,"A,");
			break;
		case AB:
			fprintf(ofp,"AB,");
			break;
		case B:
			fprintf(ofp,"B,");
			break;
		default:
			fprintf(ofp,"O,");
			break;
	}
	fprintf(ofp,"%s\n",pItem->RhD ? "positive" : "negative")
);
}

int GenRandomRecord(ItemType *itemRecord) {

	_genRandString(NameChars,itemRecord->FirstName,FirstNameLength);
	_genRandString(NameChars,itemRecord->LastName,LastNameLength);
	_genRandString(StoryChars,itemRecord->LifeStory,LifeStoryLength);
	itemRecord->Age = ( (double) rand() / RAND_MAX ) * 100;
	itemRecord->IQ = ( (double) rand() / RAND_MAX ) * 200;
	switch ( (double) rand() / RAND_MAX ) * 4 ) {
		case 0:		itemRecord->RedCellType = A; break;
		case 1:		itemRecord->RedCellType = AB; break;
		case 2:		itemRecord->RedCellType = B; break;
		default:	itemRecord->RedCellType = O;
	}
	itemRecord->RhD = ( ( (double) rand() / RAND_MAX ) > 0.5 );

	return 0;
}

ItemType * GetDefaultTestVector() {
	static ItemType defaultvector[] = calloc(3,ItemTypeSize);

	strcpy(defaultvector[0].FirstName,"Xeno");
	strcpy(defaultvector[0].LastName,"Campanoli");
	strcpy(defaultvector[0].LifeStory,"In the initial years of the present human induced climate change, I was born to a very nice woman, on the shortest day of 1958.");
	strcpy(defaultvector[0].Age = 57;
	strcpy(defaultvector[0].IQ = 121;
	strcpy(defaultvector[0].RedCellType = O;
	strcpy(defaultvector[0].RhD = false;

	strcpy(defaultvector[1].FirstName,"Barak");
	strcpy(defaultvector[1].LastName,"Obama");
	strcpy(defaultvector[1].LifeStory,"Some guy in Washington.");
	strcpy(defaultvector[1].Age = 57;
	strcpy(defaultvector[1].IQ = 121;
	strcpy(defaultvector[1].RedCellType = O;
	strcpy(defaultvector[1].RhD = false;

	strcpy(defaultvector[2].FirstName,"Franny");
	strcpy(defaultvector[2].LastName,"Fixion");
	strcpy(defaultvector[2].LifeStory,"Now is the time for all good fallacies to literalize the test data with whatever harmless text comes to the mind of the writer.");
	strcpy(defaultvector[2].Age = 6;
	strcpy(defaultvector[2].IQ = 199;
	strcpy(defaultvector[2].RedCellType = A;
	strcpy(defaultvector[2].RhD = true;

	return &defaultvector;
}

int ParseCSVRecord(char *csvLine, ItemType *pItem) {
	if ( ! csvLine || strlen(csvLine) < 16 ) { return EOF }
	char * fptr = strtok(csvLine,",");
	strcpy(pItem->LastName,fptr);
	strcpy(pItem->FirstName,strtok(NULL,","));

	strcpy(pItem->LifeStory,strtok(NULL,","));

	pItem->Age = (char) atoi(strtok(NULL,","));
	pItem->IQ = (char) atoi(strtok(NULL,","));

	pItem->RedCellType = O;
	fptr = strtok(NULL,",");
	if (strcmp(fptr,"A") == 0)	pItem->RedCellType = A;
	if (strcmp(fptr,"AB") == 0)	pItem->RedCellType = AB;
	if (strcmp(fptr,"B") == 0)	pItem->RedCellType = B;

	pItem->RhD = false;
	fptr = strtok(NULL,",");
	if (strcmp(fptr,"positive") == 0)	pItem->RhD = true;
	if (strcmp(fptr,"p") == 0)			pItem->RhD = true;
	return 0;
}

size_t SetCSVRecord(char *bBuffer, ItemType *pItem) {
	size_t r
	r = sprintf(bBuffer,"%s,%s,%s,%d,%d",pItem->LastName,pItem->FirstName,pItem->LifeStory,pItem->Age,pItem->IQ);
	switch(pItem->RedCellType) {
		case A:
			r += sprintf(bBuffer,"A,");
			break;
		case AB:
			r += sprintf(bBuffer,"AB,");
			break;
		case B:
			r += sprintf(bBuffer,"B,");
			break;
		default:
			r += sprintf(bBuffer,"O,");
			break;
	}
	r += sprintf(bBuffer,"%s\n",pItem->RhD ? "positive" : "negative")

	return r;
}

#else

int Cmp0ItemType(const void *pItemArray1, const void *pItemArray2) {
	
	const ItemType *pit1 = (const ItemType *) pItemArray1;
	const ItemType *pit2 = (const ItemType *) pItemArray2;

	if ( *pit1 < *pit2 ) {
		return LessThanValue;
	}
	if ( *pit1 > *pit2 ) {
		return GreaterThanValue;
	}
	return 0;
}

int Cmp1ItemType(const void *pItemArray1, const void *pItemArray2) {
	
	const ItemType *pit1 = (const ItemType *) pItemArray1;
	const ItemType *pit2 = (const ItemType *) pItemArray2;

	/* This idea taken from:  
		https://www.gnu.org/software/libc/manual/html_mono/libc.html#Comparison-Functions
	Probably not better, due to my SortAscending option here.
	 */
	if ( SortAscending )	return ( (*pit1 > *pit2) - (*pit1 < *pit2) );
							return ( (*pit1 < *pit2) - (*pit1 > *pit2) );
}

/* Copies in C go from right to left, like assignments, so doing that here: */
int CopyItem(ItemType *pItem1, ItemType *pItem2) {
	*pItem1 = *pItem2; 
}

int DumpRecord(FILE *ofp, ItemType *pItem) {
	fprintf(ofp,"%d,",(int)*pItem);
}

int GenRandomRecord(ItemType *itemRecord) {
	*itemRecord = rand();
	return 0;
}

ItemType * GetDefaultTestVector() {
	static ItemType defaultvector[] = (ItemType []) {1958,5101,6530250,9352619,4512,57,98422,5516,47,46,19961219,1957,0,9,1023,45};

	return &defaultvector;
}

int ParseCSVRecord(char *csvLine, ItemType *pItem) {
	if ( ! csvLine || strlen(csvLine) < 16 ) { return EOF }
	int result = sscanf(bufferStr,"%d",pItem);
	return 0;
}

size_t SetCSVRecord(char *bBuffer, ItemType *pItem) {
	size_t r = sprintf(bBuffer,"%d\n",(int)*pItem);
	return r;
}

#endif

/*	END:  ItemType pre-prosessor conditioned code. */

/*  BEGIN:  Preprocessor independent Interfaces.  */

ComparisonFnPtr GetComparisonFunction(char cmpflag) {
	switch(cmpflag) {
		case '0':  return Cmp0ItemType;
		case '1':  return Cmp1ItemType;
		default:
			fprintf(stderr,"Only two comparison functions available.");
	}
}

ItemType * CopyVector(ItemType *pItemArray, int itemCount) {
	int i;
	ItemType *pnewitem = (ItemType *) calloc(itemCount,ItemTypeSize);

	for(i=0; i<itemCount; ++i) CopyItem(pnewitem+i,pItemArray+i);
	return pnewitem;
}

void CopyVectorData(ItemType *pItemArray1, ItemType *pItemArray2, int itemCount) {
	int i;

	for(i=0; i<itemCount; ++i) CopyItem(pItemArray1+i,pItemArray2+i);
}

int DefaultCount = sizeof(DefaultVector) / sizeof(ItemType);

bool EqualVectors(char cmpFlag, ItemType *pItemArray1, ItemType *pItemArray2, int itemCount) {
	int i;
	ComparisonFnPtr cmp = GetComparisonFunction(cmpFlag);

	for(i=0; i<itemCount; ++i) {
		if ( cmp(pItemArray1+i,pItemArray2+i) != 0 ) { return false; }
	}
	return true;
}

ItemType * MakeReverseOfVector(ItemType *pItemArray, int itemCount) {
	int i,j;
	ItemType *pnewitem = (ItemType *) calloc(itemCount,ItemTypeSize);

	j=itemCount;
	for(i=0; i<itemCount; ++i)
		CopyItem(pnewitem+(--j), pItemArray+i);
	return pnewitem;
}

/* Copies in C go from right to left, like assignments, so doing that here: */
void ReverseCopyVector(ItemType *pItemArray1, ItemType *pItemArray2, int itemCount) {
	int i,j;

	j=itemCount;
	for(i=0; i<itemCount; ++i)
		CopyItem(pItemArray1+(--j), pItemArray2+i);
}

void ReverseVector(ItemType *pItemArray, int itemCount) {
	int i,j;

	j=itemCount;
	for(i=0; i<j; ++i) SwapItem(pItemArray+i,pItemArray+(--j));
}

void SwapItem(ItemType *pItem1,ItemType *pItem2) {
	ItemType buffer = *pItem1;
	*pItem1         = *pItem2;
	*pItem2         = buffer;
}

void ValidateStorageType(char storageType) {
	switch (storageType) {
		case CSV_Storage:
			return;
		case NativeStorage:
			return;
	}
	fprintf(stderr,"Invalid storage type '%c' passed.  Abnormal end.",storageType);
	exit(9);
}

/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890
    I/O Facilities:

		a.  Internals.
		b.	Interfaces.
 */

/* I/O Internals */

#include <sys/stat.h> 


/* I/O Interface procedures */

void DumpVector(FILE *outputFilePointer, ItemType *pItem, int n) {
	int i;

	fprintf(outputFilePointer,"(");
	for(i=0; i<n; ++i) {
		DumpRecord(outputFilePointer,pItem+i);
	}
	fprintf(outputFilePointer,")\n");
}

int GetMaxItemsInFile(char storageType, size_t fileSize) {
	int minrecordsize = GetMinStorageRecordSize(storageType);
	int maxitems = fileSize / minrecordsize;
	return maxitems;
}

size_t GetFileSize(FILE *iFp) {
	int ifd = fileno(iFp);
	struct stat stst;
	int fsr = fstat(ifd,&stst);
	if ( fsr != 0 ) {
		fprintf(stderr, "FATAL:  fstat call failed.\n");
		exit(9);
	}

	return stst.st_size;
}

int GetItemsGivenMaxBufferSize(char storageType, size_t maxBufferSize) {
	ValidateStorageType(storageType);
	size_t navailable;
	switch (storageType) {
		case CSV_Storage:
			navailable = maxBufferSize - LoadBufferIncrement / MaxCSVRecordSize;
			break;
		case NativeStorage:
			navailable = maxBufferSize;
			break;
	}
	return navailable / NativeRecordSize;
}

size_t GetMaxItemRecordReadBufferBytes(char storageType) {
	ValidateStorageType(storageType);
	size_t rbytes;
	switch (storageType) {
		case CSV_Storage:
			rbytes = ItemTypeSize + MaxCSVRecordSize;
			break;
		case NativeStorage:
			rbytes = ItemTypeSize;
			break;
	}
}

size_t GetSizeGivenItemCount(char storageType, int itemCount) {
	ValidateStorageType(storageType);
	size_t bsize = NativeRecordSize * itemCount;
	if ( storageType == CSV_Storage )
		bsize += MaxCSVRecordSize * LoadBufferIncrement;
	return bsize;
}

size_t GetMaxStorageRecordSize(char storageType) {
	ValidateStorageType(storageType);
	switch (storageType) {
		case CSV_Storage:	return MaxCSVRecordSize;
		case NativeStorage:	return NativeRecordSize;
	}
}

size_t GetMinStorageRecordSize(char storageType) {
	ValidateStorageType(storageType);
	switch (storageType) {
		case CSV_Storage:	return MinCSVRecordSize;
		case NativeStorage:	return NativeRecordSize;
	}
}

ItemType * LoadVector(FILE *inputFilePointer, int *n) {
	char b[80];
	ItemType *v;
	
	const size_t LoadTotalLimit = 1024*1024*1024;
	size_t vstepitems = LoadBufferIncrement;
	size_t vitems = vstepitems;
	int i = 0; /* index for a */
	int m = 1; /* memory allocation multiplier */
	char *moremarker = "More";
	int result;

	if ( ! inputFilePointer ) {
		v = DefaultVector;
		*n = DefaultCount;
	} else {
		*n = 0;
		v = (ItemType *) malloc(vitems*ItemTypeSize);
		while( *n < LoadTotalLimit && moremarker ) {
			if (*n) {
				++m; /* because this is safer and clearer than calculating it from i. */
				vitems = vstepitems * m;
				v = (ItemType *) realloc(v,vitems*ItemTypeSize);
			}
			while( *n < vitems ) {
				moremarker = fgets(b,80,inputFilePointer);
				if ( ferror(inputFilePointer) ) {
					fprintf(stderr,"ERROR reading text record into input buffer using fgets.\n");
					fprintf(stderr,"result == %s\n",moremarker);
					exit(9);
				}
				if ( ! moremarker ) break;
				result = ParseCSVRecord(b,v+*n);
				if ( result == EOF ) {
					fprintf(stderr,"ERROR parsing ItemInt from input value '%s' using sscanf.\n",b);
					fprintf(stderr,"result == %d, record number %d\n",result,*n);
					fprintf(stderr,"buffer %s, vitems %d\n",b,(int)vitems);
					exit(result);
				}
				++*n;
			}
		}
	}
	if ( inputFilePointer ) fclose(inputFilePointer);
	return v;
}

int ReadCSV_VectorSegment(FILE *iFp, ItemType *pItemArray, int itemElements) {
	/* Note:  Sizing must be for approximate doubling due to buffer. */
	int byteBufferSize = MaxCSVRecordSize * itemElements;
	int byteReadSize = byteBufferSize - MaxCSVRecordSize;
	char *b = (char *) malloc(byteBufferSize);
	char *bstart = b;
	ItemType *v = pItemArray;
	size_t r;
	int icount = 0;
	int offset;
	int parseresult;
	while ( icount < itemElements ) {
		b = bstart;
		r = fread(b,1,byteReadSize,iFp);
		while ( b[r-1] != '\n' )
			fgets(b + r, MaxCSVRecordSize,iFp);
		while(b) {
			if ( icount == itemElements ) {
				offset = b - bstart;
				fseek(iFp,offset,SEEK_SET);
				break;
			}
			parseresult = ParseCSVRecord(b,v+icount);
			if ( parseresult == EOF ) {
				fprintf(stderr,"ERROR parsing ItemInt from input value '%s' using sscanf.\n",b);
				fprintf(stderr,"result == %d, record number %d\n",parseresult,icount);
				fprintf(stderr,"buffer %s, byteBufferSize %d\n",b,(int)byteBufferSize);
				exit(parseresult);
			}
			++icount;
			b = strtok(NULL, "\n");
		}
	}
	free(bstart);
	return icount;
}

int ReadNativeVectorSegment(FILE *iFp, ItemType *pItemArray, int itemElements) {
	size_t r = fread(pItemArray,ItemTypeSize,itemElements,iFp);
	if ( ferror(iFp) ) {
		fprintf(stderr,"ERROR reading struct records using fread.\n");
		fprintf(stderr,"attempted count==%d\n",itemElements);
		exit(9);
	}
	return (int)r;
}

int WriteNativePointerVector(FILE *oFp, ItemType *pItemArray, int itemElements) {
	/* This is not intended to be efficient, but is merely a placeholder
		for an abstract ingestion mechanism that could take such batches
		efficiently in this form. */
	int i;

	for(i=0; i<itemElements; ++i) {
		size_t r = fwrite(pItemArray+i,ItemTypeSize,1,oFp);
		if ( ferror(oFp) ) {
			fprintf(stderr,"ERROR writing struct records to output file using fwrite.\n");
			fprintf(stderr,"attempted count==%d, result==%d\n",itemElements,(int)r);
			exit(9);
		}
	}
	return (int)r;
}

int WriteNativeVectorSegment(FILE *oFp, ItemType *pItemArray, int itemElements) {
	size_t r = fwrite(pItemArray,ItemTypeSize,itemElements,oFp);
	if ( ferror(oFp) ) {
		fprintf(stderr,"ERROR writing struct records to output file using fwrite.\n");
		fprintf(stderr,"attempted count==%d, result==%d\n",itemElements,(int)r);
		exit(9);
	}
	return (int)r;
}

int WriteCSV_VectorSegment(FILE *oFp, ItemType *pItemArray, int itemElements) {
	/* Note:  Sizing must be for approximate doubling due to buffer. */
	int i; 
	size_t rsl=0; /* record string length */
/* TBD:  The buffering here doubles the usage approximately, so the calculation function needs to be corrected for this. */
	int byteBufferSize = MaxCSVRecordSize * itemElements;
	char *b = (char *) malloc(byteBufferSize);
	for(i=0; i < itemElements; ++i) rsl = SetCSVRecord(b+rsl,pItemArray+i);
	size_t r = fwrite(b,1,rsl,oFp);
	if ( ferror(oFp) ) {
		fprintf(stderr,"ERROR writing struct records to output file using fwrite.\n");
		fprintf(stderr,"attempted count==%d, result==%d\n",itemElements,(int)r);
		exit(9);
	}
	return (int)r;
}

/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890
End of itemtype.c
 */
