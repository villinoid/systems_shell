#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


char **parse_args(char *line) //Ex: "ls -a -f"
{
	char **return_args = malloc(sizeof(char) * strlen(line));
	char *s, *b;
	s = line;
	s[strlen(s)-1]=NULL;
	printf("s: %s\n",s);
	int i = 0;
	while (s)
	{
		return_args[i] = strsep(&s, " ");
		i++;
	}
	return_args[i]=NULL;

	return return_args;
}