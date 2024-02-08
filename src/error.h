#ifndef ERROR_H
#define ERROR_H

typedef enum ErrorType 
{
    STACK_OVERFLOW,
    STACK_UNDERFLOW,
    DIVISION_BY_ZERO,
    INCOMPLETE_BRACKETS,
    EOF_REACHED
} ErrorType;

void print_error(ErrorType err);


#endif
