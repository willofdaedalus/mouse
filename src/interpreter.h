#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "environment.h"

#include <stdlib.h>
#include <stdbool.h>

void begin_interpreter(const char *contents, size_t file_len, environment *env);

/* handlers */
void handle_alloc(const char c, environment **env);
void skip_to(const char *buf, size_t *pos, const char from, const char to);
void handle_loop(const char *buf, size_t *pos, environment **env);
void handle_comparison(const char c, stack **stack);
void handle_math(const char c, stack **stack);
void handle_io(const char c, stack **stack, bool input);
void handle_digits(const char *buf, stack **stack, size_t *cur_pos, size_t len);


#endif
