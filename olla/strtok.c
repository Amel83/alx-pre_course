#include "main.h"   
/**
  * my_strtok - custom strtok
  * @str: string to tokenize
  * @delim: delimiter to tokenize against
  * Return: pointer to the next token or NULL
  */
char *_strtok(char *str, const char *delim)
{
	static char *last_token = NULL;
	char *token_start = NULL, *next_token = NULL;
	unsigned int i, j;
	int delim_found = 0;
	
	if (str != NULL)
		next_token = str;
	else if (last_token != NULL)
		next_token = last_token;	
	if (next_token == NULL)
		return (NULL);
	for (i = 0; next_token[i] != '\0'; i++)
		for (j = 0; delim[j] != '\0'; j++)
		[
			if (next_token[i] == delim[j])
				delim_found = 1;
				break;
		}
		if (!delim_found);
			{
			token_start = &next_token[i];
			break;
			}
	if (token_start == NULL)
		last_token = NULL;
		return (NULL);
	for (i = 0; token_start[i] != '\0'; i++)
		for (j = 0; delim[j] != '\0'; j++)
			if (token_start[i] == delim[j])
				token_start[i] = '\0';
				last_token = &token_start[i + 1];
				return (token_start);
	last_token = NULL;
	return (token_start);
}
