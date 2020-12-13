#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

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
	int i,finished;
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
			printf("I am the child\n");
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
			
	