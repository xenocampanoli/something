
typedef int ItemType;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char *s = "Now is the time for all good folks to come to the country of their aid.";
	char sn = strlen(s) + 1;
	char *b = malloc(sn);
	char *bs = b;
	strcpy(b,s);
	int dn;

	printf("trace 0 %d\n",sn);
	printf("trace 1 %s\n",b);
	
	b = strtok(b," ");
	while(b) {
		sscanf(b,"%d",&dn);
		printf("trace 1 %s,%d\n",b,dn);
		b = strtok(NULL, " ");
	}
	free(bs); 
}
