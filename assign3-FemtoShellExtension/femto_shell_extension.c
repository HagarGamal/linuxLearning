#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
 #include <stdlib.h>
int parse(char *s, char *strings[])
{
    char *token;
    token = strtok(s, " ");
    strings[0] = token;
    int i = 1;
    while (token != NULL) {
	token = strtok(NULL, " ");
	strings[i] = token;
	i++;
    }
    return i;
}

int parseVar(char *s, char *name[], char *value[], int i)
{
	char *token;
	char * copiedS;
	strcpy(copiedS, s);
	token = strtok(s, "=");
	if(strcmp(token, copiedS) != 0)
	{
 		name[i] = token;
	        token = strtok(NULL, " ");
		value[i] = token;
		return 0;
	}
	else
	{
		return 1;
	}
	
}

const char * construct_promMsg()
{
    char * envUSER = getenv("USERNAME");
    char * envPWD = getenv("PWD");
    char * promMsg = envUSER;
    strcat(promMsg, "@");
    char hostname[100];
    gethostname(hostname, 100);
    strcat(promMsg, hostname);
    strcat(promMsg, ":");
    strcat(promMsg, envPWD);
    strcat(promMsg, "$ ");
    return promMsg;
}

int main()
{
    char buff[100];
    char buffTemp[100];
    int ret_pid;
    int status;
    char *strings[10];
    char *name[100];
    char *value[100];
    char *namemalloc[100];
    char *valuemalloc[100];
    const char * promMsg = construct_promMsg();
    int i = 0;
    int retP;
    int j;
    while (1) {
	printf("%s", promMsg);
	fgets(buff, 100, stdin);
	int len = strlen(buff);

	buff[len - 1] = '\0';
	strcpy(buffTemp, buff);
	if (len > 1)
	{
		 retP = parseVar(buff, name, value, i);
        }
	if(len > 1 && retP == 0)
	{
		namemalloc[i] = (char *) malloc(strlen(name[i]) * sizeof(char));
	        valuemalloc[i] = (char *) malloc(strlen(value[i]) * sizeof(char));
		strcpy(namemalloc[i], name[i]);
		strcpy(valuemalloc[i], value[i]);
		i++;
	}
	else if (len > 1 && retP !=0 )
	{
		if(strcmp(buffTemp, "set")== 0)
		{
			for(j = 0; j < i; j++)
				printf("local_vars[%d]: %s = %s\n", j, namemalloc[j], valuemalloc[j]);
			
		}
		else
		{
	   		 ret_pid = fork();

	   		 if (ret_pid == 0) {
				// child process
				parse(buffTemp, strings);
				int ret = execvp(strings[0], strings);
				printf("%s: not a valid cmd\n", strings[0]);
	    		}
			 else if (ret_pid > 0) {
				// parent process
				wait(&status);
	   		} else {
				printf("fork failed");
	   		 }
		}
       }
 }
    for(int ii = 0; ii < i; i++)
    {
	    free(namemalloc[ii]);
	    free(valuemalloc[ii]);
    }
    return 0;
}
