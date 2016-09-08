/* Use two type defs that are the same interchangeably. */
#include <stdio.h>

void byeguy(char x, int y) {
	printf("Bye y'all:  %c, %d\n",x,y);
}

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

typedef void (*FPTRD1)();
typedef void (*FPTRD2)(char,int);

FPTRD1 callagain() { return justprintit; }
FPTRD2 callbye() {
	return byeguy;
}

int main(int argumentCount, char * const* argumentVector) {
	void (*jpi1)() = justprintit;
	void (*jpi2)() = callunder();
	void (*jpi3)(char,int) = callreally();
	FPTRD2 jpi4 = callreally();
	FPTRD1 jpi5 = callagain();
	FPTRD2 jpi6 = callbye();

	justprintit();
	jpi1();
	jpi2();
	jpi3('x',57);
	jpi4('a',0);
	jpi5();
	jpi6('c',3);
}
