#include <stdio.h>
#include <string.h>

void f1(char *someStr) {
	printf("trace 3 %d\n",(int)(sizeof(someStr)));
	printf("trace 4 %d\n",(int)(strlen(someStr)));
}

int main() {
	char charset[] = "0123456789"
				 "abcdefghijklmnopqrstuvwxyz"
				 "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	printf("trace 0\n");
	printf("trace 1 %d\n",(int)(sizeof charset));
	printf("trace 1a %d\n",(int)(sizeof charset[0]));
	printf("trace 1b %d\n",(int)(sizeof(charset)));
	printf("trace 2 %d\n",(int)(strlen(charset)));
	f1(charset);
}
