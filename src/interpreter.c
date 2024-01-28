#include "interpreter.h"
#include "stack.h"

#include <stdlib.h>
#include <stdio.h>


void begin_interpreter(char *contents, size_t file_len, stack *stack)
{
    char cur_char = 0;
    size_t pos = 0;

    while (pos < file_len)
    {
        cur_char = contents[pos];

        handle_math_operators(cur_char, &stack);

        switch (cur_char)
        {
            case ' ':
                continue;

            case '"':
                pos++; /* skip the current character to read from the next */
                while (contents[pos] != '"')
                {
                    if (contents[pos] == '!')
                        putchar('\n');
                    else
                        putchar(contents[pos]);

                    pos++;
                }
                break;
            
            case '$':
                return;

            default:
                continue;
        }

        pos++;
    }
}

/**
 * handles math operators that appear while interpreting the file
 *
 * @cur_char: the char that is checked
 * @stack: a pointer to the current stack
 */
void handle_math_operators(char cur_char, stack **stack)
{
    int lhs = 0, rhs = 0;

    /* aside the commutative properties of * and + the others
     * need special checks to make sure they function the way
     * they're supposed to
     */
    switch(cur_char)
    {
        case '+':
            rhs = pop(*stack), lhs = pop(*stack);
            push(*stack, lhs + rhs);
            break;

        case '*':
            rhs = pop(*stack), lhs = pop(*stack);
            push(*stack, lhs * rhs);
            break;

        case '-':
            rhs = pop(*stack), lhs = pop(*stack);
            push(*stack, lhs - rhs);
            break;

        case '/':
            rhs = pop(*stack), lhs = pop(*stack);

            /* in case the divisor is 0
             * we throw a division by zero error
             */
            if (rhs == 0)
            {
                printf("can't divide by zero\n");
                exit(EXIT_FAILURE);
            }

            push(*stack, (int)(lhs / rhs));
            break;
    }
}
