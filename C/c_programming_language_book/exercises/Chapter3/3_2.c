#include <stdio.h>

void escape(char *s, char *t);
void unescape(char *s, char *t);

int main(int argc, char **argv) {
	char *test = "this	is	a	test	.";
	char s[500];
	char *test2 = "this\\tis\\na\\ptest\\n.";
	char s2[500];

	escape(s, test);

	unescape(s2, test2);

	printf("%s\n\n", s);
	printf("%s\n\n", s2);
}

/* Copies string t to s while replacing tab and newline characters with visible escapes char sequences */
void escape(char *s, char *t) {
	for( ; *t; ++s, ++t) {
		switch(*t) {
			case '\n':
				*s++ = '\\';
				*s = 'n';
				break;
			case '\t':
				*s++ = '\\';
				*s = 't';
				break;
			default:
				*s = *t;
				break;
		}		
	}
	*s = '\0';
}

void unescape(char *s, char *t) {
	for( ; *t ; ++s, ++t) {
		switch(*t) {
		case '\\': 
			switch (*++t) {
			case 'n': 
				*s = '\n';
				break; 
			case 't': 
				*s = '\t';
				break; 
			default : 
				*s++ = '\\';
				*s = *t;
				break; 
			}
			break;
		default:
			*s = *t;
			break;
		}
	}
	*s = '\0';
}
