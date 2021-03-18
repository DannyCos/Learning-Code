#include <stdio.h>


int main(int argc, char** argv) {

  int c;
  
  while((c = getchar()) != EOF) {
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
      putchar('x');
    } else if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
      putchar('X');
    } else {
      putchar(c);
    }
  }

  return 0;
}
