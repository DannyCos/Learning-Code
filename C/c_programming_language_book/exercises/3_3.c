#include <stdio.h>

void expand(char *s1, char s2[]);

int main() {
	char *s1 = "a-b-cA-Z";
	char s2[100];

	/* The following string pattern will cause a segmentation fault 
		b-c-a
		where the the first character is lower in value than 
		the last character, seperated by a character that is lower than the first
	*/

	expand(s1, s2);

	printf("%s", s2);
}

void expand(char *s1, char s2[]) {
	while (*s1) {
		if (*s1 != '-' && *(s1+1) == '-' && *(s1+2) != '-' && *(s1+2) > *s1) {
			int base = *s1;
			while(*(s1+1) == '-' && *(s1+2) != '\0') {
				s1+=2;
			}
			while (base != *s1) {
				*s2++ = base++;
			} 
		} else {
			*s2++ = *s1++;
		}
	}
	*s2 = '\0';
}
