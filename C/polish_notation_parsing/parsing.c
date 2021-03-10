#include "mpc.h"

#define VERSION "0.2a"

long eval(mpc_ast_t* t);
long eval_op(char* op, long x, long y);

#ifdef _WIN32
#include <string.h>

static char buffer[2048];

char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1) = '\0';
  return cpy;
}

void add_history(char* unused) {}

#else
#include <readline/readline.h>
#include <readline/history.h>
#endif 

long eval(mpc_ast_t* t) {
  // If tagged as number return it directly.
  if (strstr(t -> tag, "number")) {
    return atof(t -> contents);
  }

  // The operator is always the second child
  char* op = t -> children[1] -> contents;

  // We store the third child in 'x'
  long x = eval(t -> children[2]);

  // Iterate over the remaining children and combining
  int index = 3;
  // While child is of type 'expr'
  while (strstr(t -> children[index] -> tag, "expr")) {
    x = eval_op(op, x, eval(t -> children[index]));
    index++;
  }

  return x;
}

long eval_op(char* op, long x, long y) {
  if (strcmp(op, "+") == 0 || strcmp(op, "add") == 0) { return x + y; }
  if (strcmp(op, "-") == 0 || strcmp(op, "sub") == 0) { return x - y; }
  if (strcmp(op, "*") == 0 || strcmp(op, "mul") == 0) { return x * y; }
  if (strcmp(op, "/") == 0 || strcmp(op, "div") == 0) { return x / y; }
  if (strcmp(op, "%") == 0 || strcmp(op, "mod") == 0) { return x % y; }
  if (strcmp(op, "^") == 0) { return pow(x, y); }
  if (strcmp(op, "min") == 0) { return x < y ? x : y; }
  if (strcmp(op, "max") == 0) { return x > y ? x : y;}
  return 0;
}

int main(int argc, char** argv) {

  /* Create some parsers */
  mpc_parser_t* Number 	= mpc_new("number");
  mpc_parser_t* Operator 	= mpc_new("operator");
  mpc_parser_t* Expr 	= mpc_new("expr");
  mpc_parser_t* Lispy 	= mpc_new("lispy");

  /* Define them with the following Language */
  mpca_lang(MPCA_LANG_DEFAULT,
	    "									\
	  	number		: /-?[0-9]+/ ;					\
	  	operator 	: '+' | '-' | '*' | '/' | '%' | '^' | \"add\" | \"sub\" | \"mul\" | \"div\" | \"mod\" | \"min\" | \"max\" ; \
		expr		: <number> | '(' <operator> <expr>+ ')' ;	\
		lispy		: /^/ <operator> <expr>+ /$/ ;", Number, Operator, Expr, Lispy);

  puts("Lispy Version " VERSION);
  puts("Press Ctrl + c to Exit\n");

  while(1) {

    char* input = readline("lispy>");
    add_history(input);
    
    /* Attempt to parse the user input */
    mpc_result_t r;
  
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      // If successful parse
      long result = eval(r.output);
      printf("%li\n", result);
      mpc_ast_delete(r.output);
    } else {
      /* Otherwise print the error */
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
  }
  
  mpc_cleanup(4, Number, Operator, Expr, Lispy);
  
  return 0;
}
