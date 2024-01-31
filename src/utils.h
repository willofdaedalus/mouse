#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>

size_t load_file(FILE *src, char **contents);
bool is_digit(char c);
bool is_variable(char c);

#endif
