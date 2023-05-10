#ifndef MAIN_H
#define MAIN_H

#include <signal.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdarg.h>

typedef struct liststr
{
	char **args;
	char *argv;
	char **env;
	int number;
} list_t;

extern char **environ;
void _isatty(void);
void freee(void *nptr);
void _EOF(int bytes, char *line);
void sig_handler(int signal);
char *_strtok(char *str, const char *delim);
int _atoi(const char *nptr);
void parse_input(char *line, char **args, int *arg_index);
void execute_command(char **args);
char *search_path(char *cmd);
char *_strcat(char *dest, const char *src);
char *_strdup(const char *s);
void *_realloc(void *old, size_t size);
char *_getenv(const char *name);
void *_memcpy(void *dest, const void *src, size_t n);
char *_strchr(const char *s, int c);
size_t _strlen(const char *s);
int _strcmp(char const string1[], char const string2[]);
int _strncmp(const char *s1, const char *s2, size_t n);
int _putchar(char c);
void _puts(char *str);
char *_getline(char *cmd, int fd, int *status);
char *_changer(unsigned int number);
void _error(list_t *list, char *string);
int main();
void command_not_found_handle();

#endif
