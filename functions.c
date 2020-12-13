#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"
#include <sys/types.h>
#include <sys/wait.h>

//Return -1 = exit shell


//need to remove \n before
char **parse_args(char *line, char separator) //Ex: "ls -a -f"
{
	char **return_args = malloc(sizeof(char) * strlen(line));
	
	char *s, *b;
	s = line;
	
	//printf("s: %s\n",s);
	int i = 0;
	while (s)
	{
		return_args[i] = strsep(&s, &separator);
		i++;
	}
	return_args[i]=NULL;

	return return_args;
}

int main_exec(char * in_string){
	char** args;
	int i,finished,status;

	args=parse_args(in_string, ' ');


		
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
			finished=execvp(args[0],args);//ERRNO????//ERRNO????//ERRNO????//ERRNO????//ERRNO????//ERRNO????
			//Non PATH exec?
			//
			//
			printf("CHILD PROCESS - ERROR WITH COMMAND INPUT\n");
			return 1;
			}//CHILD END
		else
			free(args);

		wait(&status);
		}
}