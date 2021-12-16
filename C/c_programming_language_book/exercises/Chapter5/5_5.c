#include <stdio.h>

char *strncpy1(char *s, char *t, int n);
char *strncpy2(char *s, char *t, int n);
char *strncat1(char *s, char *t, int n);
int strncmp1(char *s, char *t, int n);

int main(int argc, char **argv) {
	char s[50] = "This is a test";
	char t[] = "Whatever.";
	
	strncpy2(s, t, 4);

	printf("%s\n", s);

	char a[50] = "This is a ";
	char b[] = "test for strcat.";

	strncat1(a, b, 8);
	
	printf("%s\n", a);

	printf("%d", strncmp1("test what", "test this", 4));
}

// Copies n chars of t into s, stopping at first null character reached or when n chars has been reached.
char *strncpy1(char *s, char *t, int n) {
	while(n-- && (*s++ = *t++))
		;
	return s;
}

// Copies n chars of t into s, pads 0 if t is shorter than n
char *strncpy2(char *s, char *t, int n) {
	while(n--) {
		*s++ = *t ? *t++ : '\0';	
	}
	return s;
}

char *strncat1(char *s, char *t, int n) {
	while(*s)
		++s;
	while(n-- && (*s++ = *t++))
		;
	return s;
}

int strncmp1(char *s, char *t, int n) {
	while(n-- && (*s++ == *t++))
		;
	return *s - *t;
}
