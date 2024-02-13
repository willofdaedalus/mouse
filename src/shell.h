#ifndef SHELL_H
#define SHELL_H

#define PROMPT                                      ">>> "

void init_shell(void);
void handle_builtin(char *cmd);

#endif
