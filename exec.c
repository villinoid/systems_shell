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
//Return -1 = exit shell
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
	int finished;
	if (redir_check(in_string)) {

		char fn[100];
		char **funcs = malloc(sizeof(char) * 150);
		char **pipe_funcs = malloc(sizeof(char) * 150);
		char **positions = malloc(sizeof(char) * 100);
		char pipe_string[100];
		strcpy(pipe_string,in_string);
		funcs = parse_args(funcs, in_string, ' ');
		pipe_funcs = parse_args(pipe_funcs, pipe_string, ' ');
		positions = count_sep(funcs);
		funcs = redir_parse(funcs);
		pipe_funcs[(positions[0])[1]]=0;


		if (pos_length(positions) == 1) {
			if ((positions[0])[0] == 62) {
				int f=0;
				f=fork();
				if (!f) {
					strcpy(fn, funcs[ (positions[0])[1] ]);
					funcs[(positions[0])[1]] = 0;
					stdout_redirect(fn, funcs);
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

			if ((positions[0])[0] == 124) {
				int f=0;
				f=fork();
				if(!f) {//Child
					pipe_redirect_and_fork(pipe_funcs,pipe_funcs+1+(positions[0])[1]);
					return -1;
				}
				else{
					return 0;
				}
			}



		}

		else {
			int f=0;
			f=fork();
			if (!f) {
				char fn2[100];

				strcpy(fn, funcs[ (positions[0])[1] ]);

				strcpy(fn2, funcs[(positions[1])[1] - 1]);

				funcs[(positions[1])[1]- 1] = 0;
				funcs = stdin_arr(funcs, (positions[0])[1]);
				double_redirect(fn, fn2, funcs);
				return -1;
			}
			else {
				return 0;
			}
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
		if(!strcmp(args[0],"cd")) {
			if(!args[1])
				printf("No args inputted for cd\n"); //PERHAPS GO HOME?
			chdir(args[1]);
		}
		else{
			//Normal run ls or whatever
			int f=0;
			f=fork();

			if(!f) {//CHILD START
				finished=0;

				//PATH Exec
				finished=execvp(args[0],args);
				printf("Errror %d: %s\n",errno,strerror(errno));

				//Non PATH exec?
				return -1;
			}        //CHILD END
			else{
				return 1;
			}
		}
	}
}

void format_whitespace(char *line){
	int i=0;
	while(line[i]) {
		if(line[i]=='\t'||line[i]=='\n')
			line[i]=' ';
		i++;
	}
}

char *trim_spaces(char *line){
	int i=0;
	int j=strlen(line)-1;
	while(line[i]==' ') {
		i++;
	}
	while(line[j]==' ') {
		line[j]=0;
		j--;
	}
	return line+i;
}
