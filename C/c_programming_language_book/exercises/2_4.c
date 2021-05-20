#include <stdio.h>

void squeeze(char*, char*);

int main(int argc, char **argv) {

	/* Fascinatingly enough, declaring the strings used in squeeze(char[], char[])
		using a pointer, ie.
		char *s = "string"; vs char s[] = "string"

		Will cause a segmentation fault when used as a parameter to squeeze. 

		See c-faq http://c-faq.com/decl/strlitinit.html

	*/

	char s1[] = "aaabbbcccdddeeefff";
	char s2[] = "ccc";

	squeeze(s1, s2);

	printf("%s", s1);
}

void squeeze(char *s1, char *s2) {
	int i, j;

	/* Loop over s1 */
	for(j = i = 0; s1[i] != '\0'; i++) {
		
		/* Check if the char in s1 is contained in s2 */
		/* Save s2 first char pointer */
		char *c1 = s2;
		
		/* Boolean whether char pointed at s1 is equal to any char within s2 */
		int contains = 0;

		/* Loop over s2 till end of string or until the char matches */
		while (*s2 && !contains) {
			if (*s2 == s1[i]) {
				contains = 1;
			}
			s2++;
		}
		/* Set s2 as first char pointer */
		s2 = c1;

		/* If the char is not found, s1 continues as normal */
		if (!contains) {
			s1[j] = s1[i];	
			j++;
		}
	}
	/* Append NULL to new end of s1 */
	s1[j] = '\0';
}
