/* Return a function Pointer from a function */
#include <stdio.h>

void justprintit() {
	printf("Hello, world\n");
}

void reallyprintit(char x, int y) {
	printf("Hello, world:  %c, %d\n",x,y);
}

void (*callunder())() {
	return justprintit;
}

void (*callreally())(char,int) {
	return reallyprintit;
}

int main(int argumentCount, char * const* argumentVector) {
	void (*jpi1)() = justprintit;
	void (*jpi2)() = callunder();
	void (*jpi3)(char,int) = callreally();

	justprintit();
	jpi1();
	jpi2();
	jpi3('x',57);
}
