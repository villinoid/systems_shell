#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


char **parse_args(char *line) //Ex: "ls -a -f"
{
	char **return_args = malloc(sizeof(char) * strlen(line)); //Five args plus ending NULL
	char *s, *b;
	s = line;
	s[strlen(s)-1]=NULL;
	printf("s: %s\n",s);
	int i = 0;
	while (s)
	{
		//printf("RUN\n");
		//printf("%s\n",s);
		return_args[i] = strsep(&s, " ");
		//printf("%s\n",return_args[i]);
		i++;
		//printf("strlen: %d\n",strlen(s));
		//printf("END\n");
	}

	return return_args;
}