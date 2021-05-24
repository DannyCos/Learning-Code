#include <stdio.h>

int main(int argc, char** argv) {
  int c, count;

  while((c = getchar()) != EOF) {
    if(c == ' ' || c == '\t' || c == '\n') {
      count++;
    }
  }
  printf("%i blanks, tabs and newlines counted.", count);
}
