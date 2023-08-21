#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	int j = 0, status;
	pid_t ch_pid;
	char **arr;
	char *buff = NULL;
	char *token;
	size_t buffsize = 0;

	while(1)
	{
		write(1, "cisfun$ ", 9);
		getline(&buff, &buffsize, stdin);

		if (strcmp(buff, "exit\n") == 0) {
                    break; // Exit the loop and terminate the shell
                }

		token = strtok(buff, " \t\n");
		arr = malloc(sizeof(char *) * 1024);

		while (token)
		{
			arr[j] = token;
			token = strtok(NULL, " \t\n");
			j++;
		}
		arr[j] = NULL;
		ch_pid = fork();
		if (ch_pid == 0)
		{
			if (execve(arr[0], arr, NULL) == -1)
				perror("Error");
		}
		else
		{
			wait(&status);
		}
		j = 0;
		free(arr);
	}
	return (0);
}
