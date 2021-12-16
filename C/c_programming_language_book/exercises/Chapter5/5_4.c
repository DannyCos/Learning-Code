#include <stdio.h>
	
int strend(char *s, char *t);

int main(void) {
	char s[] = "This is a test.";
	char t[] = "test.";

	printf("%d\n", strend(s, t));

	char a[] = "This is a test.";
	char b[] = "fail.";

	printf("%d\n", strend(a, b));
}

int strend(char *s, char *t) {
	while(*s && *s != *t) 
		++s;
	while(*s && *s++ == *t++)	
		;
	return *s == *t;
}
