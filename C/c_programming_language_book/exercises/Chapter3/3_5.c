#include <stdio.h>

void itob(unsigned int n, char s[], int b);
void reverse(char s[]);

int main() {
	char s[100];
	itob(782973489, s, 7);
	printf("%s", s);
	return 0;
}

void itob(unsigned int n, char s[], int b) {
	int i;
	i = 0;

	do {
		int mod = n % b;
		s[i++] = mod < 10 ? mod + '0' : mod - 10 + 'a';
	} while ((n /= b) > 0);

	/* Append NULL and set index to character before */
	s[i--] = '\0';
	
	/* reverse the string */
	for(int j = 0; j < i; ++j, --i) {
		int c = s[j];
		s[j] = s[i];
		s[i] = c;
	}
}

