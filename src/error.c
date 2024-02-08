#include "error.h"

#include <stdio.h>

void print_error(ErrorType err)
{
    char *msg;

    if (err == STACK_OVERFLOW)
        msg = "mouse: there's is a stack overflow in your program\n";
    else if (err == STACK_UNDERFLOW)
        msg = "mouse: there's is a stack underflow in your program\n";
    else if (err == DIVISION_BY_ZERO)
        msg = "mouse: division by zero in your program\n";
    else if (err == INCOMPLETE_BRACKETS)
        msg = "mouse: incomplete number of brackets\n";
    else if (err == EOF_REACHED)
        msg = "mouse: no $ found at end of the source file\n";

    printf("%s", msg);
}
