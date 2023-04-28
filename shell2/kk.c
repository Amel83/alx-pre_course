#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_PATH_LENGTH 1024
#define MAX_ARGUMENT 100
/**
 * prompt - reads from the input
 * apply the cd command
 * fork and excute
 * @argv: check the code
 * @cmd: check the code
 * Return: 0 on success
 */

int main()
{
	
	char path[MAX_PATH_LENGTH];
	char *home_dir = getenv("HOME");
	char *previous_dir = NULL, *cmd;
	char line[MAX_PATH_LENGTH];
	int status;
	pid_t pid; 
	char *argv;
	while (1)
	{
		printf("$ ");
		cmd = NULL;
		argv = NULL;
		previous_dir = NULL;
		if (fgets(line, sizeof(line), stdin) == NULL)
		{
			printf("no input to read");
			break;
		}
		line[strcspn(line, "\n")] = '\0';  
		cmd = strtok(line, " ");
		if (cmd == NULL)
		{
			continue;  
		}
		argv = strtok(NULL, " ");
		if (strcmp(cmd, "cd") == 0)
		{
			if (argv == NULL)
			{
				argv = home_dir;
			} 
			else if (strcmp(argv, "-") == 0)
			{
				if ((previous_dir = getenv("OLDPWD")) == NULL)
				{
					fprintf(stderr, "cd: OLDPWD not set\n");
					continue;
				}
				argv = previous_dir;
			}
			if (chdir(argv) != 0)
			{
				fprintf(stderr, "cd: %s: No such file or directory\n", argv);
				continue;
			}
			setenv("OLDPWD", getcwd(path, MAX_PATH_LENGTH), 1);
			setenv("PWD", getcwd(path, MAX_PATH_LENGTH), 1);
			continue;
		}
		pid = fork();
		if (pid == -1)
		{
			fprintf(stderr, "fork failed\n");
			exit(1);
		}
		else if (pid == 0)
		{
			execlp(cmd, cmd, argv, NULL);
			fprintf(stderr, "%s: command not found\n", cmd);
			exit(1);
		}
		else
		{
			waitpid(pid, &status, 0);
		}
		if (strncmp(cmd, "exit",5) == 0) 
		{
			status = atoi(&cmd[5]);
			exit(status);
		}
	}
	return 0;
}

