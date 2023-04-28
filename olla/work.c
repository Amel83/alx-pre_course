#include "main.h"
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
	ssize_t bytes = 0;

	signal(SIGINT, sig_handler);
	while (bytes != EOF)
	{
		_isatty();
		bytes = getline(&line, &i, stdin);
		_EOF(bytes, line);
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
			free(args);
			free(line);
			exit(status);
		}
		execute_command(args);
		free(args);
		args = NULL;
		num = 0;
	}
	freee(line);
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
	if (*num == 0)
	{
		args[*num] = "";
		(*num)++;
	}
	args[*num] = NULL;
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
	char *cmd, *dir = NULL, *path;
	list_t list;

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
			list.args = args;
			list.number = 1;
			_error(&list, ": not found\n");
			_puts(dir);
			_puts("\n");
			exit(127);
		}
		args[0] = path;
		if (execve(args[0], args, environ) == -1)
		{
			list.args = args;
			list.number = 1;
			_error(&list, " \n");
			exit(127);
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
	char *path, *path_copy, *dir, *full_path = NULL;

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
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}
	free(full_path);
	free(path_copy);
	return (NULL);
}
