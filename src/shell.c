#include "shell.h"
#include "environment.h"
#include "interpreter.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

/* ===== shell commands =====
 * help - prints the help document
 * exit - exits the shell
 * load - loads the specified file
 */

void init_shell()
{
    char *buf = NULL;
    size_t size = 0;
    environment *shell_env = init_env();

    while (true)
    {
        if (isatty(STDIN_FILENO))
            printf(PROMPT);

        ssize_t bytes_read = getline(&buf, &size, stdin);
        if (bytes_read == -1)
        {
            putchar('\n');
            break;
        }

        if (buf[bytes_read - 1] == '\n')
            buf[bytes_read - 1] = '\0';

        /* the following before the interpreter function call
         * appends a $ symbol to whatever the user typed
         */
        int buf_len = strlen(buf);
        char *new_buf = malloc(buf_len + 2);
        if (new_buf == NULL)
            continue;

        /* Append '$' and null-terminate */
        snprintf(new_buf, buf_len + 2, "%s$", buf);

        begin_interpreter(new_buf, strlen(new_buf), shell_env, 1);

        free(new_buf);
    }

    free_env(shell_env);
    free(buf);
}
