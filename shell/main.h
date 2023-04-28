#ifndef MAIN_H
#define MAIN_H
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_PATH_LENGTH 1024
#define MAX_ARGS 100

    char path[MAX_PATH_LENGTH];
    char *home_dir = getenv("HOME");
    char *prev_dir = NULL;
    char *cmd = NULL;
    char *arg = NULL, line[MAX_PATH_LENGTH];
    int status;
    pid_t pid;

void prompt(char *cmd, char *arg);



#endif
