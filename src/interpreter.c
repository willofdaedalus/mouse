#include "interpreter.h"
#include "environment.h"
#include "utils.h"

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>


/**
 * main interpreter loop begins here
 *
 * @contents: the source file buffer as a string
 * @file_len: the length of the file or number of bytes in the source file
 * @stack: the general stack
 */
void begin_interpreter(const char *contents, size_t file_len, environment *env)
{
    char c = 0;
    size_t pos = 0;
    bool prime = false;

    while (c != '$')
    {
        prime = false;
        c = contents[pos];

        if (isdigit(c))
        {
            handle_digits(contents, &env->stack, &pos, file_len);
        }

        if (c >= 'A' && c <= 'Z')
        {
            int value = c - ASCII_OFFSET;
            push(env->stack, value);
            pos++;
        }

        switch (c)
        {
            case '~':
                skip_to(contents, &pos, '\n');
                break;

            case '[':
                if (pop(env->stack) <= 0)
                {
                    skip_to(contents, &pos, ']');
                }
                break;

            case ']':
                break;

            case '<': case '=': case '>':
                handle_comparison(c, &env->stack);
                break;

            case ':': case '.':
                handle_alloc(c, &env);
                break;

            case '+': case '*': case '-': case '/': case '\\':
                handle_math(c, &env->stack);
                break;

            case '!': case '?':
                prime = (contents[pos + 1] == '\'');
                handle_io(c, &env->stack, prime);
                pos += prime; /* skip the prime if it's present */
                break;

            case ' ': case '\n':
                pos += 1; /* this might be problematic */
                continue;

            case '\'':
                pos++;
                push(env->stack, (int)contents[pos]);
                break;

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
 * @buf: the source file buffer; needed to read to the rest of the numbers
 * @pos: the current position in the source file buffer
 * @file_size: needed to ensure we don't read past the source file's length
 */
void handle_digits(const char *buf, stack **stack, size_t *pos, size_t len)
{
    int temp = 0;

    /* so long as we haven't hit the end of the buffer and the current
     * character is still a digit we continue parsing
     */
    while (isdigit(buf[*pos]) && *pos < len)
    {
        temp = temp * 10 + (buf[*pos] - '0');
        *pos += 1;
    }

    push(*stack, temp);
}

/**
 * handles math operators that appear while interpreting the file
 *
 * @c: the char that is checked
 * @stack: a pointer to the current stack
 */
void handle_math(const char c, stack **stack)
{
    int rhs = pop(*stack), lhs = pop(*stack);

    /* aside the commutative properties of * and + the others
     * need special checks to make sure they function the way
     * they're supposed to
     */
    switch(c)
    {
        case '+':
            push(*stack, lhs + rhs);
            break;

        case '*':
            push(*stack, lhs * rhs);
            break;

        case '-':
            push(*stack, lhs - rhs);
            break;

        case '\\':
            /* in case the divisor is 0 we throw a division by zero error */
            if (rhs == 0)
            {
                printf("can't divide by zero\n");
                exit(EXIT_FAILURE);
            }

            push(*stack, (int)(lhs % rhs));
            break;

        case '/':
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
void handle_io(char c, stack **stack, bool prime)
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
                 /* Good God I love this language lol
                 * https://stackoverflow.com/a/69587510
                 */
                scanf(" %c", &character);
                push(*stack, (int)character);
            }
            else
            {
                scanf(" %d", &from);
                push(*stack, from);
            }
            break;
    }
}

/**
 * this handles assignment and dereference operators
 *
 * @c: is the character that matches any of the operators
 * @env: the environment we're executing in
 */
void handle_alloc(char c, environment **env)
{
    environment *cur_env = (*env);
    int variable = 0, value = 0;

    switch(c)
    {
        /* assignment operator takes the address of a variable and pushes
         * a new value to the space it occupies
         */
        case ':':
            variable = pop(cur_env->stack), value = pop(cur_env->stack);
            /* pop two items; the variable and the value
             * assign the variable with the value that was popped
             */
            cur_env->variables[variable] = value;
            break;

        /* dereference operator gets the value stored at the variable */
        case '.':
            variable = pop(cur_env->stack);
            push(cur_env->stack, cur_env->variables[variable]);
            break;
    }
}

void handle_comparison(char c, stack **stack)
{
    int rhs = pop(*stack), lhs = pop(*stack);

    switch(c)
    {
        case '>':
            push(*stack, (lhs > rhs) ? 1 : 0);
            break;
        case '<':
            push(*stack, (lhs < rhs) ? 1 : 0);
            break;
        case '=':
            push(*stack, (lhs == rhs) ? 1 : 0);
            break;
    }
}

void skip_to(const char *buf, size_t *pos, char to)
{
    while (buf[*pos] != EOF || buf[*pos] != to)
    {
        *pos += 1;
    }
}
