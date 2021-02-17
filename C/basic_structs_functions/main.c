#include <stdio.h>
#include <math.h>

typedef struct {
  int x;
  int y;
} coordinate;

void print_hello_world_5_times_while_loop();

int main(int argc, char** argv) {
  coordinate point;

  point.x = 5;
  point.y = 3;

  double length = sqrt(point.x * point.x + point.y * point.y);

  print_hello_world_5_times_while_loop();
  
  return 0;
}

void print_hello_world_5_times_while_loop() {
  int n = 5;
  while(n > 0) {
    puts("Hello World!");
    n -= 1;
  }
}

void print_hello_world_5_times_for_loop() {
  for(int i = 0; i < 5; i++) {
    puts("Hello World!");
  }
}

void print_hello_world_n_times(int* n) {
  for(int i = 0; i < n; i++) {
    puts("Hello World!");
  }
}


