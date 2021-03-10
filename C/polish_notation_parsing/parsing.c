#include "mpc.h"

#define VERSION "0.2a"

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

typedef struct {
  int type;
  long num;
  int err;
} lval;

// Enumeration of possible lval 
enum { LVAL_NUM, LVAL_ERR };

// Enumeration of possible error types
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

lval eval(mpc_ast_t* t);
lval eval_op(char* op, lval x, lval y);
lval lval_num(long x);
lval lval_err(int x);
void lval_print(lval v);
void lval_println(lval v);

// Creating a new number type lval
lval lval_num(long x) {
  lval v;
  v.type = LVAL_NUM;
  v.num = x;
  return v;
}

// Creating a new error type lval
lval lval_err(int x) {
  lval v;
  v.type = LVAL_ERR;
  v.err = x;
  return v;
}

// Print lval
void lval_print(lval v) {
  switch (v.type) {
    // In case of number type
  case LVAL_NUM: printf("%li", v.num); break;

    // In case of error type
  case LVAL_ERR:
    if (v.err == LERR_DIV_ZERO) {
      printf("Error: Division by Zero.");
    }
    if (v.err == LERR_BAD_OP) {
      printf("Error: Invalid Operator.");
    }
    if (v.err == LERR_BAD_NUM) {
      printf("Error: Invalid Number.");
    }
    break;
  }
}

void lval_println(lval v) { lval_print(v); putchar('\n'); }
    

lval eval(mpc_ast_t* t) {
  // If tagged as number return it directly.
  if (strstr(t -> tag, "number")) {
    // Check for error in conversion
    errno = 0;
    long x = strtol(t -> contents, NULL, 10);
    return errno != ERANGE ? lval_num(x) : lval_err(LERR_BAD_NUM);
  }

  // The operator is always the second child
  char* op = t -> children[1] -> contents;

  // We store the third child in 'x'
  lval x = eval(t -> children[2]);

  // Iterate over the remaining children and combining
  int index = 3;
  // While child is of type 'expr'
  while (strstr(t -> children[index] -> tag, "expr")) {
    x = eval_op(op, x, eval(t -> children[index]));
    index++;
  }

  return x;
}

lval eval_op(char* op, lval x, lval y) {

  // If either value is an error, return it
  if(x.type == LVAL_ERR) { return x; }
  if(y.type == LVAL_ERR) { return y; }

  if (strcmp(op, "+") == 0 || strcmp(op, "add") == 0) { return lval_num(x.num + y.num); }
  if (strcmp(op, "-") == 0 || strcmp(op, "sub") == 0) { return lval_num(x.num - y.num); }
  if (strcmp(op, "*") == 0 || strcmp(op, "mul") == 0) { return lval_num(x.num * y.num); }
  if (strcmp(op, "/") == 0 || strcmp(op, "div") == 0) {
    // If second operand is zero, return error.
    return y.num == 0 ? lval_err(LERR_DIV_ZERO) : lval_num(x.num / y.num);
  }
  if (strcmp(op, "%") == 0 || strcmp(op, "mod") == 0) { return lval_num(x.num % y.num); }
  if (strcmp(op, "^") == 0) { return lval_num(pow(x.num, y.num)); }
  if (strcmp(op, "min") == 0) { return x.num < y.num ? lval_num(x.num) : lval_num(y.num); }
  if (strcmp(op, "max") == 0) { return x.num > y.num ? lval_num(x.num) : lval_num(y.num); }
  
  return lval_err(LERR_BAD_OP);
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
      lval result = eval(r.output);
      lval_println(result);
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
