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
char *make_path_copy(char *str);
int _strncmp(char *str1, char *str2, int n);
char *_strcat(char *dest, char *src);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strcmp(char *str1, char *str2);

char *_getline(void);
char *_strtok(char *str, char *delimiters);
int find_char(char c, char *str);

int _atoi(char *s);

ssize_t _read_input(char *buf, size_t buf_size);
int _get_line_from_buf(char *buf, int *buf_pos, int buf_size, char **line, int *line_pos, int *line_size);

char *_strtok_two(char *str, char *delimiters, char **saveptr);
char *_memset(char *str, char b, unsigned int n);
char *_strdup(char *str);
int _printenv(char **env);
void my_exit(char **args, char *cmd, char **envp);
void my_free_args(char **args);
#endif
