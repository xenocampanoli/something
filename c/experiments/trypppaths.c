/* Return a function Pointer from a function */
#include "../env.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DSPEC "/here/there"
#define FILENAME "everywhere"
#define FSPEC DSPEC"/"FILENAME

#define TestData0FSpec RelSpecTestData"/inttestdata0.lst"

int main(int argumentCount, char * const* argumentVector) {
	FILE *fp = fopen(TestData0FSpec,"r");
	char b[2048];
	int r;


	printf("path value 1:  %s\n",FSPEC);
	printf("path value 2:  %s/%s\n",DSPEC,FILENAME);
	printf("path value 3:  %s\n",TestData0FSpec);

	r = fread((void *)b,1,2048,fp);
	puts(b);
}
