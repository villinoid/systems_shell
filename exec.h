#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char **parse_args(char **,char *, char);  //parses line with a separator Ex: "ls -a -f"
int main_exec(char **,char *);//the main execute function all executes 1 command
void format_whitespace(char *);//converts all other instances of whitespace to ' '
char *trim_spaces(char *);//removes ' ' from the ends of the string
