#include <stdio.h>

int main(int argc, char** argv) {
  /* c = character, pc = previous character */
  int c, pc;

  while ((c = getchar()) != EOF) {
    if(c == ' ') {
      if(pc != ' ') {
	putchar(c);
      }
      pc = c;  
    } else {
      putchar(c);
      pc = c;
    }
    
  }
  return 0;
}
