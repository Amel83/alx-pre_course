#include "main.h"
#define MAX_PATH_LENGTH 1024
void directory(char *arg)
{
	char *cmd = NULL, *home, *path = NULL, *previous_dir = NULL;
	home = getenv("HOME");

	if (strcmp(cmd, "cd") == 0)
	{
		if (arg == NULL)
		{
			arg = home;
		}
		else if (strcmp(arg, "-") == 0)
		{
			if ((previous_dir = getenv("OLDPWD")) == NULL)
			{
						perror("errno");
			}
			arg = previous_dir;
		}
		if (chdir(arg) != 0)
		{
			perror("errno");
		}
		setenv("OLDPWD", getcwd(path, MAX_PATH_LENGTH), 1);
		setenv("PWD", getcwd(path, MAX_PATH_LENGTH), 1);
	}
}
