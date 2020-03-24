#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <errno.h>   
#include <sys/wait.h>
#include <stdarg.h>

#define MAX_BUFFER 1024                      
#define MAX_ARGS 64                           
#define SEPARATORS " \t\n"  


void getDir()
{
	char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
        printf("Current working dir: %s\n", cwd);
    } 
    return;
}

void changeDir(char *dir)
{
	chdir(dir);
}

void run(char *program, char* argv[])
{
	pid_t pid; 
   	int status; 
   	pid = fork(); // creates child process 

   	printf("%c\n", argv[1][0]);
   	if (pid == -1)
   	{ 
     	exit(EXIT_FAILURE); 
   	} 
   	else if (pid == 0) // successful creation, does execution
   	{
   		execv(program, argv);
   	}

   	//waitpid(pid, &status, 0);

   	if (status < 0)
   	{
   		fprintf(stdout, "Execution failed");
   	}
}

void background(char *program, char *argv[])
{
	pid_t pid; 
   	int status; 
   	pid = fork(); // creates child process 
   	if (pid == -1)
   	{ 
     	exit(EXIT_FAILURE); 
   	} 
}

int main (int argc, char **argv)
{
	char buf[MAX_BUFFER];                      
    char *args[MAX_ARGS];                     
    char **arg;                       
    char *prompt = "#";
    char lastcommands[64][512];
    int i;
    int j = 0;

    while (!feof(stdin))
    {
    	fputs(prompt, stdout);
    	if (fgets(buf, MAX_BUFFER, stdin))
    	{
    		// Stores all arguments passed in
    		strcpy(lastcommands[j++], buf); 
    		arg = args;
    		*arg++ = strtok(buf, SEPARATORS);
    		// Separate args
    		while ((*arg++ = strtok(NULL, SEPARATORS)));

    		// If there is an argument, compare it to commands
    		if (args[0])
    		{
    			if (!strcmp(args[0], "quit"))
    			{
    				exit(1);
    			}

    			if (!strcmp(args[0], "whereami"))
    			{
    				getDir();
    				continue;
    			}

    			if (!strcmp(args[0], "changedir"))
    			{
    				changeDir(args[1]);
    				continue;
    			}

    			if (!strcmp(args[0], "lastcommands"))
    			{
    				// Clears the array containing previous commands
    				if (args[1] != NULL && !strcmp(args[1], "-c"))
    				{
    					for (i = 0; i < j; i++)
    					{
    						strcpy(lastcommands[i], "\0");
    					}
    					j = 0;
    				}
    				else
    				{
    					// Displays all previous commands
    					for (i = 0; i < j; i++)
    					{
    						fprintf(stdout, "%s\n", lastcommands[i]);
    					}	
    				}
    				continue;
    			}

    			if (!strcmp(args[0], "run"))
    			{
    				char* argv[64];
    				// Goes thorugh all parameters in argument
    				// Copies into a single array
    				for (i = 1, j = 0; args[i] != NULL; i++, j++)
    				{
    					argv[j] = malloc(sizeof(char*) * strlen(args[i] + 1));
    					strcpy(argv[j], args[i]);
    				}
    				// Terminating array with \0 necessary for exec
    				argv[j] = malloc(sizeof(char*));
    				strcpy(argv[j], "\0");
    				
    				run(args[1], argv);
    				continue;
    			}

    			if (!strcmp(args[0], "background"))
    			{
    				char* argv[64];
    				
    				for (i = 1, j = 0; args[i] != NULL; i++, j++)
    				{
    					argv[j] = malloc(sizeof(char*) * strlen(args[i] + 1));
    					strcpy(argv[j], args[i]);
    				}
    				argv[j] = malloc(sizeof(char*));
    				strcpy(argv[j], "\0");
    				
    				background(args[1], argv);
    				continue;
    			}

    			if (!strcmp(args[0], "exterminate"))
    			{
    				int ret = kill(args[1], SIGKILL);
    				if (ret == -1)
    				{
    					fprintf(stdout, "Kill failure\n");
    				}
    				else
    				{
    					fprintf(stdout, "Process successfully killed\n");
    				}
    				continue;
    			}

    			// If argument not recognized as commands, print it
    			arg = args;
    			while (*arg)
    			{
    				fprintf(stdout, "%s\n", *arg++);
    			}
    			fputs("\n", stdout);
    		}
    	}
    }
    return 0;
}
