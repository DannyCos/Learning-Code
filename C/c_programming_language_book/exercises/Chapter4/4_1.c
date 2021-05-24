#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int getline2(char line[], int max);
int strindex(char source[], char searchfor[]);

char *pattern = "ould";

int main(int argc, char **argv) {
	char line[MAXLINE];
	int found = 0;
	while (getline2(line, MAXLINE) > 0)
		if(strindex(line, pattern) >= 0) {
			printf("%s", line);
			found++;
		}
	return found;
}

int getline2(char s[], int lim) {
	int c, i;

	i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/* Find furthest right substring matching t within s */
int strindex(char *s, char *t) {
	int i, j;
	for(i = strlen(s), j = 0; i >= 0; i--) {
		for ( ; s[i+j] == t[j]; j++)
			;
		if(t[j] == '\0')
			return i;
		j = 0;
	}
	
	return -1;
}
