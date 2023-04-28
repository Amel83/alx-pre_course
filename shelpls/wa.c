#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"
int main()
{
	char *cmd, *arg;
	char **args;
	int arg_index;
	char *line = NULL;
	size_t i = 0;
	int len;
	extern char **environ;

	int status;
	pid_t pid;

	while (1)
	{
		_puts("$ ");
		cmd = NULL;
		if (getline(&line, &i, stdin) == -1)
		{
			_puts("no input to read");
			break;
		}
		len = _strlen(line);
		if (len > 0 && line[len-1] == '\n')
		{
			line[len-1] = '\0';
		}
		args = malloc(sizeof(char*) * (len + 1));
		arg_index = 0;
		arg = strtok(line, " ");
		while (arg != NULL) {
			args[arg_index++] = arg;
			arg = strtok(NULL, " ");
		}
		args[arg_index] = NULL;
		cmd = args[0];

		pid = fork();
		if (pid == -1)
		{
			perror("errno");
			exit(1);
		}
		else if (pid == 0)
		{
			char **newargs = malloc(sizeof(char*) * (arg_index + 1));
			int i;
			for (i = 0; i < arg_index; i++) {
				newargs[i] = args[i];
			}
			newargs[i] = NULL;

			if (_strncmp(cmd, "/", 1) == 0) {

				if (execve(args[0], newargs, environ) == -1) {
					perror("errno");
					exit(1);
				}
			}
		       	else {

				char *path = getenv("PATH");
				char *path_copy = strdup(path);
				char *dir = strtok(path_copy, ":");
				char *full_path = malloc(strlen(dir) + strlen(cmd) + 2);
				    while (dir != NULL) {
					    if (full_path != NULL) {

						    full_path[0] = '\0';


						    if (dir != NULL) {
							    strcat(full_path, dir);
							    strcat(full_path, "/");
						    }
						    if (cmd != NULL) {
							    strcat(full_path, cmd);
						    }
					    }

			    		    if (access(full_path, X_OK) == 0) {
						if (execve(full_path, newargs, environ) == -1) {
							perror("errno");
							exit(1);
						}
					}
					dir = strtok(NULL, ":");
				}


				perror("errno");
			       
		
				exit(1);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
		}

		if (_strncmp(cmd, "exit", 5) == 0)
		{
			status = atoi(&cmd[5]);
			exit(status);
		}
	}
	free(line);
	return 0;
}
