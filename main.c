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
	while(1){
		fgets(input_buffer,sizeof(input_buffer),stdin);
		printf("%s",input_buffer);
		args=parse_args(input_buffer);
		execvp(args[0],args);
	}
	return 0;
}
		