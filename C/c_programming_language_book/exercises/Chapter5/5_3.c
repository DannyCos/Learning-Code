#include <stdio.h>

void strcat(char *s, char *t);

int main(void) {
	char s[50] = "This is a test";
	char t[] = "for strcat.";

	strcat(s, t);

	printf("%s", s);
}


void strcat(char *s, char *t) {
	while(*s)
		++s;
	while((*s++ = *t++))
		;
}
