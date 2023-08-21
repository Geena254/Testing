#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main()
{
	pid_t child_pid;
	int status;
	char *argv[] = {"ls", "-l", "/tmp", NULL};

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	
	if (child_pid == 0)
	{
		execve("/usr/bin/ls", argv, NULL);
		perror("Error:");
		exit(1);
	}
	else
		wait(&status);

}
