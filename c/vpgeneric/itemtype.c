#include "./itemtype.h"

#ifdef __AscendingSort

#define GreaterThanValue -1
#define LessThanValue 1

#else

#define GreaterThanValue 1
#define LessThanValue -1

#endif

#ifdef __PersonStructItemType 

int itemTypeCmp(const ItemType *pItemType1, const ItemType *pItemType2) {
	if ( memcmp(pItemType1->LastName,pItemType2->LastName) < 0 ) {
		return LessThanValue;
	}
	if ( memcmp(pItemType1->LastName,pItemType2->LastName) > 0 ) {
		return GreaterThanValue;
	}
	if ( memcmp(pItemType1->FirstName,pItemType2->FirstName) < 0 ) {
		return LessThanValue;
	}
	if ( memcmp(pItemType1->FirstName,pItemType2->FirstName) > 0 ) {
		return GreaterThanValue;
	}
	return 0
}

#else

int intTypeCmp(const void *pItemType1, const ItemType *pItemType2) {
	if ( *pItemType1 < *pItemType2 ) {
		return LessThanValue;
	}
	if ( *pItemType1 > *pItemType2 ) {
		return GreaterThanValue;
	}
	return 0;
}

#endif

