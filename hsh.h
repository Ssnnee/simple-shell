#ifndef HSH_H
#define HSH_H

#include <unistd.h>
#define MAX_ARGS 10
#define MAX_LINE 1024

char *app_name;

int _putchar(int c);
int execute(char **args);
char **parse_line(char *line);
int shell_loop(void);

char *get_full_path(char *cmd);
int _strcmp(char *str1, char *str2);

#endif
