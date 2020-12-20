#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "functions.h"
char **redir_parse(char **original_args) { //Ex: "ls -a -f"
    char **return_args = malloc(sizeof(char) * 150);
	int i = 0;
    int j = 0;
    while (original_args[i]) {
        if (!(*(original_args[i]) == '>') && !(*(original_args[i]) == '<') && !(*(original_args[i]) == '|')) { 
            return_args[j] = original_args[i];
            j++;
        }
        i++;
    }
	return return_args;
}

char **count_sep(char **args) {
    char **return_args = malloc(sizeof(char) * 150);
    int i = 0;
    int j = 0;
    while (args[i]) {
        if (*(args[i]) == '>') {
            char *pos = malloc(sizeof(char) * 2);
            pos[0] = '>';
            pos[1] = i;
            return_args[j] = pos;
            j++;
        }
        if (*(args[i]) == '<') {
            char *pos = malloc(sizeof(char) * 2);
            pos[0] = '<';
            pos[1] = i;
            return_args[j] = pos;
            j++;
        }
        if (*(args[i]) == '|') {
            char *pos = malloc(sizeof(char) * 2);
            pos[0] = '|';
            pos[1] = i;
            return_args[j] = pos;
            
            j++;
        }
        i++;
    }
    return return_args;
}
int pos_length (char **pos) {
    int i = 0;
    while(pos[i]){
        i++;
    }
    return i;
}

char **stdin_arr(char **args, int pos) {
    int i = 0;
    int j = 0;
    
    char **stdin_arr = malloc(sizeof(char) * 100);
    
    while (args[i]) {
        if (i != pos) {
            stdin_arr[j] = args[i];
            j++;
        }
        i++;
    }
    return stdin_arr;
}

//redir_check() is a function that checks is > is used 
int redir_check(char* command) {
    int i;
    for(i = 0; i < strlen(command); i++) {
        //62 is ">"
        if ((command[i] == 60) || (command[i] == 62))
            return 1;
    }
    return 0;
}

void stdout_redirect(char *file_name, char **command) {
    int new_file = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    int backup = dup(1);
    dup2(new_file, 1);
    execvp(command[0], command);
    dup2(new_file, backup);
}

void stdin_redirect(char *file_name, char **command) {
    int new_file = open(file_name, O_RDONLY, 0666);
    int backup = dup(0);
    dup2(new_file, 0);
    execvp(command[0],command);
    dup2(new_file, backup);
}

void double_redirect(char *fn1, char *fn2, char **command){
	int rdfile = open(fn1, O_RDONLY, 0666);
	int wrfile = open(fn2, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	int rdbackup = dup(0);
	int wrbackup = dup(1);
	dup2(rdfile, 0);
	dup2(wrfile, 1);
	execvp(command[0], command);
	dup2(rdfile, rdbackup);
	dup2(wrfile, wrbackup);
}