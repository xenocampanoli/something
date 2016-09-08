#include <stdio.h>
#include <string.h>

int main() {
	int outmess= 999;
	int inmess;

	FILE *fp = fopen("messy.lst","w");
	int ro = fwrite(&outmess,sizeof(int),1,fp);
	fclose(fp);
	fp = fopen("messy.lst","r");
	int ri = fread(&inmess,sizeof(int),1,fp);
	fprintf(stderr,"trace 9 %d, %d; %d, %d\n",ro,outmess,ri,inmess);
}
