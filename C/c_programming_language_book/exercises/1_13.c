/* This exercise asks the reader to print a histogram of the length of words on input. */
#include <stdio.h>

#define INSIDE_WORD 1
#define OUTSIDE_WORD 0

#define MAX_WORD_LENGTH 41

void print_histogram_horizontal(int *word_length) {
  for (int i = 0; i < MAX_WORD_LENGTH; ++i) {
    printf(" %2i | ", i+1);
    for(int j = 0; j < word_length[i]; ++j) {
      printf("-");
    }
    printf("\n");
  }
}

void print_histogram_vertical(int *word_length) {
  for (int count_index = 90; count_index > 0; --count_index) {
    for (int i = 0; i < MAX_WORD_LENGTH; ++i) {
      if(word_length[i] >= count_index) {
	printf(" * ");
      } else {
	printf("   ");
      }
    }
    printf("\n");
  }
  //Look... use a monospace font..
  for (int i = 0; i < MAX_WORD_LENGTH; ++i) {
    printf(" %i ", i);
  }
  printf("\n");
}

int main(int argc, char** argv) {

  /* Initialise variables */

  // Character being read
  int c;

  // Counter for current length of word, and state of current position
  int counter, state;

  // Array containing frequency of word lengths
  int word_length[MAX_WORD_LENGTH];

  c = counter = state = 0;
  
  // Initialise the array to contain all zeroes
  for (int i = 0; i < MAX_WORD_LENGTH; ++i) {
    word_length[i] = 0;
  }
  
  // Read letter until EOF is reached.
  while ((c = getchar()) != EOF) {

    //Basically, if C is not an alphanumeric character (we're counting digits as words)
    if (c == ' ' || c == '\t' || c == '\n') {
      //Set the state to outside of word, and add the current length of the word to the word_length array.
      state = OUTSIDE_WORD;

      //For repeated spaces or inputs begenning with whitespaces.
      if(counter != 0) {
	//Increment the array at word length - 1. (As index zero is length 1).
	++word_length[counter - 1];
      }

      //Set counter to 0 once again.
      counter = 0;
    } else if (state == INSIDE_WORD) {
      /* The previous character was a alphanumeric character, and we are currently inside the word */
      ++counter;
    } else {
      /* The previous character was not alphanumeric, we have just reached the beginning of a word */
      state = INSIDE_WORD;
      counter = 1;
    }
  }

  /* If we reached an EOF right after the last character of a word, state will still be INSIDE_WORD,
   * and the final word would not have been added to the array. This adds the word in such a case.
   * Unfortunately, this is rather ugly to have the 'content' of the loop iterate once more outside
   * of the loop. This can be avoided if we instead flag the while loop with a boolean that is set 
   * while iterating through the loop instead. In other words, when EOF is reached, set flag to 1, 
   * add word to array.*/
  if (state == INSIDE_WORD) {
    ++word_length[counter - 1];
  }

  print_histogram_horizontal(word_length);
  print_histogram_vertical(word_length);
}

