#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "exec.h"
#include "redirect.h"

char **redir_parse(char **);
char **count_sep(char **);
int pos_length (char **);
char **stdin_arr(char **, int);
int redir_check(char *);
void stdout_redirect(char *, char **);
void stdin_redirect(char *, char **);
void double_redirect(char *, char *, char **);