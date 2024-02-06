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
        printf("\n"PROMPT);
        if ((getline(&buf, &size, stdin) == -1))
        {
            break;
        }

        begin_interpreter(buf, strlen(buf), shell_env, 1);
    }

    free_env(shell_env);
    free(buf);
}
