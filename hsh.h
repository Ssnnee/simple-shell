#ifndef HSH_H
#define HSH_H

#include <unistd.h>
#define MAX_ARGS 10
#define MAX_LINE 1024

int _putchar(int c);
int execute(char *app_name, char **args, char **envp);
char **parse_line(char *line);
int shell_loop(char *app_name, char **envp);

char *get_full_path(char *cmd, char **envp);
char *get_path(char *cmd, char **envp);
char *get_path_var(char **envp);

int _strcmp(char *str1, char *str2);
int _strlen(char *str);
char *make_path_copy(char *path);

char *_getline(void);
char *_strtok(char *str, char *delimiters);
int find_char(char c, char *str);

int _atoi(char *s);

ssize_t _read_input(char *buf, size_t buf_size);
int _get_line_from_buf(char *buf, int *buf_pos, int buf_size, char **line, int *line_pos, int *line_size);

#endif
