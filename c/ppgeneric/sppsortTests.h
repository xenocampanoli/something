/* sppsortTests.h */

#include "../env.h"
#include "sppsorts.h"
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

#endif

/* End of sppsortTests.h */
