#include "main.h"
#include <stdlib.h>
/**
 * main - the main function fot other prototypes
 * doesn't take any parameter
 * Return: 0
 */
int main(void)
{
	char **args = NULL, *line = NULL;
	int num = 0, status = 0, len;
	size_t i = 0;

	while (1)
	{
		_puts("$ ");
		if (getline(&line, &i, stdin) == -1)
		{
			_puts("no input to read");
			break;
		}
		len = _strlen(line);
		if (len > 0 && line[len - 1] == '\n')
		{
			line[len - 1] = '\0';
		}	
		args = malloc(sizeof(char *) * (len + 1));
		parse_input(line, args, &num);
		if (_strncmp(line, "exit", 5) == 0)
		{
			status = _atoi(&line[5]);
			exit(status);
		}
		execute_command(args);
		free(args);
		args = NULL;
		num = 0;
	}
	free(line);
	return (0);
}

/**
 * parse_input - to devide the input using delim by strtok
 * @line: input command
 * @args: arrays of commands
 * @num: pointer to integer
 * Return: NULL
 */
void parse_input(char *line, char **args, int *num)
{
	char *arg = strtok(line, " ");

	while (arg != NULL)
	{
		args[*num] = arg;
		(*num)++;
		arg = strtok(NULL, " ");
	}
	args[*num] = NULL;
	directory(arg);	
}

/**
 * execute_command - fork and excute
 * @args: arrays of command
 * Return: none
 */
void execute_command(char **args)
{
	int status;
	pid_t pid;
	char *cmd, *path;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		cmd = args[0];
		path = search_path(cmd);
		if (path == NULL)
		{
			perror("errno");
			exit(1);
		}

		args[0] = path;
		if (execve(args[0], args, environ) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

/**
 * search_path - search and find the path
 * @cmd: pointer to char
 * Return: pointer to path
 */
char *search_path(char *cmd)
{
	char *path, *path_copy, *dir, *full_path;

	if (_strchr(cmd, '/') != NULL)
	{
		return (cmd);
	}
	path = _getenv("PATH");
	path_copy = _strdup(path);
	dir = strtok(path_copy, ":");
	full_path = malloc(_strlen(dir) + _strlen(cmd) + 2);

	while (dir != NULL)
	{
		if (full_path != NULL)
		{
			full_path[0] = '\0';
			_strcat(full_path, dir);
			_strcat(full_path, "/");
			_strcat(full_path, cmd);
		}

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}

	free(full_path);
	free(path_copy);
	return (NULL);
}
