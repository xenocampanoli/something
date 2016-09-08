/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890
	itemtype.h
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define CSV_Storage		'c'
#define NativeStorage	'n'

#define LoadBufferIncrement 1024*8

#ifdef __PERSON_ITEMTYPE

#define PointerType true

#define ItemTypeName "person"

#define FirstNameLength 24
#define LastNameLength 32
#define LifeStoryLength 128

#define NameChars " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define StoryChars " ,.01234567890;!abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

enum Red_BloodCell_Type { A, B, AB, O }

typedef struct PersonItem {
	char FirstName[FirstNameLength];
	char LastName[LastNameLength];
	char LifeStory[LifeStoryLength];
	unsigned char Age;
	unsigned char IQ;
	enum Red_BloodCell_Type RedCellType;
	bool RhD;
} *ItemType;

#define MaxCSVRecordSize ( FirstNameLength + 1 + LastNameLength + 1 + LifeStoryLength + 1 + 3 + 1 + 3 + 2 + 1 + 9 + 2)
#define MinCSVRecordSize ( 2 + 1 + 2 + 1 + 0 + 1 + 1 + 1 + 2 + 1 + 1 + 1 + 1 + 1 + 1)

#define NativeRecordSize sizeof(struct PersonItem)

#else
	/* In this ppgeneric suite, default ItemType is always int */

#define PointerType false

#define ItemTypeName "int"

typedef int ItemType;

#define ItemByteSizeGuess ( sizeof(ItemType) * 8 )

#define MaxCSVRecordSize ( 16 + 2 )
#define MinCSVRecordSize ( 1 + 1 )
#define NativeRecordSize sizeof(ItemType)

#endif

#define ItemTypeSize sizeof(ItemType)

typedef struct ItemIndex {
	ItemType *pitem;
	int index;
} ItemIndexType;

#define LoadByteLimit 1024*1024*1024
#define LoadItemLimit ( LoadByteLimit / sizeof(NativeRecordSize)

/* Note that for gcc the following is also comparison_fn_t */
typedef int (*ComparisonFnPtr)(const void *, const void *);

extern ComparisonFnPtr GetComparisonFunction(char cmpflag);

extern ItemType * CopyVector(ItemType *pItemArray, int itemCount);

extern void CopyVectorData(ItemType *pItemArray1,ItemType *pItemArray2, int itemCount);

extern void DumpVector(FILE *outputFilePointer, ItemType *pItem, int n);

extern bool EqualVectors(char cmpFlag, ItemType *pItemArray1, ItemType *pItemArray2, int itemCount);

extern int GenRandomRecord(ItemType *itemRecord);

extern size_t GetFileSize(FILE *iFp);
extern int GetItemsGivenMaxBufferSize(char storageType, size_t maxBufferSize);
size_t GetMaxItemRecordReadBufferBytes(char storageType);
extern size_t GetMaxStorageRecordSize(char storageType);
extern size_t GetMinStorageRecordSize(char storageType);

extern ItemType * LoadVector(FILE *inputFilePointer, int *n);

extern int ParseRecord(char *bufferStr, ItemType *pItem);

extern int ReadNativeVectorSegment(FILE *iFp, ItemType *pItemArray, int itemElements);

extern int ReadCSV_VectorSegment(FILE *iFp, ItemType *pItemArray, int itemElements);

extern ItemType * ReverseCopyVector(ItemType *pItemArray, int itemCount);

extern void ReverseCopyVectorData(ItemType *pItemArray1,ItemType *pItemArray2, int itemCount);

extern void ReverseVector(ItemType *pItemArray, int itemCount);

extern void SwapItem(ItemType *pItem1,ItemType *pItem2);

extern int SortAscending;
extern int LessThanValue;
extern int GreaterThanValue;

extern int WriteNativeVectorSegment(FILE *outputFilePointer, ItemType *vSegment, int vSegmentLength);
extern int WriteVectorSegment(FILE *oFp, ItemType *pItemArray, int itemCount);

extern void ValidateStorageType(char storageType);

/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890
End of itemtype.h
 */
