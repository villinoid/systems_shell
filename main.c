#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	printf("\n");
	char input_buffer[1000];
	char** args;
	int i;
	int finished,status;
	while(1){
		fgets(input_buffer,sizeof(input_buffer),stdin);
		printf("%s",input_buffer);
		args=parse_args(input_buffer);
		//Check what type it is
		//exit
		if(!strcmp(args[0],"exit"))
			return 0;
		//CD
		if(!strcmp(args[0],"cd"))
			chdir(args[1]);
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
	return 0;
}
		