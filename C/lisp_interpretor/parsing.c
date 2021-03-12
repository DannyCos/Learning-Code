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
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

void add_history(char* unused) {}

#else
#include <readline/readline.h>
#include <readline/history.h>
#endif 

//Union type stores all memory in same spot, only one element can be used at once, making it useful for structures where only 1 type is used.
//Struct has seperate memory location for each element, all can be used at once.
//typdef union {
typedef struct lval {
  int type;
  double num;
  /* Error and Symbol types have some string data */
  char* err;
  char* sym;
  /* Count and Pointer to a list of "lval*" */
  int count;
  struct lval** cell;
} lval;

// Enumeration of possible lval 
enum { LVAL_NUM, LVAL_ERR, LVAL_SYM, LVAL_SEXPR };

// Enumeration of possible error types
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

// Constructing a pointer to a new Number lval
lval* lval_num(double x) {
  lval* v = malloc(sizeof(lval));
  v -> type = LVAL_NUM;
  v -> num = x;
  return v;
}

// Constructing a pointer to a new Error lval
lval* lval_err(char* m) {
  lval* v = malloc(sizeof(lval));
  v -> type = LVAL_ERR;
  v -> err = malloc(strlen(m) + 1);
  strcpy(v -> err, m);
  return v;
}

// Constructing a pointer to a new Symbol lval
lval* lval_sym(char* s) {
  lval* v = malloc(sizeof(lval));
  v -> type = LVAL_SYM;
  v -> sym = malloc(strlen(s) + 1);
  strcpy(v -> sym, s);
  return v;
}

lval* lval_sexpr(void) {
  lval* v = malloc(sizeof(lval));
  v -> type = LVAL_SEXPR;
  v -> count = 0;
  v -> cell = NULL;
  return v;
}

lval* lval_read_num(mpc_ast_t* t) {
  errno = 0;
  double x = strtod(t->contents, NULL);
  return errno != ERANGE ? lval_num(x) : lval_err("Invalid Number");
}

lval* lval_add(lval* v, lval* x) {
  v->count++;
  v->cell = realloc(v->cell, sizeof(lval*) * v->count);
  v->cell[v->count-1] = x;
  return v;
}

lval* lval_read(mpc_ast_t* t) {
  // If symbol or number return converion to that type
  if (strstr(t->tag, "number")) { return lval_read_num(t); }
  if (strstr(t->tag, "symbol")) { return lval_sym(t->contents); }

  //If root or sexpr then create empty list
  lval* x = NULL;
  if (strcmp(t->tag, ">") == 0) { x = lval_sexpr(); }
  if (strstr(t->tag, "sexpr"))	{ x = lval_sexpr(); }

  // Fill this list with any valid expressions contained within
  for (int i = 0; i < t->children_num; i++) {
    if (strcmp(t->children[i]->contents, "(") == 0) { continue; }
    if (strcmp(t->children[i]->contents, ")") == 0) { continue; }
    if (strcmp(t->children[i]->tag, "regex") == 0) { continue; }
    x = lval_add(x, lval_read(t->children[i]));
  }

  return x;
}

void lval_expr_print(lval* v, char open, char close) {
  putchar(open);
  for (int i = 0; i < v->count; i++) {
    // Print Value contained within
    lval_print(v->cell[i]);

    // Don't print trailing space if last element
    if (i != (v->count-1)) {
      putchar(' ');
    }
  }
  putchar(close);
}

// Print lval
void lval_print(lval* v) {
  switch (v->type) {
    // In case of number type
  case LVAL_NUM: printf("%f", v->num); break;

    // In case of error type
  case LVAL_ERR: printf("Error: %s", v->err); break;
  case LVAL_SYM: printf("%s", v->sym); break;
  case LVAL_SEXPR: lval_expr_print(v, '(', ')'); break;
  }
}

void lval_println(lval* v) { lval_print(v); putchar('\n'); }

void lval_del(lval* v) {
  switch (v -> type) {
    // do nothing for number type
  case LVAL_NUM: break;

    // For err or sym free the string data
  case LVAL_ERR: free(v -> err); break;
  case LVAL_SYM: free(v -> sym); break;

    // If Sexpr then delete all elements inside
  case LVAL_SEXPR:
    for (int i = 0; i < v -> count; i++) {
      lval_del(v->cell[i]);
    }
    free(v -> cell);
    break;
  }

  // Finally, free memory allocated for struct itself
  free(v);
}
    

lval eval(mpc_ast_t* t) {
  // If tagged as number return it directly.
  if (strstr(t -> tag, "number")) {
    // Check for error in conversion
    errno = 0;
    double x = strtod(t -> contents, NULL);
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
  if (strcmp(op, "%") == 0 || strcmp(op, "mod") == 0) { return lval_num(fmod(x.num, y.num)); }
  if (strcmp(op, "^") == 0) { return lval_num(pow(x.num, y.num)); }
  if (strcmp(op, "min") == 0) { return x.num < y.num ? lval_num(x.num) : lval_num(y.num); }
  if (strcmp(op, "max") == 0) { return x.num > y.num ? lval_num(x.num) : lval_num(y.num); }
  
  return lval_err(LERR_BAD_OP);
}

int main(int argc, char** argv) {

  /* Create some parsers */
  mpc_parser_t* Number 	= mpc_new("number");
  mpc_parser_t* Symbol	= mpc_new("symbol");
  mpc_parser_t* Sexpr	= mpc_new("sexpr");
  mpc_parser_t* Expr 	= mpc_new("expr");
  mpc_parser_t* Lispy 	= mpc_new("lispy");

  /* Define them with the following Language */
  mpca_lang(MPCA_LANG_DEFAULT,
	    "									\
	  	number		: /-?[0-9]+(\\.[0-9]+)?/ ;					\
	  	symbol	 	: '+' | '-' | '*' | '/' | '%' | '^' | \"add\" | \"sub\" | \"mul\" | \"div\" | \"mod\" | \"min\" | \"max\" ; \
		sexpr		: '(' <expr>* ')' ;	\
		expr		: <number> | <symbol> | <sexpr> ;	\
		lispy		: /^/ <expr>* /$/ ;", Number, Operator, Expr, Lispy);

  puts("Lispy Version " VERSION);
  puts("Press Ctrl + c to Exit\n");

  while(1) {

    char* input = readline("lispy>");
    add_history(input);
    
    /* Attempt to parse the user input */
    mpc_result_t r;
  
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      // If successful parse
      lval* x = lval_read(r.output);
      lval_println(x);
      lval_del(x);
    } else {
      /* Otherwise print the error */
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
  }
  
  mpc_cleanup(5, Number, Symbol, Sexpr, Expr, Lispy);
  
  return 0;
}
