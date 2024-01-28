#include "interpreter.h"
#include "stack.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>


/**
 * main interpreter loop begins here
 *
 * @contents: the source file buffer as a string
 * @file_len: the length of the file or number of bytes in the source file
 * @stack: the general stack
 */
void begin_interpreter(char *contents, size_t file_len, stack *stack)
{
    char cur_char = 0;
    size_t pos = 0;
    bool prime = false;

    while (pos < file_len)
    {
        cur_char = contents[pos];

        if (is_digit(cur_char))
        {
            handle_numbers(&stack, contents, &pos, file_len);
        }

        switch (cur_char)
        {
            case '+': case '*': case '-': case '/': case '\\':
                handle_math_operators(cur_char, &stack);
                break;

            case '!': case '?':
                prime = contents[++pos] == '\'';
                handle_io_operators(cur_char, &stack, prime);
                /* hack to skip the prime symbol in order to not process it */
                pos = prime ? pos + 1 : pos - 1;
                break;

            case ' ': case '\n':
                pos += 1; /* this might be problematic */
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
 * function that "builds" a number
 *
 * @stack: the stack to push the number into
 * @cur_char: the character to check
 * @cur_pos: the current position in the source file buffer
 * @file_size: needed to ensure we don't read past the source file's length
 */
void handle_numbers(stack **stack, char *buf, size_t *cur_pos, size_t len)
{
    int temp = 0;

    while (is_digit(buf[*cur_pos]) && *cur_pos < len)
    {
        temp = temp * 10 + (buf[*cur_pos] - '0');
        *cur_pos += 1;
    }

    push(*stack, temp);
}

/**
 * handles math operators that appear while interpreting the file
 *
 * @cur_char: the char that is checked
 * @stack: a pointer to the current stack
 */
void handle_math_operators(char c, stack **stack)
{
    int lhs = 0, rhs = 0;

    /* aside the commutative properties of * and + the others
     * need special checks to make sure they function the way
     * they're supposed to
     */
    switch(c)
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

        case '\\':
            rhs = pop(*stack), lhs = pop(*stack);

            /* in case the divisor is 0 we throw a division by zero error */
            if (rhs == 0)
            {
                printf("can't divide by zero\n");
                exit(EXIT_FAILURE);
            }

            push(*stack, (int)(lhs % rhs));
            break;

        case '/':
            rhs = pop(*stack), lhs = pop(*stack);

            /* in case the divisor is 0 we throw a division by zero error */
            if (rhs == 0)
            {
                printf("can't divide by zero\n");
                exit(EXIT_FAILURE);
            }

            push(*stack, (int)(lhs / rhs));
            break;
    }
}

/**
 * function that handles basic i/o, for both numbers and letters
 *
 * @c: the character to check
 * @stack: the general stack
 * @prime: this is true if the next character after the operator is
 * an apostrophe. if that's the case, the both output and input are
 * adjusted for characters instead of numbers like default
 */
void handle_io_operators(char c, stack **stack, bool prime)
{
    int from = 0;
    switch(c)
    {
        /* operator that writes to stdout */
        case '!':
            if (prime)
            {
                /* chose to use printf instead of putchar for single
                 * character to maintain consistency with %d formatter
                 */
                printf("%c", pop(*stack));
            }
            else
            {
                printf("%d", pop(*stack));
            }
            break;

        /* operator that reads from from stdin */
        case '?':
            if (prime)
            {
                char character = 0;
                scanf("%c", &character);
                push(*stack, (int)character);
            }
            else
            {
                scanf("%d", &from);
                push(*stack, from);
            }
            break;
    }
}
