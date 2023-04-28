#include "main.h"
/**
 * _changer - take unsigned int to return string
 * @number: unsignerd int
 * Return: string changed
 */

char *_changer(unsigned int number)
{
	char *str;
	unsigned int num, i, j;

	num = number;
	i = 0;
	while (num != 0)
	{
		i++;
		num /= 10;
	}
	str = (char *) malloc(sizeof(char) * (i + 1));
	if (str == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	j = 0;
	while (number != 0)
	{
		str[i - j - 1] = (number % 10) + '0';
		number /= 10;
		j++;
	}
	str[i] = '\0';
	return (str);
	free(str);
}

/**
 * _error - print the error message
 * @string: points to a string
 * @list: struct
 * Return: nothing
 */
void _error(list_t *list, char *string)
{
	char *number;

	_puts(list->args[0]);
	_puts(": ");
	number = _changer(list->number);
	_puts(number);
	free(number);
	_puts(": ");
	_puts(list->args[0]);
	if (string != NULL)
	{
		_puts(string);
	}
}
