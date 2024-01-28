#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "stack.h"
#include <stdlib.h>

void begin_interpreter(char *contents, size_t file_len, stack *stack);

/* handlers */
void handle_math_operators(char cur_char, stack **stack);
void handle_io_operators(char c, stack **stack);
void handle_numbers(stack **stack, char *buf, size_t *cur_pos, size_t len);


#endif
