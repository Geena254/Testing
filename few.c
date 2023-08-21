#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
	pid_t ch_pid;
	int j, status;
	char *arg[] = {"ls", "-l", "/tmp", NULL};

	for (j = 0; j <= 2; j++)
	{
		ch_pid = fork();
		if (ch_pid == -1)
		{
			perror("Error:");
			return (1);
		}
	}
	if (ch_pid == 0)
	{
		execve("/usr/bin/ls", arg, NULL);
		perror("Error:");
		exit(1);
	}
	else
	{
		/* parent process waits until child processes are executed */
		wait(&status);
	}
}
