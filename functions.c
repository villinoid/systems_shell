#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "functions.h"
//Return -1 = exit shell
void stdin_redirect(char *file_name, char **command) {
    int new_file = open(file_name, O_RDONLY, 0666);
    int backup = dup(0);
    dup2(new_file, 0);
    execvp(command[0],command);
    dup2(new_file, backup);
    
}

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

int redir_exec(char *input_buffer) {
	char **funcs = malloc(sizeof(char) * 150);
    format_whitespace(input_buffer);
    funcs=parse_args(funcs,input_buffer,' ');
	execvp(funcs[0],funcs);
}
void redirect(char *file_name, char* command) {
    int new_file = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    int backup = dup(1);
    dup2(new_file, 1);
    redir_exec(command);
    dup2(new_file, backup);
    
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

//need to remove \n before
char **parse_args(char **return_args, char *line, char separator) //Ex: "ls -a -f"
{
	
	char *s, *b;
	s = line;
	
	//printf("s: %s\n",s);
	int i = 0;
	while (s)
	{
		s=trim_spaces(s);
		return_args[i] = strsep(&s, &separator);
		
		i++;
	}
	return_args[i]=NULL;

	return return_args;
}

int main_exec(char ** args,char * in_string){
	int i,finished;
	if (redir_check(in_string)) {
		
		char fn[100];
		char **funcs = malloc(sizeof(char) * 150);
		char **positions = malloc(sizeof(char) * 100);
		funcs = parse_args(funcs, in_string, ' ');
		positions = count_sep(funcs);
		funcs = redir_parse(funcs);
		int k = 0;
		while (funcs[k]) {
			printf("%s\n", funcs[k]);
			k++;
		}
	
		if (pos_length(positions) == 1) {
			if ((positions[0])[0] == 62) {
				int f=0;
				f=fork();
				if (!f) {
					redirect(funcs[1], funcs[0]);
					return -1;
				}
				else {
					return 0;
				}
			}
			if ((positions[0])[0] == 60) {
				int f=0;
				f=fork();
				if (!f) {
					strcpy(fn, funcs[ (positions[0])[1] ]);
					funcs = stdin_arr(funcs, (positions[0])[1]);
					stdin_redirect(fn, funcs);
					return -1;
				}
				else {
					return 0;
				}
			}
		}

		else {

		}
		
	}
	else {
		args=parse_args(args,in_string, ' ');


		
		//MAIN
		//Check what type it is
		//exit
		if(!strcmp(args[0],"exit"))
			return -1;
		//cd
		if(!strcmp(args[0],"cd")){
			if(!args[1])
				printf("No args inputted for cd\n");//PERHAPS GO HOME?
			chdir(args[1]);
			}
		else{
			//Redirct
			
			//Pipe

			//Normal run ls or whatever
			int f=0;
			f=fork();
			
			if(!f){//CHILD START
				finished=0;

				//PATH Exec
				finished=execvp(args[0],args);
				printf("Errror %d: %s\n",errno,strerror(errno));
				
				//Non PATH exec?
				//
				//
				
				return -1;
				}//CHILD END
			else{
				return 1;
			}
		}
	}
}

void format_whitespace(char *line){
	int i=0;
	while(line[i]){
		if(line[i]=='\t'||line[i]=='\n')
			line[i]=' ';
		i++;
	}
}

char *trim_spaces(char *line){
	int i=0;
	int j=strlen(line)-1;
	while(line[i]==' '){
		i++;
	}
	while(line[j]==' '){
		line[j]=0;
		j--;
	}
	return line+i;
}
			
	