#include "main.h"
#define SIZE 1024
/**
 * _getline - to read line from stdin
 * @prompt:
 * @fd:
 * @status:
 * Return: 
 */
char *_getline(char *cmd, int fd, int *status)
{    
	static char buffer[SIZE];
	static int current = 0, size = 0;
	int len;
	char *line = NULL;
	
	if (cmd != NULL)
	{
		write(STDOUT_FILENO, cmd, strlen(cmd));
	}
	while (1)
	{
		if (current >= size)
		{
			size = read(fd, buffer, SIZE);
			if (size == 0)
			{
				*status = 0; 
				return (line);
			} 
			else if (size < 0)
			{
				*status = -1;
				free (line);
				return (NULL);
			}
			current = 0;
			size = size;
		}
		if (buffer[current] == '\n')
		{
			buffer[current] = '\0';
			current++;
			if (line == NULL)
			{
				line = strdup("");
				if (line == NULL)
				{
					*status = -1;
					return (NULL);
				}
			}
			len = strlen(line);
			line = realloc(line, len + 2);
			if (line == NULL)
			{
				*status = -1;
				free (line);
				return (NULL);
			}
			line[len] = buffer[current];
			current++;
			line[len + 1] = '\0';
		}
	}
}
