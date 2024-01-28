#include "interpreter.h"

#include <string.h>
#include <stdio.h>


void begin_interpreter(char *contents, size_t file_len, stack *stack)
{
    char cur_char = 0;
    size_t pos = 0;

    while (pos < file_len)
    {
        cur_char = contents[pos];

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

void handle_math_operators(char cur_char, size_t *cur_pos)
{
}
