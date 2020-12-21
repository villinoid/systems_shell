#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "exec.h"

char **redir_parse(char **); //gets rid of redirection operators
char **count_sep(char **); //finds position of redirection and piping operators
int pos_length (char **); //finds how many redirection operators there are
char **stdin_arr(char **, int); //gets command for input redirection without file
int redir_check(char *); //checks if redirection or piping is involved
void stdout_redirect(char *, char **); //opens output file and swaps it with stdout and executes command 
void stdin_redirect(char *, char **); //opens input file and swaps it with stdin so command reads input file
void double_redirect(char *, char *, char **); //swaps input and stdin and swaps output and stdout -> input is read and modified -> written to output
void pipe_redirect_and_fork(char **, char **); //opens an unnamed pipe and forks and allows for communication between processes 
