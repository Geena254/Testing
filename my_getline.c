#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "custom_getline.h"

#define INITIAL_BUFF_SIZE 1024
#define BUFFER_INCREMENT 1024

char* custom_getline()
{
	static char buff[INITIAL_BUFF_SIZE];
	static size_t pos = 0;
	char c;

	while (1)
	{
		if (pos == 0)
		{
			ssize_t bytesRead = read(STDIN_FILENO, buff, INITIAL_BUFF_SIZE);
			if (bytesRead <= 0)
			{
				if (bytesRead < 0)
					perror("Read error");
				else
					fprintf(stderr, "No input provided.\n");
				exit(EXIT_FAILURE);
			}
		}

		c = buff[pos];
		pos++;

		if (c == '\n' || c == '\0')
		{
			buff[pos - 1] = '\0';
			pos = 0;
			break;
		}
		if (pos >= INITIAL_BUFF_SIZE)
		{
			char *error_message = "Input too long.\n";
			write(STDERR_FILENO, error_message, strlen(error_message));
			exit(EXIT_FAILURE);
		}
	}

	return buff;
}
