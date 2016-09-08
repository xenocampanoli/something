#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int outmess[2] = {999,8};
	int *inmess=calloc(sizeof(int),2);
	/*int inmess[2];*/

	FILE *fp = fopen("messy2.lst","w");
	int ro = fwrite(outmess,sizeof(int),2,fp);
	fclose(fp);
	fp = fopen("messy2.lst","r");
	int ri = fread(inmess,sizeof(int),2,fp);
	fprintf(stderr,"trace 8 %d, %d; %d, %d\n",ro,outmess[0],ri,inmess[0]);
	fprintf(stderr,"trace 9 %d, %d; %d, %d\n",ro,outmess[1],ri,inmess[1]);
}
