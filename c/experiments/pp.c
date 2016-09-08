#include <stdio.h>

void swapem(int **p1, int **p2) {
  int *b = *p1;
  *p1 = *p2;
  *p2 = b;
}

void callunder(int a[]) {
	int i,j;
	i = 1;
	j = 2;
	swapem(a+i,a+j);
}

int a[] = (int []) {1958,5101,45};

int main(int argumentCount, char * const* argumentVector) {

	int i,j;

	for(i=0; i<3; ++i) printf("One %d\n",a[i]);
	i = 1;
	j = 2;
	swapem(a+i,a+j);
	for(i=0; i<3; ++i) printf("Two %d\n",a[i]);
	callunder(a);
	for(i=0; i<3; ++i) printf("Three %d\n",a[i]);
}
