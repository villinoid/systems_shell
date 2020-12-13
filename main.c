#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	char input_buffer[1000];
	char curr_dir[100];
	int exec_return;
	
	while(1){
		
		getcwd(curr_dir,99);
		printf("%s - $ ",curr_dir);

		
		fgets(input_buffer,sizeof(input_buffer),stdin);

		exec_return=0;
		exec_return=main_exec(input_buffer);
		if(exec_return==-1)
			return 0;


		//PARSE DIVIDE BY ;


		/*
		args=parse_args(input_buffer);


		
		//MAIN
		//Check what type it is
		//exit
		if(!strcmp(args[0],"exit"))
			return 0;
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
		//END
		*/
	}
	return 0;
}
		