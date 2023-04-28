#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
void excute(char **newargs);
int my_strtok(char *cmd);
int main();
char *split(char *line, const char *delim);
pid_t fork(void);
int my_execvp(const char *file, char *const argv[]);
size_t _strlen(char *s);
int _execlp(const char *file, const char *arg, ...);
int _strcmp(char const string1[], char const string2[]);
int _strncmp(const char *s1, const char *s2, size_t n);
int _putchar(char c);
void _puts(char *str);

#endif
