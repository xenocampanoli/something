
#ifdef __PersonStructItemType 

#define FirstNameLength 24
#define LastNameLength 32
#define LifeStoryLenght 128

typedef struct TBD {
	char FirstName[FirstNameLength];
	char LastName[LastNameLength];
	char LifeStory[LifeStoryLength];
	unsigned char Age;
	unsigned char IQ;
} ItemType;

#else

typedef int ItemType;

#endif

extern int itemTypeCmp(const ItemType *pItemType1, const ItemType *pItemType2);
