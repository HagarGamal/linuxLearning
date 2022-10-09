#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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

int main()
{
    char buff[100];
    int ret_pid;
    int status;
    char *strings[10];
    while (1) {
	printf("Ana Gahez ya basha > ");
	fgets(buff, 100, stdin);
	int len = strlen(buff);
	buff[len - 1] = 0;
	ret_pid = fork();

	if (ret_pid == 0) {
	    // child process
	    parse(buff, strings);
	    execvp(strings[0], strings);
	} else if (ret_pid > 0) {
	    // parent process
	    wait(&status);
	} else {
	    printf("fork failed");
	}

    }
    return 0;
}
