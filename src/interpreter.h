#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "stack.h"
#include <stdlib.h>

void begin_interpreter(char *contents, size_t file_len, stack *stack);

/* handlers */
void handle_math_operators(char cur_char, stack **stack);
void handle_operators(char cur_char, stack **stack);


#endif
