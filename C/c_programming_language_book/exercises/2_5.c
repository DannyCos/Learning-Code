#include <stdio.h>

int any(char*, char*);

int any(char *s1, char *s2) {
	int i;

	for(i = 0; s1[i] != '\0'; i++) {
		
		char *c1 = s2;
		while (*s2) {
			if (*s2 == s1[i]) {
				return i;
			}
			s2++;
		}
		s2 = c1;
	}

	return -1;
}

int main(int argc, char **argv) {
	char *s1 = "get position of this h";
	char *s2 = "zzzhzzz";

	int pos = any(s1, s2);
	printf("%i", pos); 
}
