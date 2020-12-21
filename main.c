#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "exec.h"
#include "redirect.h"

int main(){
	char input_buffer[1000];
	char curr_dir[100];
	int exec_return;
	int i, status;
	char **args = malloc(sizeof(char) * 150);
	char **funcs = malloc(sizeof(char) * 150);
	char name_buf[1000];
	readlink("/proc/self/fd/0",name_buf,1000);//gets the directory for the input stream
	while(1) {
		printf("%s\n",name_buf);
		getcwd(curr_dir,99);
		if (!strcmp(name_buf,"/dev/tty1")){
			printf("%s - $ ",curr_dir);
		}

		fgets(input_buffer,sizeof(input_buffer),stdin);

		format_whitespace(input_buffer);
		//rintf("test\n");
		funcs=parse_args(funcs,input_buffer,';');
		i=0;
		while(funcs[i]) {
			//printf("a\n");
			exec_return=0;
			exec_return=main_exec(args,funcs[i]);
			i++;
			wait(&status);
			if(exec_return==-1) {
				free(args);
				free(funcs);
				return 0;
			}

		}
	}
	return 0;
}
