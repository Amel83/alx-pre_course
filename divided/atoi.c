#include "main.h"
/**
 * _atoi - convert string to an integer
 * @nptr: points to the string
 * Return: number of strings changed
 */

int _atoi(const char *nptr)
{
	int i = 0, sign = 1, j = 0;

	if (nptr[i] == ' ')
	{
		i++;
	}
	if (nptr[i] == '+')
	{
		i++;
	}
	else if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		j = j * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * j);
}
