#include <stdio.h>

#define ASCII_TO_NUM 48

int htoi(char*);
int power(int, int);
int strlength(char*);

int main(int argc, char **argv) {
	printf("%i\n", htoi("0xabcdef"));
	return 0;
}

/* Convert a string in hex format to an integer */
int htoi(char *s) {

	/* Validate that first 2 chars are '0' and 'x' */
	if (*s != '0') {
		return 0;
	}

	s++;
	if (*s != 'x' && *s != 'X') {
		return 0;
	} else {
		s++;
	}

	int value = 0;

	/* Iterate over each char in string */
	for (int i = strlength(s) - 1; *s; s++, i--) {
		
		if (*s >= '0' && *s <= '9') {
			value = value + ((*s - '0') * power(16, i));
		} else if (*s >= 'a' && *s <= 'z') {
			value = value + ((*s - 'a' + 10) * power(16, i));
		} else if (*s >= 'A' && *s <= 'Z') {
			value = value + ((*s - 'A' + 10) * power(16, i));
		}

	}
	return value;
}

int power(int x, int y) {
	int val = 1;
	while(y > 0) {
		val = val * x;
		y--;
	}
	return val;
}

int strlength(char *s) {
	int len = 0;
	while (*s) {
		len++;
		s++;
	}
	return len;
}
