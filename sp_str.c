#include <string.h>
#include <stdio.h>

int main(void)
{
	char str[] = "This is my main file";
	char delimeter[5] = " ";
	char *bag;

	bag = strtok(str, delimeter);
	while (bag != NULL)
	{
		printf("%s\n", bag);
		bag = strtok(NULL, delimeter);
	}
	return (0);
}
