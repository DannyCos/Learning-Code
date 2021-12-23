#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 1024

double s[STACK_SIZE];
int sp = 0;

double pop() {
	return s[--sp];
}

void push(double x) {
	s[sp++] = x;
}

int main(int argc, char **argv) {
	double value;
	for (int i = 1; i < argc; ++i) {
		switch(*argv[i]) {
		case '\0':
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			push(atof(argv[i]));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '-':
			value = pop();
			push(pop() - value);
			break;
		case '*':
			push(pop() * pop());
			break;
		case '/':
			value = pop();
			push(pop() / value);
			break;
		default:
			break;
		}
	}

	printf("%g\n", pop());
	return 0;
}
