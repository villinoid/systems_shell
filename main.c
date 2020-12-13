#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"

int main(){
	printf("\n");
	char input_buffer[1000];
	char** args;
	int i;
	int finished;
	while(1){
		fgets(input_buffer,sizeof(input_buffer),stdin);
		printf("%s",input_buffer);
		args=parse_args(input_buffer);
		//Check what type it is
		//exit
		if(!strcmp(args[0],"exit"))
			return 0;
		//Redirct

		//Pipe

		//Normal run ls or whatever
		int f=0;
		f=fork();
		if(!f){
			finished=0;
			finished=execvp(args[0],args);//ERRNO????//ERRNO????//ERRNO????//ERRNO????//ERRNO????//ERRNO????
			printf("CHILD PROCESS - ERROR WITH COMMAND INPUT\n");
			return 1;
			}
		else
			free(args);
	}
	return 0;
}
		