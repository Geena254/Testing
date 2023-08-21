#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "custom_getline.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 1024

void sample_shell()
{
	int j, status;
	pid_t ch_pid;
	char **arr;
	char *buff = NULL;
	size_t buffsize = 0;

	while (1)
	{
		write(1, "cisfun$ ", 9);
		buff = custom_getline();

		if (strcmp(buff, "exit") == 0)
		{
			break; // Exit the loop and terminate the shell
		}

		arr = malloc(sizeof(char *) * MAX_ARGS);

		int i = 0;
		j = 0;
		int len = strlen(buff);

		while (i < len)
		{
			// Skip leading whitespace
			while (i < len && (buff[i] == ' ' || buff[i] == '\t' || buff[i] == '\n'))
			{
				i++;
			}

			if (i < len)
			{
				int start = i;
				while (i < len && buff[i] != ' ' && buff[i] != '\t' && buff[i] != '\n')
				{
					i++;
				}
				int end = i;

				arr[j] = malloc(end - start + 1);
				strncpy(arr[j], buff + start, end - start);
				arr[j][end - start] = '\0';
				j++;
			}
		}
		arr[j] = NULL;

		if (j > 0)
		{
			ch_pid = fork();
			if (ch_pid == 0)
			{
				execvp(arr[0], arr); // Search for the command in PATH
				perror("Error");
				exit(1);
			}
			else
			{
				wait(&status);
			}
		}

		for (int i = 0; i < j; i++)
		{
			free(arr[i]);
		}
		free(arr);
	}

	return;
}

int main()
{
	sample_shell();
	return 0;
}
