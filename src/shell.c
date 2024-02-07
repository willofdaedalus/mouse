#include "shell.h"
#include "environment.h"
#include "interpreter.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* ===== shell commands =====
 * help - prints the help document
 * exit - exits the shell
 * load - loads the specified file
 */

void init_shell()
{
    char *buf;
    size_t size = 0;
    environment *shell_env = init_env();

    while (true)
    {
        printf(PROMPT);
        if ((getline(&buf, &size, stdin) == -1))
        {
            break;
        }

        /* the following before the the interpreter function call
         * basically appends a $ symbol to whatever the user typed
         * which fixes a bug that resulted in numbers being pushed
         * pushing the zeroes the number of it's length times
         * e.g if 890 is pushed three zeroes are also pushed
         */
        int buf_len = strlen(buf);
        char *new_buf = malloc(buf_len + 2);
        if (new_buf == NULL)
            continue;

        /* real appending happens here */
        strncpy(new_buf, buf, buf_len);
        new_buf[buf_len] = '$';
        new_buf[buf_len + 1] = '\0';

        begin_interpreter(new_buf, strlen(new_buf), shell_env, 1);

        free(new_buf);
        free(buf);
    }

    free_env(shell_env);
    free(buf);
}
