#ifndef HSH_H
#define HSH_H

#include <unistd.h>
#define MAX_ARGS 10
#define MAX_LINE 1024

int _putchar(int c);
int execute(char *app_name, char **args, char **envp);
char **parse_line(char *line);
int shell_loop(char *app_name, char **envp);

char *get_full_path(char *cmd);
int _strcmp(char *str1, char *str2);

#endif
