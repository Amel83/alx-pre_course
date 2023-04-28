#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_PATH_LENGTH 1024
#define MAX_ARGS 100

void prompt(char *cmd) {
    char path[MAX_PATH_LENGTH];
    char *home_dir = getenv("HOME");
    char *prev_dir = NULL, *line = NULL, *arg = NULL;
  
        cmd = NULL;
        arg = NULL;
        prev_dir = NULL; 
    while (1) {
        printf("%s $ ", getcwd(path, MAX_PATH_LENGTH));
        cmd = NULL;
        arg = NULL;
        prev_dir = NULL;

       
        
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;  
        }
        line[strcspn(line, "\n")] = '\0';  
  
        cmd = strtok(line, " ");
        if (cmd == NULL) {
            continue;  
        }
        arg = strtok(NULL, " ");

        
        if (strcmp(cmd, "cd") == 0) {
            if (arg == NULL) {
                arg = home_dir;
            } else if (strcmp(arg, "-") == 0) {
                if ((prev_dir = getenv("OLDPWD")) == NULL) {
                    fprintf(stderr, "cd: OLDPWD not set\n");
                    continue;
                }
                arg = prev_dir;
            }

            
            if (chdir(arg) != 0) {
                fprintf(stderr, "cd: %s: No such file or directory\n", arg);
                continue;
            }


            setenv("OLDPWD", getcwd(path, MAX_PATH_LENGTH), 1);
            setenv("PWD", getcwd(path, MAX_PATH_LENGTH), 1);
            continue;
        }
    }
   
}


void execute(char *cmd)
{	pid_t pid;
	int status;
	char  *arg = NULL;
	pid = fork();
        if (pid == -1) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (pid == 0) {
           
            execlp(cmd, cmd, arg, NULL);
            fprintf(stderr, "%s: command not found\n", cmd);
            exit(1);
        } else {
         
            waitpid(pid, &status, 0);
        }
        if (strncmp(cmd, "exit", 5) == 0) 
	{
		status = atoi(&cmd[5]);
		exit(status);
	}
  


}

