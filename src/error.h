#ifndef ERROR_H
#define ERROR_H

typedef enum ErrorType 
{
    STACK_OVERFLOW,
    STACK_UNDERFLOW,
    DIVISION_BY_ZERO,
    INCOMPLETE_BRACKETS,
    EOF_REACHED,
    ILLEGAL_CHARACTER,
} ErrorType;

void print_error(ErrorType err);


#endif
