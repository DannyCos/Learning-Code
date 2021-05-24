#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void itoa(int n, char s[], int l);
void reverse(char s[]);

int main() {
	char s[100];
	itoa(-2147483648, s, 50);
	printf("%s", s);
	return 0;
}

void itoa(int n, char s[], int l) {
	int i, sign;
	sign = n;

	i = 0;
	do {
		s[i++] = abs(n % 10) + '0';
	} while (n /= 10);

	while (i <= l) {
		s[i++] = '0';
	}

	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

void reverse(char s[]) {
    int c, i, j;
    for ( i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


